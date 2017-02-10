#include <Windows.h>
#include <node.h>
#include <thread>
#include <list>
#include "keyboard.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

HHOOK hooked = 0;
std::unique_ptr<std::thread> messageThread;

std::list<int> keyboardHistory;
int lastKey = 0;
// interface
// ��ȡ���һ�μ���������
int CKeyboard::getLastKey()
{
    return lastKey;
}

// ģ����̰�ס
void CKeyboard::keyDown(int vkCode, int count)
{
    INPUT input;
    input.type = INPUT_KEYBOARD;
    // unicode char
    if (vkCode > 254) {
        input.ki.wVk = 0;
        input.ki.wScan = vkCode;
        input.ki.dwFlags = KEYEVENTF_UNICODE;
    } else {
        input.ki.wVk = vkCode;
        input.ki.wScan = vkCode;
        input.ki.dwFlags = 0;
    }
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    SendInput(1, &input, sizeof(INPUT));

    while (count > 1) {
        Sleep(100);
        SendInput(1, &input, sizeof(INPUT));
        count--;
    }
}

// ģ����̰�ס
bool CKeyboard::keyPress(int vkCode, int count)
{
    keyDown(vkCode, count);
    return true;
}

// ģ����̰�ס
void CKeyboard::keyUp(int vkCode, int count)
{
    INPUT input;
    input.type = INPUT_KEYBOARD;
    if (vkCode > 254) {
        input.ki.wVk = 0;
        input.ki.wScan = vkCode;
        input.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
    }
    else {
        input.ki.wVk = vkCode;
        input.ki.wScan = vkCode;
        input.ki.dwFlags = KEYEVENTF_KEYUP;
    }
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    SendInput(1, &input, sizeof(INPUT));

    while (count > 1) {
        Sleep(100);
        SendInput(1, &input, sizeof(INPUT));
        count--;
    }
}

// �ȴ��������
// �ű����е���һ�л���ͣ,���û����¼��̺����ִ��,���Ұ��û��İ����뷵��
int waitKey()
{
}

// sniffer keyboard press
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT* aboutKeyboard = (KBDLLHOOKSTRUCT*)lParam;

    lastKey = aboutKeyboard->vkCode;
    return CallNextHookEx(hooked, nCode, wParam, lParam);
}

void HookKeyboard()
{
    messageThread = std::unique_ptr<std::thread>(new std::thread([]() {
        hooked = SetWindowsHookEx(WH_KEYBOARD_LL, &LowLevelKeyboardProc, (HINSTANCE)&__ImageBase, NULL);

        MSG msg;
        HWND hwnd = nullptr;

        BOOL bRet;
        while ((bRet = GetMessage(&msg, hwnd, 0, 0)) != 0) {
            if (bRet == -1) {
                // something is wrong
                break;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }));

    node::AtExit([](void*) {
        UnhookWindowsHookEx(hooked);
        hooked = nullptr;

        if (messageThread)
        {
            DWORD threadId = GetThreadId(reinterpret_cast<HANDLE>(messageThread->native_handle()));
            PostThreadMessage(threadId, WM_QUIT, 0, 0);
            messageThread->join();
            messageThread.reset(nullptr);
        }
    }, nullptr);
}
