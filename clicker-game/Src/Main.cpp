#include "Engine/Engine.h"
#include "Game/Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Engine engine;
    Game game;

    if (!engine.Init(hInstance, nCmdShow))
        return 0;
    engine.Update(&game);

    return 0;
}
