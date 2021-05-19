#pragma once
#include "Character.h"
class Orange: public Character
{
private:
	sf::Clock collision_clock;
	sf::Clock rotate_clock;
	sf::Clock charge_clock;
	
	int kierunek;
	float start_pos;
	float przyspieszenie;
	class Player* player;

public:
	Orange(class ResourceManager* manager,float left, float top, class Player* pplayer);
	void move();
	void collision(Character* player);
	void update();
	
};

