#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
public:
    Enemy(float x, float y);

    bool Update();

private:
    float m_lifespan;
    float m_posX;
    float m_posY;

public:
    float GetPosX() const { return m_posX; }
    float GetPosY() const { return m_posY; }
};

#endif
