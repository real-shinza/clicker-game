#include "GameScene.h"

GameScene::GameScene(Graphic& graphic, Input& input) : SceneBase(graphic, input)
{
    m_startTime = std::chrono::steady_clock::now();
    m_timeLimit = 60;
    m_remaining = 0;
    m_killCount = 0;
}

SceneType GameScene::Update()
{
    // カウントダウン
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - m_startTime;
    m_remaining = static_cast<int>(m_timeLimit - elapsed.count());

    // エネミー処理
    m_pEnemies.GenerateEnemy();
    m_pEnemies.ReduceLifespan();
    float x = m_input.GetMousePos().x - (Window::WINDOW_WIDTH / 2.0f);
    float y = (Window::WINDOW_HEIGHT / 2.0f) - m_input.GetMousePos().y;
    if (m_input.GetIsMousePressed() && m_pEnemies.CheckHit(x, y))
        m_killCount++;
    m_pEnemies.CheckDie();

    if (m_remaining <= 0)
        return SceneType::Result;
    return SceneType::Game;
}

void GameScene::Draw()
{
    // エネミーを描画
    for (Enemy* enemy : m_pEnemies.GetEnemies())
    {
        m_graphic.DrawTexture("Enemy", enemy->GetPosX(), enemy->GetPosY());
    }

    // 残り時間を描画
    std::wstringstream time;
    time << L"残り" << m_remaining << L"秒";
    m_graphic.DrawString(time.str(), 330.0f, 230.0f, D2D1::ColorF::Black);

    // 倒した数を描画
    std::wstringstream killCount;
    killCount << L"クリックした数：" << std::setw(2) << std::setfill(L'0') << m_killCount;
    m_graphic.DrawString(killCount.str(), 250.0f, 270.0f, D2D1::ColorF::Black);
}
