#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"

class Engine
{
public:
    /// <summary>
    /// エンジン初期化
    /// </summary>
    void Init(HINSTANCE hInstance, int nCmdShow);

    /// <summary>
    /// エンジン更新
    /// </summary>
    void Update();

private:
    Window m_Window;
};

#endif
