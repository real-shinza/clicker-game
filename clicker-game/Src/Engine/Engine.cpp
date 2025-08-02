#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
    Release();
}

bool Engine::Init(HINSTANCE hInstance, int nCmdShow)
{
    m_Window.Init(hInstance, nCmdShow);
    if (!m_Graphic.Init(m_Window.GetHWND()))
        return false;
    return true;
}

void Engine::Update(Game* game)
{
    while (true)
    {
        if (m_Window.Update()) return;
        game->Update();
        m_Graphic.Render(game);
    }
}

void Engine::Release()
{
    m_Graphic.Release();
}
