#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "SceneBase.h"

class GameScene : public SceneBase
{
public:
    GameScene(Graphic& graphic) : SceneBase(graphic) {};

    void Update() override;
    void Draw() override;
};

#endif
