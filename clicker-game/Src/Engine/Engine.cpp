#include "Engine.h"

void Engine::Init(HINSTANCE hInstance, int nCmdShow)
{
    m_Window.Init(hInstance, nCmdShow);
}

void Engine::Update()
{
    while (true)
    {
        if (m_Window.Update()) return;
    }
}
