#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>

class Window
{
public:
    /// <summary>
    /// ウィンドウ初期化
    /// </summary>
    void Init(HINSTANCE hInstance, int nCmdShow);

    /// <summary>
    /// ウィンドウ更新
    /// </summary>
    /// <returns>ウィンドウ閉じられたか</returns>
    bool Update();

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    HWND m_hWnd;
};

#endif
