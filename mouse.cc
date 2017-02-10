#include <Windows.h>
#include <utility>

#include "mouse.h"

static int screen_width  = GetSystemMetrics(SM_CXSCREEN);
static int screen_height = GetSystemMetrics(SM_CYSCREEN);

bool mouseClick(DWORD dwFlags1, DWORD dwFlags2, int count);
POINT screenPosToInputPos(POINT pt);

// interface
// ��ȡ��ǰ���λ������
POINT CMouse::getCursorPos()
{
    POINT pt;
    if (GetCursorPos(&pt)) {
        return pt;
    }
    return POINT{ 0, 0 };
}

// ��ȡ�����״
int CMouse::getCursorShape()
{
    return 0;
}

// ����ϴΰ���������
int CMouse::getLastClick()
{
    return 0;
}

// �������
bool CMouse::leftClick()
{
    return mouseClick(MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP, 1);
}

// ���˫��
bool CMouse::leftDoubleClick()
{
    return mouseClick(MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP, 2);
}

// �������λ��
void CMouse::lockMouse(int x, int y)
{
}

// �м�����
bool CMouse::middleClick ()
{
    return mouseClick(MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_MIDDLEUP, 1);
}

// �Ҽ�����
bool CMouse::rightClick ()
{
    return mouseClick(MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP, 1);
}

// �Ҽ�˫��
bool rightDoubleClick ()
{
    return mouseClick(MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP, 2);
}

// ������
bool CMouse::mouseWheel(int wheelDelta)
{
    POINT pt;
    if (!GetCursorPos(&pt)) {
        return false;
    }

    pt = screenPosToInputPos(pt);
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dx = pt.x;
    input.mi.dy = pt.y;
    input.mi.mouseData = wheelDelta;
    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_WHEEL;
    input.mi.time = 0;
    input.mi.dwExtraInfo = 0;

    return SendInput(1, &input, sizeof(INPUT)) > 0;
}

// �������ƶ�
bool CMouse::moveBy(int x, int y)
{
    POINT pt;
    if (!GetCursorPos(&pt)) {
        return false;
    }

    pt.x += x;
    pt.y += y;
    pt = screenPosToInputPos(pt);

    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dx = pt.x;
    input.mi.dy = pt.y;
    input.mi.mouseData = 0;
    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE;
    input.mi.time = 0;
    input.mi.dwExtraInfo = 0;

    return SendInput(1, &input, sizeof(INPUT)) > 0;
}

// ����ƶ�
bool CMouse::moveTo(int x, int y)
{
    POINT pt{ x, y };
    pt = screenPosToInputPos(pt);

    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dx = pt.x;
    input.mi.dy = pt.y;
    input.mi.mouseData = 0;
    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE;
    input.mi.time = 0;
    input.mi.dwExtraInfo = 0;

    return SendInput(1, &input, sizeof(INPUT)) > 0;
}


// ����ڵ�ǰλ�õ��
bool mouseClick(DWORD dwFlags1, DWORD dwFlags2, int count)
{
    POINT pt;
    if (!GetCursorPos(&pt)) {
        return false;
    }

    pt = screenPosToInputPos(pt);

    int inputCount = 0;
    INPUT input[2];
    input[0].type = INPUT_MOUSE;
    input[0].mi.dx = pt.x;
    input[0].mi.dy = pt.y;
    input[0].mi.mouseData = 0;
    input[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE|dwFlags1;
    input[0].mi.time = 0;
    input[0].mi.dwExtraInfo = 0;

    input[1].type = INPUT_MOUSE;
    input[1].mi.dx = pt.x;
    input[1].mi.dy = pt.y;
    input[1].mi.mouseData = 0;
    input[1].mi.dwFlags = MOUSEEVENTF_ABSOLUTE|dwFlags2;
    input[1].mi.time = 0;
    input[1].mi.dwExtraInfo = 0;

    for (int i = 0; i < count; i++) {
        inputCount += SendInput(2, input, sizeof(INPUT));
    }
    return inputCount >= 2*count;
}

// ��Ļ����ת����(0-65535)����ϵ
POINT screenPosToInputPos(POINT pt)
{
    pt.x = LONG(((double)pt.x+0.5)*(65535.0/screen_width));
    pt.y = LONG(((double)pt.y+0.5)*(65535.0/screen_height));
    return pt;
}
