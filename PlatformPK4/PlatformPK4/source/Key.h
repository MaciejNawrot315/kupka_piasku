#pragma once
#include "PickUp.h"
class Key: public PickUp
{
public:
	Key(ResourceManager* manager, float left, float top);
	void collision(class Character* character);
};

