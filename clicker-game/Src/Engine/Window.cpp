#include "Window.h"

void Window::Init(HINSTANCE hInstance, int nCmdShow)
{
    // ウィンドウクラスの登録
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = Window::CLASS_NAME;
    RegisterClassEx(&wc);

    // ウィンドウを作成
    HWND hWnd = CreateWindow(
        wc.lpszClassName,
        Window::CLASS_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        Window::WINDOW_WIDTH,
        Window::WINDOW_HEIGHT,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    // ウィンドウを表示
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
}

bool Window::Update()
{
    MSG msg;
    // メッセージがあれば取得
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        // 終了メッセージなら
        if (msg.message == WM_QUIT)
        {
            return true;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return false;
}

LRESULT Window::WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    if (nMsg == WM_DESTROY)
    {
        // メッセージループに終了を伝達
        PostQuitMessage(0);
        return 0;
    }
    // デフォルトのウィンドウ処理
    return DefWindowProc(hWnd, nMsg, wParam, lParam);
}
