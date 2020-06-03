#pragma once
#include "Scene.h"
#include "Player.h"
class GameScene : public Scene
{
private:
	GameObject * Background;
	Player* player;
	GameObject * enemy[5];
public:
	void Init();
	void Update();
	void Render();
	void Release();
};

