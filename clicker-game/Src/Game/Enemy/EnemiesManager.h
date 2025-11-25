#ifndef ENEMIES_MANAGER_H
#define ENEMIES_MANAGER_H

#include <list>
#include <random>
#include "Enemy.h"
#include "../../Engine/Window.h"

class EnemiesManager
{
public:
    EnemiesManager();
    ~EnemiesManager();

    void Init();
    void GenerateEnemy();
    void ReduceLifespan();
    bool CheckHit(float x, float y);
    void CheckDie();

public:
    std::list<Enemy*> GetEnemies() { return m_pEnemies; }

private:
    std::list<Enemy*> m_pEnemies;
    int generateSpan;
};

#endif
