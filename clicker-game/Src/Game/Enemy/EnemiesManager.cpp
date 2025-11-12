#include "EnemiesManager.h"

EnemiesManager::EnemiesManager()
{
}

EnemiesManager::~EnemiesManager()
{
    for (Enemy* enemy : m_Enemies)
    {
        delete enemy;
    }
    m_Enemies.clear();
}

void EnemiesManager::Init()
{
    m_Enemies.push_back(new Enemy());
}

void EnemiesManager::Update()
{
    for (Enemy* enemy : m_Enemies)
    {
        enemy->Update();
    }
}

void EnemiesManager::Draw()
{
    for (Enemy* enemy : m_Enemies)
    {
        enemy->Draw();
    }
}
