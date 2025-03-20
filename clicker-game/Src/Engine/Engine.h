#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"

class Engine
{
public:
    static void Initialize(HINSTANCE hInstance, int nCmdShow);
    static void Update();

    /// <summary>
    /// �E�B���h�E������ꂽ���ǂ�����Ԃ�
    /// </summary>
    static bool IsClosedWindow() { return instance->window->GetIsClosed(); }

private:
    static Engine* instance;

    Window* window;
};

#endif
