#include "ResultScene.h"

SceneType ResultScene::Update()
{
    if (m_input.GetIsMousePressed())
        return SceneType::Title;
    return SceneType::Result;
}

void ResultScene::Draw()
{
    m_graphic.DrawString(L"画面クリックでタイトルへ戻る", 0.0f, 0.0f, D2D1::ColorF::Black);
}
