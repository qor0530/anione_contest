#include "MainScene.h"

void MainScene::Init()
{
	SelectUI = new GameObject(L"ȭ��ǥ.png");

	mainUI[0] = new  GameObject(L"���ӽ���.png");
	mainUI[1] = new  GameObject(L"��ŷ.png");
	mainUI[2] = new  GameObject(L"���ӳ�.png");
	

	SelectUI->position = {0, 0 }; //���� �ϰų� �ᵵ ������� 
	SelectUI->scale = { 0.2f, 0.2f };
	for (int i = 0; i < 3; i++)
	{
		mainUI[i]->position = { 1000,300 + (float)250 * i };
		mainUI[i]->scale = { 1,0.5f };
	}
	mciSendString(L"Play ����.mp3", 0, 0, 0);
}

void MainScene::Update()
{
	PlayUI();
}

void MainScene::Render()
{
	GraphicManager::Render(SelectUI);
	for (int i = 0; i < 3; i++)
	{
		GraphicManager::Render(mainUI[i]);
	}
}

void MainScene::Release()
{
}

void MainScene::PlayUI()
{
	if (GetAsyncKeyState(VK_DOWN) & 0x0001 && cnt < 2)
	{
		cnt++;
	}
	if (GetAsyncKeyState(VK_UP) & 0x0001 && cnt > 0)
	{
		cnt--;
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		switch (cnt)
		{
		case 0:
			GameSystem::change_Scene_number = GAME;
			break;
		case 1:
			break;
		case 2:
			GameSystem::GameExit = true;
			break;
		}
	}
	SelectUI->position = { 400, 300 + (float)250 * cnt };
}
