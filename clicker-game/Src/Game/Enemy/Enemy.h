#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
public:
    Enemy(float x, float y);

    void ReduceLifespan();
    bool IsHit(float x, float y);

private:
    float m_lifespan;
    float m_posX;
    float m_posY;
    bool m_isDie;

public:
    inline static const float WIDTH = 64;
    inline static const float HEIGHT = 64;

public:
    float GetPosX() const { return m_posX; }
    float GetPosY() const { return m_posY; }
    bool GetIsDie() const { return m_isDie; }
};

#endif
