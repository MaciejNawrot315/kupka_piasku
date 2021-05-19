#pragma once
#include "Object.h"
class Character: public Object
{protected:
	int health;
	bool IsAlive;
	sf::Clock animation_clock;
	sf::IntRect current_frame;
	int animation_state;
	sf::Vector2i hitbox_size;
public:
	Character(class ResourceManager* manager, const std::string& texture_name, float left, float top,int health);
	 virtual void setHealth(int ile);
	int getHealth();
	bool IsDead();
	void animate();
};

