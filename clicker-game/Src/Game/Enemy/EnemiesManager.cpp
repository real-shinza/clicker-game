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

void EnemiesManager::ReduceLifespan()
{
    for (Enemy* enemy : m_pEnemies)
    {
        enemy->ReduceLifespan();
    }
}

bool EnemiesManager::CheckHit(float x, float y)
{
    for (Enemy* enemy : m_pEnemies)
    {
        if (enemy->IsHit(x, y))
            return true;
    }
    return false;
}

void EnemiesManager::CheckDie()
{
    for (auto enemy = m_pEnemies.begin(); enemy != m_pEnemies.end();)
    {
        if ((*enemy)->GetIsDie())
        {
            delete* enemy;
            enemy = m_pEnemies.erase(enemy);
        }
        else
        {
            ++enemy;
        }
    }
}
