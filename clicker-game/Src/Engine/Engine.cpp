#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Init(HINSTANCE hInstance, int nCmdShow)
{
    m_Window.Init(hInstance, nCmdShow);
    m_Graphic.Init(m_Window.GetHWND());
}

void Engine::Update(Game* game)
{
    while (true)
    {
        if (m_Window.Update()) return;
        game->Update();
        m_Graphic.Update();
    }
}

void Engine::Release()
{
    m_Graphic.Release();
}
