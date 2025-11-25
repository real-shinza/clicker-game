#include "ResultScene.h"

SceneType ResultScene::Update()
{
    if (m_input.GetIsMousePressed())
        return SceneType::Title;
    return SceneType::Result;
}

void ResultScene::Draw()
{
    m_graphic.DrawString(L"画面クリックでタイトルへ戻る", 176, 276, D2D1::ColorF::Black);
}
