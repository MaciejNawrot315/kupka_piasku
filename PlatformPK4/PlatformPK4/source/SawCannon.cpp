#include "SawCannon.h"
#include "Player.h"
#include "Game.h"
SawCannon::SawCannon(ResourceManager* manager, float left, float top, int facing, Player* pplayer, std::vector<std::weak_ptr<Object>>* upd_obiekty_p, std::vector<std::shared_ptr<Object>>* obiekty_player_collision_p): Wall(manager,"sawcannon",left,top,50,50),kierunek(facing)
{
	player = pplayer;
	to_add_to_upd_obiekty = upd_obiekty_p;
	obiekty_player_collision = obiekty_player_collision_p;
	Rmanager = manager;
	sprite.setOrigin(25.f, 0.f);
	sprite.setScale(kierunek, 1);
}

void SawCannon::update()
{
	if 	(shoot_clock.getElapsedTime().asMilliseconds() >= 2000)
	{
		//shoot
		Game::addProjectile(Rmanager, obiekty_player_collision, to_add_to_upd_obiekty, "saw", sprite.getPosition().x + (25 * kierunek), sprite.getPosition().y + 25, sf::Vector2f(kierunek *9.7f, 0));
		shoot_clock.restart();
	}
}


