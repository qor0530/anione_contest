#pragma once
#include "GameObject.h"
#include "ColliderManager.h"
class Bullet : public GameObject
{
public:
	Bullet(LPCWSTR filename);
public:
	void Move1();
	void Move2();
	void Attack(GameObject* obj);
};

