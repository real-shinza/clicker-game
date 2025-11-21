#include "GameScene.h"

SceneType GameScene::Update()
{
    return SceneType::Game;
}

void GameScene::Draw()
{
    m_graphic.DrawTexture("Enemy", 0.0f, 0.0f);
}
