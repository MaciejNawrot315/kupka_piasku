#include "Projectile.h"
#include "Character.h"
Projectile::Projectile(class ResourceManager* manager, const std::string& texture_name, float left, float top, sf::Vector2f v) : Object(manager, texture_name, left, top), velocity(v), to_delete(false)
{
	sprite.setOrigin(7.f, 7.f);
}

void Projectile::collision(Character* character)
{
	to_delete = true;
	character->setHealth(-1);
}

void Projectile::update()
{
	sprite.move(velocity);
	sprite.rotate(velocity.x);
	
}

bool Projectile::getDelete()
{
	return to_delete;
}
