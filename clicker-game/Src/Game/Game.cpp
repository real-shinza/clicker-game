#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
    for (Enemy* enemy : enemies)
    {
        delete enemy;
    }
    enemies.clear();
}

void Game::Init()
{
    enemies.push_back(new Enemy());
}

void Game::Update()
{
    for (Enemy* enemy : enemies)
    {
        enemy->Update();
    }
}

void Game::Draw()
{
    for (Enemy* enemy : enemies)
    {
        enemy->Draw();
    }
}
