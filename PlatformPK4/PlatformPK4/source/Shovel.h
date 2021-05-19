#pragma once
#include "PickUp.h"
class Shovel:public PickUp
{private:
	bool win;
public:
	Shovel(ResourceManager* manager, float left, float top);
	bool EndGame();
	void collision(class Character* character);
};

