#include "Player.h"

Player::Player(LPCWSTR filename) : GameObject(filename)
{
	for (int i = 0; i < 10; i++)
	{
		bullet[i] = new Bullet(L"bullet.png");
	}
	currentBullet = 0;
}

void Player::Move()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		position.x += 5;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		position.y -= 5;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		position.x -= 5;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		position.y += 5;
	}
}

void Player::Shot()
{
	if (GetTickCount() - bulletTime > 100)
	{
		
		bulletTime = GetTickCount();
		if (GetAsyncKeyState(0x41) & 0x8001)
		{
			mciSendString(L"Play ShotSound.mp3", 0, 0, 0);
			currentBullet %= 10;
			bullet[currentBullet++]->position = position;
			
		}
	}
	for (int i = 0; i < 10; i++)
	{
		bullet[i]->Move1();
	}
}

void Player::Render()
{
	for (int i = 0; i < 10; i++)
	{
		GraphicManager::Render(bullet[i]);
	}
	GraphicManager::Render(this);
}

void Player::BulletAttackCheck(GameObject * obj)
{
	for (int i = 0; i < 10; i++)
	{
		bullet[i]->Attack(obj);
	}
}
