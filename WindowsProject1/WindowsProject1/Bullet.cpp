#include "Bullet.h"

Bullet::Bullet(LPCWSTR filename) : GameObject(filename)
{
}

void Bullet::Move1()
{ 
	position.y -= 7;
	scale = { 0.5f, 0.5f };
}
void Bullet::Move2()
{
	position.y -= 5;
	scale = { 0.5f, 0.5f };
}

void Bullet::Attack(GameObject * obj)
{
	if (ColliderManager::BoxCollider(this, obj))
	{
		if (obj->exist == true)
		{
			mciSendString(L"Play Enemy_Dead.mp3", 0, 0, 0);
			this->exist = false;
		}
		obj->exist = false;
		
	}
}
