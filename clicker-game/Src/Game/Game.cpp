#include "Game.h"

Game::Game(Graphic& graphic, Input& input) : m_graphic(graphic), m_input(input)
{
    SceneType startScene = SceneType::Title;
    m_currentType = startScene;
    ChangeScene(startScene);
}

void Game::Init()
{
    m_graphic.LoadTexture("Enemy", L"Assets/Img/Enemy.png");
}

void Game::Update()
{
    SceneType next = m_currentScene->Update();
    if (next != m_currentType)
        ChangeScene(next);
}

void Game::Draw()
{
    m_currentScene->Draw();
}

void Game::ChangeScene(SceneType nextScene)
{
    m_currentType = nextScene;
    m_input.Init();

    switch (nextScene)
    {
    case SceneType::Title:
        m_currentScene = std::make_unique<TitleScene>(m_graphic, m_input);
        break;
    case SceneType::Game:
        m_currentScene = std::make_unique<GameScene>(m_graphic, m_input);
        break;
    case SceneType::Result:
        m_currentScene = std::make_unique<ResultScene>(m_graphic, m_input);
        break;
    }
}
