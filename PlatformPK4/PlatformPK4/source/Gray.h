#pragma once
#include "Character.h"
class Gray: public Character
{
private:
	sf::Clock rotate_clock;
	sf::Clock collision_clock;
	sf::Clock shoot_clock;
	int kierunek;
	float start_pos;
	float przyspieszenie;
	
	ResourceManager* Rmanager;
	class Player* player;
	std::vector<std::weak_ptr<Object>>* upd_obiekty;
	std::vector<std::shared_ptr<Object>>* obiekty_player_collision;
public:
	Gray(class ResourceManager* manager, float left, float top, class Player* pplayer, std::vector<std::weak_ptr<Object>>* upd_obiekty, std::vector<std::shared_ptr<Object>>* obiekty_player_collision,int facing);
	void move();
	void collision(Character* player);
	void update();

};

