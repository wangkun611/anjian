#include <Windows.h>
#include <node.h>
#include <thread>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

HHOOK hooked = 0;
std::unique_ptr<std::thread> messageThread;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT* ABoutKeyboard = (KBDLLHOOKSTRUCT*)lParam;

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
                // something is wroing
                break;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        OutputDebugString("exit messageThread");

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
        OutputDebugString("AtExit");
    }, nullptr);
}
