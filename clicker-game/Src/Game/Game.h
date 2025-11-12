#ifndef GAME_H
#define GAME_H

#include "Scene/SceneManager.h"

class Game
{
public:
    Game();
    ~Game();

    void Init();
    void Update();
    void Draw();

private:
    SceneManager m_SceneManager;
};

#endif
