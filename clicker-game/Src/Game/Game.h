#ifndef GAME_H
#define GAME_H

#include <memory>
#include "../Engine/Graphic.h"
#include "../Engine/Input.h"
#include "Scene/SceneBase.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"
#include "Scene/ResultScene.h"

class Game
{
public:
    Game(Graphic& graphic, Input& input);

    void Init();
    void Update();
    void Draw();

private:
    void ChangeScene(SceneType nextScene);

private:
    SceneType m_currentType;
    Graphic& m_graphic;
    Input& m_input;
    std::unique_ptr<SceneBase> m_currentScene;
};

#endif
