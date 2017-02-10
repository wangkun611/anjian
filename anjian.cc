#include "anjian.h"
#include "keyboard.h"

CKeyboard* g_keyboard = nullptr;
CMouse*    g_mouse = nullptr;

CKeyboard* keyboard()
{
    if (!g_keyboard) {
        g_keyboard = new CKeyboard();
    }

    return g_keyboard;
}

CMouse* mouse()
{
    if (!g_mouse) {
        g_mouse = new CMouse();
    }

    return g_mouse;
}

CAJWindow* desktop()
{
    return CAJWindow::desktop();
}

void sleep(int ms)
{
    Sleep(ms);
}
