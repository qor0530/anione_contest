#include "ColliderManager.h"

bool ColliderManager::BoxCollider(GameObject * obj1, GameObject * obj2)
{
	RECT temp;
	RECT rc1 = {
		obj1->position.x - obj1->pBitmap->GetPixelSize().width / 2 * obj1->scale.x,
		obj1->position.y - obj1->pBitmap->GetPixelSize().height / 2 * obj1->scale.y,
		obj1->position.x + obj1->pBitmap->GetPixelSize().width / 2 * obj1->scale.x,
		obj1->position.y + obj1->pBitmap->GetPixelSize().height / 2 * obj1->scale.y,
	};
	RECT rc2 = {
		obj2->position.x - obj2->pBitmap->GetPixelSize().width / 2 * obj2->scale.x,
		obj2->position.y - obj2->pBitmap->GetPixelSize().height / 2 * obj2->scale.y,
		obj2->position.x + obj2->pBitmap->GetPixelSize().width / 2 * obj2->scale.x,
		obj2->position.y + obj2->pBitmap->GetPixelSize().height / 2 * obj2->scale.y,
	};
	return IntersectRect(&temp, &rc1, &rc2);
}
