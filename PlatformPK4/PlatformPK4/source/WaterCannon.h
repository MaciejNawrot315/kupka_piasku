#pragma once
#include "Wall.h"
class WaterCannon: public Wall
{
private:
	sf::Clock change_clock;
	int state;
	sf::Vector2f start_pos;
public:
	WaterCannon(class ResourceManager* manager, float left, float top);
	void collision(class Character* player);
	void update();
};

