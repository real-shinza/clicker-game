#include "Engine/Window.h"
#include "Engine/Graphic.h"
#include "Game/Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Window window;
    Graphic graphic;
    Game game(graphic);

    // 初期化
    if (!window.Init(hInstance, nCmdShow)) return 0;
    if (!graphic.Init()) return 0;
    game.Init();

    while (true)
    {
        if (window.Update()) break;

        // ゲーム処理
        game.Update();

        // 描画処理
        graphic.BeginRendering();
        game.Draw();
        graphic.EndRendering();
    }

    // メモリー解放
    graphic.Release();

    return 0;
}
