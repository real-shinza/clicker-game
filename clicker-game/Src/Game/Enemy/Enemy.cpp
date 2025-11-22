#include "Enemy.h"

Enemy::Enemy(float x, float y)
{
    m_lifespan = 480;
    m_posX = x;
    m_posY = y;
}

bool Enemy::Update()
{
    if (m_lifespan-- <= 0)
        return true;

    return false;
}
