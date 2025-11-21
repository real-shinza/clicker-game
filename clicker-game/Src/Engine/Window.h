#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include "Input.h"

class Window
{
public:
    /// <summary>
    /// ウィンドウ初期化
    /// </summary>
    bool Init(HINSTANCE hInstance, int nCmdShow);

    /// <summary>
    /// ウィンドウ更新
    /// </summary>
    /// <returns>ウィンドウ閉じられたか</returns>
    bool Update(Input& m_input);

private:
    /// <summary>
    /// ウィンドウプロシージャ
    /// </summary>
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
    inline static const wchar_t* CLASS_NAME = L"Clicker Game";
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
};

#endif
