#pragma once
#include "Wall.h"
class Spikes : public Wall
{
public:
	Spikes(class ResourceManager* manager, float left, float top, int width);
	void collision(class Character* player);
};