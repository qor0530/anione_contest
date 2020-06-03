#include "GameObject.h"

GameObject::GameObject(LPCWSTR filename)
{
	position = { 500, 500 };
	angle = 0.0;
	scale = { 1,1 };
	GraphicManager::Load_Bitmap(this, filename);
}

GameObject::~GameObject()
{
}
