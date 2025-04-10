#ifndef GAME_H
#define GAME_H

#include <list>
#include "Enemy.h"

class Game
{
public:
    Game();
    ~Game();

    void Init();
    void Update();
    void Draw();

private:
    std::list<Enemy*> enemies;
};

#endif
