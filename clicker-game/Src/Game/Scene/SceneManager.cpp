#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
    m_CurrentType = SceneType::Title;
}

void SceneManager::Update()
{
    switch (m_CurrentType)
    {
    case SceneType::Title:
        m_TitleScene.Update();
        break;
    case SceneType::Game:
        m_GameScene.Update();
        break;
    case SceneType::Result:
        break;
    }
}

void SceneManager::Draw()
{
    switch (m_CurrentType)
    {
    case SceneType::Title:
        m_TitleScene.Draw();
        break;
    case SceneType::Game:
        m_GameScene.Draw();
        break;
    case SceneType::Result:
        break;
    }
}

void SceneManager::ChangeScene(SceneType nextScene)
{
    m_CurrentType = nextScene;
}
