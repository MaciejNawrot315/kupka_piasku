#include "Character.h"
Character::Character(ResourceManager* manager, const std::string& texture_name, float left, float top,int health):Object(manager, texture_name, left, top), health(health),IsAlive(true),animation_state(0)
{
}
void Character::setHealth(int ile)
{
	health += ile;
	if (health <= 0)
		IsAlive = false;
}

int Character::getHealth()
{
	return health;
}

bool Character::IsDead()
{
	return !IsAlive;
}

void Character::animate()
{

	if (animation_state >= 4) { animation_state = 0; }

	current_frame = { 0 + hitbox_size.x * animation_state, 0, hitbox_size.x, hitbox_size.y };
	animation_state++;
	sprite.setTextureRect(current_frame);
	animation_clock.restart();
}
