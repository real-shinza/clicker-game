#include "EnemiesManager.h"

EnemiesManager::EnemiesManager()
{
    Init();
}

EnemiesManager::~EnemiesManager()
{
    for (Enemy* enemy : m_pEnemies)
    {
        delete enemy;
    }
    m_pEnemies.clear();
}

void EnemiesManager::Init()
{
    m_pEnemies.push_back(new Enemy(0, 0));
    generateSpan = 0;
}

void EnemiesManager::Update()
{
    // エネミー生成
    GenerateEnemy();

    // エネミー更新
    for (auto it = m_pEnemies.begin(); it != m_pEnemies.end();)
    {
        if ((*it)->Update())
        {
            delete* it;
            it = m_pEnemies.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void EnemiesManager::GenerateEnemy()
{
    if (generateSpan-- > 0) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distSpan(30, 90);
    std::uniform_int_distribution<> distX(-Window::WINDOW_WIDTH / 2, Window::WINDOW_WIDTH / 2);
    std::uniform_int_distribution<> distY(-Window::WINDOW_HEIGHT / 2, Window::WINDOW_HEIGHT / 2);

    generateSpan = distSpan(gen);

    float x = distX(gen);
    float y = distY(gen);
    m_pEnemies.push_back(new Enemy(x, y));
}
