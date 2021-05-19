#pragma once
#include "PickUp.h"
class Heart: public PickUp
{
public:
	Heart(ResourceManager* manager, float left, float top);
	void collision(class Character* character);
};

