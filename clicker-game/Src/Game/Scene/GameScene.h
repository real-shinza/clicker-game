#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <sstream>
#include <iomanip>
#include <chrono>
#include "SceneBase.h"
#include "../Enemy/EnemiesManager.h"

class GameScene : public SceneBase
{
public:
    GameScene(Graphic& graphic, Input& input);

    SceneType Update() override;
    void Draw() override;

private:
    std::chrono::steady_clock::time_point m_startTime;
    double m_timeLimit;
    int m_remaining;
    EnemiesManager m_pEnemies;
    int m_killCount;
};

#endif
