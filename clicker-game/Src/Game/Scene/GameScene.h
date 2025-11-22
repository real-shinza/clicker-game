#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "SceneBase.h"
#include <sstream>
#include <chrono>

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
};

#endif
