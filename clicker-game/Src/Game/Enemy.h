#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
public:
    Enemy();
    ~Enemy();

    void Update();
    void Draw();

private:
    float m_Lifespan;
    int m_PosX;
    int m_PosY;

public:
    int GetPosX() const { return m_PosX; }
    int GetPosY() const { return m_PosY; }
};

#endif
