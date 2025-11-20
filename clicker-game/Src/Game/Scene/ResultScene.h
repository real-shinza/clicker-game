#ifndef RESULT_SCENE_H
#define RESULT_SCENE_H

#include "SceneBase.h"

class ResultScene : public SceneBase
{
public:
    ResultScene(Graphic& graphic) : SceneBase(graphic) {};

    void Update() override;
    void Draw() override;
};

#endif
