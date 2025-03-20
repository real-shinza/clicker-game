#include "Window.h"

Window::Window(HINSTANCE hInstance, int nCmdShow)
{
    isClosed = false;

    wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"Clicker Game";
    RegisterClass(&wc);

    hWnd = CreateWindow(
        wc.lpszClassName,
        L"Clicker Game",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        600,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    
    );
    ShowWindow(hWnd, nCmdShow);
}

Window::~Window()
{
    UnregisterClass(wc.lpszClassName, wc.hInstance);
}

void Window::Update()
{
    MSG message;
    if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
    {
        if (message.message == WM_QUIT)
        {
            isClosed = true;
        }
        else
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
