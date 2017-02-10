#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>
#include <vector>

class CAJWindow
{
protected:
    CAJWindow(HWND hWnd) :hWnd_(hWnd)
    {
    }
public:
    CAJWindow():hWnd_(NULL)
    {}
    CAJWindow(const CAJWindow& that):hWnd_(that.hWnd_)
    {}
public:
    static CAJWindow* desktop();

    // 获取子窗口
    CAJWindow* childByName(std::string name);
    CAJWindow* childByClass(std::string className);
    CAJWindow* childById(int id);
    std::vector<CAJWindow> children();

    // 获取窗口属性
    std::string name();
    std::string className();
    int id();
    RECT  windowRect();
    RECT  clientRect();

protected:
    HWND   hWnd_ = NULL;
};

#endif // _WINDOW_H_
