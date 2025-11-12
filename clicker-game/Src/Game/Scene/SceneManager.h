#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "TitleScene.h"
#include "GameScene.h"

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    void Init();
    void Update();
    void Draw();
    void ChangeScene(SceneType nextScene);

private:
    TitleScene m_TitleScene;
    GameScene m_GameScene;
    SceneType m_CurrentType;
};

enum class SceneType
{
    Title,
    Game,
    Result,
};

#endif
