#include "Engine/Engine.h"
#include "Game/Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Engine engine;
    Game game;

    if (!engine.Init(hInstance, nCmdShow))
        return 0;
    game.Init();
    engine.Update(&game);
    engine.Release();

    return 0;
}
