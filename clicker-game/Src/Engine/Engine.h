#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"
#include "Renderer.h"

class Engine
{
public:
    Engine();
    ~Engine();

    /// <summary>
    /// エンジン初期化
    /// </summary>
    void Init(HINSTANCE hInstance, int nCmdShow);

    /// <summary>
    /// エンジン更新
    /// </summary>
    void Update();

    /// <summary>
    /// エンジン解放
    /// </summary>
    void Release();

private:
    Window m_Window;
    Renderer m_Renderer;
};

#endif
