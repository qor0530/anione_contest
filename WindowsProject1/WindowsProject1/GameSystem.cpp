#include "GameSystem.h"

bool GameSystem::GameExit = false;
int	 GameSystem::change_Scene_number;

void GameSystem::Init()
{
	SetScene(SCENETYPE::MAIN);
}

void GameSystem::Update()
{
	scene->Update();
}

void GameSystem::Render()
{
	scene->Render();
}


void GameSystem::Release()
{
	scene->Release();
	delete scene;
}

void GameSystem::SetScene(int sceneNumber)
{
	current_Scene_number = sceneNumber;
	change_Scene_number = sceneNumber;
	if (scene != nullptr)
	{
		scene->Release();
		delete scene;
	}
	switch (sceneNumber)
	{
	case SCENETYPE::INTRO:
		break;
	case SCENETYPE::MAIN:
		scene = new MainScene();
		break;
	case SCENETYPE::GAME:
		scene = new GameScene();
		break;
	case SCENETYPE::SCORE:
		break;
	}
	if (scene != nullptr)
	{
		scene->Init();
	}
}

void GameSystem::SceneChangeCheck()
{
	if (current_Scene_number != change_Scene_number)
	{
		SetScene(change_Scene_number);
	}
}
