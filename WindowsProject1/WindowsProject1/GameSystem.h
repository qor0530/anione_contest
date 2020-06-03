#pragma once
#include "GameObject.h"
#include "GraphicManager.h"
#include "Scene.h"
#include "GameScene.h"
#include "MainScene.h"
enum SCENETYPE
{
	INTRO,
	MAIN,
	GAME,
	SCORE
};

class GameSystem
{
private:
	Scene * scene = nullptr;
	int current_Scene_number;
public:
	void Init();
	void Update();
	void Render();
	void Release();
	void SetScene(int sceneNumber);
	void SceneChangeCheck();
	static bool GameExit;
	static int change_Scene_number;
};

