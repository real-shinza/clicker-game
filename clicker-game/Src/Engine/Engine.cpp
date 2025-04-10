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
    m_Renderer.Init(m_Window.GetHWND());
}

void Engine::Update()
{
    while (true)
    {
        if (m_Window.Update()) return;
        m_Renderer.Update();
    }
}

void Engine::Release()
{
    m_Renderer.Release();
}
