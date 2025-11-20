#include "TitleScene.h"

void TitleScene::Update()
{
}

void TitleScene::Draw()
{
    m_graphic.DrawString(L"Start", 0.0f, 0.0f, D2D1::ColorF(D2D1::ColorF::Black));
}
