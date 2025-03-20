#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"

class Engine
{
public:
    static void Initialize(HINSTANCE hInstance, int nCmdShow);
    static void Update();

    /// <summary>
    /// ウィンドウが閉じられたかどうかを返す
    /// </summary>
    static bool IsClosedWindow() { return instance->window->GetIsClosed(); }

private:
    static Engine* instance;

    Window* window;
};

#endif
