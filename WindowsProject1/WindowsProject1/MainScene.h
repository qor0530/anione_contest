#pragma once
#include "Scene.h"
#include "GraphicManager.h"
#include "GameObject.h"
#include "GameSystem.h"
class MainScene : public Scene
{
private:
	GameObject* SelectUI;
	GameObject* mainUI[3];
	bool downchk = false;
	int cnt;

public:
	void Init();
	void Update();
	void Render();
	void Release();
	void PlayUI();
};

