#include "window.h"
#include <atlbase.h>
#include <atlconv.h>
#include <atlwin.h>
#include <atlstr.h>

using namespace std;
using namespace ATL;
CAJWindow* CAJWindow::desktop()
{
    return new CAJWindow(NULL);
}

CAJWindow* CAJWindow::childByName(std::string name)
{
    HWND hWnd = FindWindowExW(hWnd_, NULL, NULL, ATL::CA2W(name.c_str(), CP_UTF8));
    if (hWnd) {
        return new CAJWindow(hWnd);
    }
    return NULL;
}

CAJWindow* CAJWindow::childByClass(std::string className)
{
    HWND hWnd = FindWindowExW(hWnd_, NULL, ATL::CA2W(className.c_str(), CP_UTF8), NULL);
    if (hWnd) {
        return new CAJWindow(hWnd);
    }
    return NULL;
}

CAJWindow* CAJWindow::childById(int id)
{
    CWindow wnd(hWnd_);
    CWindow child = wnd.GetDlgItem(id);
    if (child.m_hWnd) {
        return new CAJWindow(child.m_hWnd);
    }

    return NULL;
}

std::vector<CAJWindow> CAJWindow::children()
{
    std::vector<CAJWindow> v;

    HWND hwndChild = FindWindowExW(hWnd_, NULL, NULL, NULL);
    while (hwndChild) {
        v.push_back(CAJWindow(hwndChild));
        hwndChild = FindWindowExW(hWnd_, hwndChild, NULL, NULL);
    }
    return v;
}

std::string CAJWindow::name()
{
    CWindow wnd(hWnd_);

    CString rString;
    wnd.GetWindowText(rString);

    return string(CW2A(rString, CP_UTF8));
}
std::string CAJWindow::className()
{
    CString rString;
    GetClassName(hWnd_, rString.GetBuffer(256), 255);
    rString.ReleaseBuffer();

    return string(CW2A(rString, CP_UTF8));
}

int CAJWindow::id()
{
    CWindow wnd(hWnd_);

    return wnd.GetDlgCtrlID();
}

RECT  CAJWindow::windowRect()
{
    CWindow wnd(hWnd_);

    RECT rect{0};
    wnd.GetWindowRect(&rect);

    return rect;
}

RECT  CAJWindow::clientRect()
{
    CWindow wnd(hWnd_);

    RECT rect{ 0 };
    wnd.GetClientRect(&rect);

    return rect;
}
