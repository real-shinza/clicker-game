#include <stdio.h>
#include "Engine.h"

Engine* Engine::instance = nullptr;

 void Engine::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	instance = new Engine();
	instance->window = new Window(hInstance, nCmdShow);
}

 void Engine::Update()
 {
	 instance->window->Update();
 }
