#ifndef _MOUSE_H
#define _MOUSE_H

#include <windows.h>
#include <utility>
class CMouse
{
public:
    POINT getCursorPos();
    bool mouseWheel(int wheelDelta);
    bool moveBy(int x, int y);
    bool moveTo(int x, int y);

    int getCursorShape();

    int getLastClick();
    bool leftClick();
    bool leftDoubleClick();
    void lockMouse(int x, int y);
    bool middleClick();
    bool rightClick();
};

#endif // _MOUSE_H
