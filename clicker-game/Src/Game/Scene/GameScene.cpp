#include "GameScene.h"

GameScene::GameScene(Graphic& graphic, Input& input) : SceneBase(graphic, input)
{
    m_startTime = std::chrono::steady_clock::now();
    m_timeLimit = 60;
    m_remaining = 0;
}

SceneType GameScene::Update()
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - m_startTime;
    m_remaining = static_cast<int>(m_timeLimit - elapsed.count());

    if (m_remaining <= 0)
        return SceneType::Result;
    return SceneType::Game;
}

void GameScene::Draw()
{
    std::wstringstream time;
    time << L"残り" << m_remaining << L"秒";
    m_graphic.DrawString(time.str(), 200.0f, 200.0f, D2D1::ColorF::Black);
    m_graphic.DrawTexture("Enemy", 0.0f, 0.0f);
}
