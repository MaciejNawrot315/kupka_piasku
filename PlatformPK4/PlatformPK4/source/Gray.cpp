#include "Gray.h"
#include "Player.h"
#include "Projectile.h"
#include "Game.h"
Gray::Gray(ResourceManager* manager, float left, float top, Player* pplayer, std::vector<std::weak_ptr<Object>>* upd_obiekty_p, std::vector<std::shared_ptr<Object>>* obiekty_player_collision_p, int facing):
			Character(manager, "gray", left, top, 15), kierunek(facing), start_pos(left), przyspieszenie(1)
{
	collision_clock.restart();
	player = pplayer;
	upd_obiekty = upd_obiekty_p;
	obiekty_player_collision = obiekty_player_collision_p;
	Rmanager = manager;
	hitbox_size = { 47,25 };
	sprite.setScale(1.3*kierunek, 1.3);
}

void Gray::move()
{
	if ((std::abs(sprite.getPosition().x - start_pos) > 250) && (rotate_clock.getElapsedTime().asMilliseconds() >= 100))
	{
		sprite.setScale(1.3*kierunek, 1.3);
		kierunek *= -1;
		rotate_clock.restart();
	}
	float odleglosc = player->getPosition().x - sprite.getPosition().x;
	sf::FloatRect sprite_gb = sprite.getGlobalBounds();
	int tema = shoot_clock.getElapsedTime().asMilliseconds();
	if ((std::abs(odleglosc) < 400 && ((odleglosc < 0 && kierunek == -1) || (odleglosc > 0 && kierunek == 1))) && 
		(shoot_clock.getElapsedTime().asMilliseconds() >= 1300)&&
		(player->getPosition().y>sprite_gb.top&& player->getPosition().y< (sprite_gb.top+ sprite_gb.height)))
	{
		//shoot
		Game::addProjectile(Rmanager, obiekty_player_collision, upd_obiekty, "enemyprojectile", sprite.getPosition().x + (25 * kierunek), sprite.getPosition().y+5, sf::Vector2f(kierunek * 6.f, 0));
		shoot_clock.restart();
		current_frame = { 0 + 47 * animation_state, 25, hitbox_size.x, hitbox_size.y };

		sprite.setTextureRect(current_frame);
		animation_clock.restart();
	}

	sprite.move(2.2 * kierunek * przyspieszenie, 0);
}

void Gray::collision(Character* character)
{
	if (Player* player = dynamic_cast<Player*>(character))
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

void Gray::update()
{
	move();
	if (animation_clock.getElapsedTime().asMilliseconds() >= 200)
	{
		animate();
	}
}


