#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"
#include "Graphic.h"
#include "../Game/Game.h"

class Engine
{
public:
    Engine();
    ~Engine();

    /// <summary>
    /// エンジン初期化
    /// </summary>
    bool Init(HINSTANCE hInstance, int nCmdShow);

    /// <summary>
    /// エンジン更新
    /// </summary>
    void Update(Game* game);

    /// <summary>
    /// エンジン解放
    /// </summary>
    void Release();

private:
    Window m_Window;
    Graphic m_Graphic;
};

#endif
