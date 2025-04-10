#include "Engine/Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    Engine engine;

    engine.Init(hInstance, nCmdShow);
    engine.Update();
    engine.Release();

    return 0;
}
