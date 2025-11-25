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
    srand((unsigned int)time(NULL));
    generateSpan = 0;
}

void EnemiesManager::GenerateEnemy()
{
    if (generateSpan-- > 0) return;

    generateSpan = rand() % 70 + 10;

    float x = rand() % (int)(Window::WINDOW_WIDTH - Enemy::WIDTH);
    float y = rand() % (int)(Window::WINDOW_HEIGHT - Enemy::HEIGHT);
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
