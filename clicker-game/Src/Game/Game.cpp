#include "Game.h"

Game::Game(Graphic& graphic) : m_graphic(graphic)
{
    ChangeScene(SceneType::Title);
}

void Game::Init()
{
    m_graphic.LoadTexture("Enemy", L"Assets/Img/Enemy.png");
}

void Game::Update()
{
    m_currentScene->Update();
}

void Game::Draw()
{
    m_currentScene->Draw();
}

void Game::ChangeScene(SceneType nextScene)
{
    switch (nextScene)
    {
    case SceneType::Title:
        m_currentScene = std::make_unique<TitleScene>(m_graphic);
        break;
    case SceneType::Game:
        m_currentScene = std::make_unique<GameScene>(m_graphic);
        break;
    case SceneType::Result:
        m_currentScene = std::make_unique<ResultScene>(m_graphic);
        break;
    }
}
