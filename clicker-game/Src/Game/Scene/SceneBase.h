#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "../../Engine/Graphic.h"
#include "../../Engine/Input.h"

enum class SceneType
{
    Title,
    Game,
    Result,
};

class SceneBase
{
public:
    SceneBase(Graphic& graphic, Input& input) : m_graphic(graphic), m_input(input) {};
    virtual ~SceneBase() = default;

    virtual SceneType Update() = 0;
    virtual void Draw() = 0;

protected:
    Graphic& m_graphic;
    Input& m_input;
};

#endif
