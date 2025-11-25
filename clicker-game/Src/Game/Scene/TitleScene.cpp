#include "TitleScene.h"

SceneType TitleScene::Update()
{
    if (m_input.GetIsMousePressed())
        return SceneType::Game;
    return SceneType::Title;
}

void TitleScene::Draw()
{
    m_graphic.DrawString(L"画面クリックでゲーム開始", 208, 276, D2D1::ColorF::Black);
}
