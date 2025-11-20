#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "../../Engine/Graphic.h"

class SceneBase
{
public:
    SceneBase(Graphic& graphic) : m_graphic(graphic) {};
    virtual ~SceneBase() = default;

    virtual void Update() = 0;
    virtual void Draw() = 0;

protected:
    Graphic& m_graphic;
};

#endif
