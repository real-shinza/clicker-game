#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
    m_SceneManager.Init();
}

void Game::Update()
{
    m_SceneManager.Update();
}

void Game::Draw()
{
    m_SceneManager.Draw();
}
