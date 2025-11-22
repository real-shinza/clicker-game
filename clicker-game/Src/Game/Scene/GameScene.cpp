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

    m_pEnemies.Update();

    if (m_remaining <= 0)
        return SceneType::Result;
    return SceneType::Game;
}

void GameScene::Draw()
{
    std::wstringstream time;
    time << L"残り" << m_remaining << L"秒";
    m_graphic.DrawString(time.str(), 300.0f, 270.0f, D2D1::ColorF::Black);
    for (Enemy* enemy : m_pEnemies.GetEnemies())
    {
        m_graphic.DrawTexture("Enemy", enemy->GetPosX(), enemy->GetPosY());
    }
}
