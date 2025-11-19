#include "Engine/Window.h"
#include "Engine/Graphic.h"
#include "Game/Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Window window;
    Graphic graphic;
    Game game;

    // 初期化
    if (!window.Init(hInstance, nCmdShow)) return 0;
    if (!graphic.Init()) return 0;
    game.Init();

    // テクスチャ読み込み
    graphic.LoadTexture("Enemy", L"Assets/Img/Enemy.png");

    while (true)
    {
        if (window.Update()) break;

        // ゲーム処理
        game.Update();

        // 描画処理
        graphic.BeginRendering();
        game.Draw();
        graphic.DrawTexture("Enemy", 0.0f, 0.0f);
        graphic.EndRendering();
    }

    // メモリー解放
    graphic.Release();

    return 0;
}
