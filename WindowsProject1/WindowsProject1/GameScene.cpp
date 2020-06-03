#include "GameScene.h"

void GameScene::Init()
{
	Background = new GameObject(L"Background.png");
	player = new Player(L"player.png");
	for (int i = 0; i < 5; i++)
	{
		enemy[i] = new GameObject(L"enemy.png");
	}
	for (int i = 0; i < 5; i++)
	{
		enemy[i]->position = { 1000 + (float)100* i,500 };
	}
}

void GameScene::Update()
{
	player->Move();
	player->Shot();
	for (int i = 0; i < 5; i++)
	{
		player->BulletAttackCheck(enemy[i]);
	}
}

void GameScene::Render()
{
	GraphicManager::Render(Background);
	player->Render();
	GraphicManager::TextRender(L"hello", 0, 0);
	for (int i = 0; i < 5; i++)
	{
		GraphicManager::Render(enemy[i]);
	}
}

void GameScene::Release()
{
	delete player;
}
