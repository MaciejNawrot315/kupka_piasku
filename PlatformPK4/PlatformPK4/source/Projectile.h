#pragma once
#include "Object.h"
class Projectile: public Object
{
private:
	sf::Vector2f velocity;
	bool to_delete;
public:

	Projectile(class ResourceManager* manager,const std::string& texture_name,float left, float top,sf::Vector2f v);
	void collision(Character*player);
	void update();
	 bool getDelete();
};

