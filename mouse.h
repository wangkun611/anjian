#ifndef _MOUSE_H
#define _MOUSE_H

#include <windows.h>
#include <utility>
class CMouse
{
public:
    POINT getCursorPos();
    bool moveBy(int x, int y);
    bool moveTo(int x, int y);
};

#endif // _MOUSE_H
