#include "Orange.h"
#include "ResourceManager.h"
#include "Player.h"
#include <cmath>
Orange::Orange(ResourceManager* manager, float left, float top,Player* pplayer) : Character(manager, "orange", left, top,20), kierunek(1), start_pos(left),przyspieszenie(1)
{
	
	collision_clock.restart();
	player = pplayer;
	hitbox_size = { 60,35 };
	current_frame = { 0,0,60,35 };
	sprite.setScale(kierunek*(-1), 1);
	sprite.setTextureRect(current_frame);
}

void Orange::move()
{
	if ((std::abs(sprite.getPosition().x - start_pos) > 250)&& (rotate_clock.getElapsedTime().asMilliseconds() >= 100))
	{
		sprite.setScale(kierunek, 1);
		kierunek *= -1;
		przyspieszenie = 1;
		rotate_clock.restart();
		charge_clock.restart();
		
	}
	float odleglosc = player->getPosition().x - sprite.getPosition().x;
	if ((std::abs(odleglosc)<250&&((odleglosc < 0 && kierunek == -1) || (odleglosc > 0 && kierunek == 1)))&& (charge_clock.getElapsedTime().asMilliseconds() >= 300))
	{
		przyspieszenie = 3.7;
	}

	sprite.move(2.2 * kierunek*przyspieszenie, 0);



}

void Orange::collision(Character* character)
{
	if (Player*player=dynamic_cast<Player*>(character))
	{
		if (collision_clock.getElapsedTime().asMilliseconds() >= 700)
		{
			player->setVelocityY(-33);
			player->setHealth(-1);
			player->scaleVelocityX(0);
			player->setCurrentPlayerState(PlayerState::in_air);
			collision_clock.restart();
		}
	}
	
}

void Orange::update()
{
	move();
	if (animation_clock.getElapsedTime().asMilliseconds() >= 500 / przyspieszenie)
	{
		animate();
	}
}
