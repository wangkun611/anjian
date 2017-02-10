#ifndef _KEYBOARD_H
#define _KEYBOARD_H

class CKeyboard
{
public:
    int getLastKey();
    void keyDown(int vkCode, int count = 1);
    bool keyPress(int vkCode, int count = 1);
    void keyUp(int vkCode, int count = 1);
};

#endif // _KEYBOARD_H
