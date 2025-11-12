#ifndef ENEMIES_MANAGER_H
#define ENEMIES_MANAGER_H

#include <list>
#include "Enemy.h"

class EnemiesManager
{
public:
    EnemiesManager();
    ~EnemiesManager();

    void Init();
    void Update();
    void Draw();

private:
    std::list<Enemy*> m_Enemies;
};

#endif
