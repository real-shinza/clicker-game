#include "Engine/Engine.h"
#include "Game/Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    Engine engine;
    Game game;

    engine.Init(hInstance, nCmdShow);
    engine.Update(&game);
    engine.Release();

    return 0;
}
