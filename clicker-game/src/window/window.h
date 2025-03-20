#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>

class Window
{
public:
    Window(HINSTANCE hInstance, int nCmdShow);
    ~Window();

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    HWND hWnd;
    WNDCLASS wc;
};

#endif
