#include <windows.h>
#include "Engine/Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    Engine::Initialize(hInstance, nCmdShow);

	while (Engine::IsClosedWindow() == false)
	{
		Engine::Update();
	}

    return 0;
}
