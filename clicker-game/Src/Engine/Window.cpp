#include "Window.h"

void Window::Init(HINSTANCE hInstance, int nCmdShow)
{
    // ウィンドウクラスの登録
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);     // 構造体のサイズ
    wc.style = CS_HREDRAW | CS_VREDRAW; // クラスのスタイル
    wc.lpfnWndProc = WndProc;           // ウィンドウプロシージャへのポインター
    wc.hInstance = hInstance;           // インスタンスへのハンドル
    wc.lpszClassName = L"Clicker Game"; // クラス名
    RegisterClassEx(&wc);

    // ウィンドウを作成
    m_hWnd = CreateWindowEx(
        0,                      // 拡張ウィンドウスタイル
        wc.lpszClassName,       // ウィンドウクラス
        L"Clicker Game",        // ウィンドウ名
        WS_OVERLAPPEDWINDOW,    // ウィンドウスタイル
        CW_USEDEFAULT,          // X座標
        CW_USEDEFAULT,          // Y座標
        800,                    // 幅
        600,                    // 高さ
        nullptr,                // 親ウィンドウ
        nullptr,                // メニュー
        hInstance,              // インスタンスハンドル
        nullptr                 // 追加パラメーター
    );

    // ウィンドウを表示
    ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd);
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
            TranslateMessage(&msg); // キー入力メッセージの前処理
            DispatchMessage(&msg);  // ウィンドウプロシージャに渡す
        }
    }
    return false;
}

LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DESTROY)
    {
        // メッセージループに終了を伝達
        PostQuitMessage(0);
        return 0;
    }
    // デフォルトのウィンドウ処理
    return DefWindowProc(hWnd, message, wParam, lParam);
}
