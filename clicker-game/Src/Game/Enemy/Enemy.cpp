#include "Enemy.h"

Enemy::Enemy(float x, float y)
{
    m_lifespan = 200;
    m_posX = x;
    m_posY = y;
    m_isDie = false;
}

void Enemy::ReduceLifespan()
{
    if (m_lifespan-- <= 0)
        m_isDie = true;
}

bool Enemy::IsHit(float x, float y)
{
    float left = m_posX - (WIDTH / 2.0f);
    float right = m_posX + (WIDTH / 2.0f);
    float top = m_posY + (HEIGHT / 2.0f);
    float bottom = m_posY - (HEIGHT / 2.0f);
    bool isHit = x >= left && x <= right && y <= top && y >= bottom;
    if (isHit)
        m_isDie = true;
    return isHit;
}
