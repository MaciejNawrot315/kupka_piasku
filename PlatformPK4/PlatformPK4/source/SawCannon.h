#pragma once
#include "Wall.h"
class SawCannon: public Wall
{
private:
	sf::Clock shoot_clock;
	int kierunek;
	ResourceManager* Rmanager;
	class Player* player;
	std::vector<std::weak_ptr<Object>>* to_add_to_upd_obiekty;
	std::vector<std::shared_ptr<Object>>* obiekty_player_collision;
public:
	SawCannon(class ResourceManager* manager, float left, float top, int facing, class Player* pplayer, std::vector<std::weak_ptr<Object>>* upd_obiekty, std::vector<std::shared_ptr<Object>>* obiekty_player_collision);
	void update();
};

