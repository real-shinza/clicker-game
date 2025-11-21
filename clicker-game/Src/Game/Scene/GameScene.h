#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "SceneBase.h"

class GameScene : public SceneBase
{
public:
    GameScene(Graphic& graphic, Input& input) : SceneBase(graphic, input) {};

    SceneType Update() override;
    void Draw() override;
};

#endif
