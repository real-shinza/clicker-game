#ifndef GAME_H
#define GAME_H

#include <memory>
#include "../Engine/Graphic.h"
#include "Scene/SceneBase.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"
#include "Scene/ResultScene.h"

enum class SceneType
{
    Title,
    Game,
    Result,
};

class Game
{
public:
    Game(Graphic& graphic);

    void Init();
    void Update();
    void Draw();

private:
    void ChangeScene(SceneType nextScene);

private:
    Graphic& m_graphic;
    std::unique_ptr<SceneBase> m_currentScene;
};

#endif
