#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:
    TitleScene(Graphic& graphic) : SceneBase(graphic) {};

    void Update() override;
    void Draw() override;
};

#endif
