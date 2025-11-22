#ifndef ENEMIES_MANAGER_H
#define ENEMIES_MANAGER_H

#include <list>
#include <iostream>
#include <random>
#include "Enemy.h"
#include "../../Engine/Window.h"

class EnemiesManager
{
public:
    EnemiesManager();
    ~EnemiesManager();

    void Init();
    void Update();

private:
    void GenerateEnemy();

public:
    std::list<Enemy*> GetEnemies() { return m_pEnemies; }

private:
    std::list<Enemy*> m_pEnemies;
    int generateSpan;
};

#endif
