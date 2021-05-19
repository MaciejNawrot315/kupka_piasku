
#include "White.h"
#include "Player.h"
#include"Projectile.h"
#include "Game.h"
White::White(ResourceManager* manager, float left, float top,int facing, Player* pplayer, std::vector<std::weak_ptr<Object>>* upd_obiekty_p, std::vector<std::shared_ptr<Object>>* obiekty_player_collision_p):
	Character(manager, "white", left, top, 80), kierunek(facing)//, Wall(manager,"white",left, top, 240, 160)
{
	player = pplayer;
	to_add_to_upd_obiekty = upd_obiekty_p;
	obiekty_player_collision = obiekty_player_collision_p;
	Rmanager = manager;
	Object::sprite.setOrigin(120.f, 0.f);
}

void White::collision(Character*character)
{
	player->setHealth(-1);
		if (Player* player = dynamic_cast<Player*>(character))
		{

			sf::FloatRect gb_obiekt = Object::getGlobalBounds();
			sf::FloatRect gb_player = player->getGlobalBounds();

			float tab[] = { std::abs(gb_obiekt.left - (gb_player.left + gb_player.width)),std::abs(gb_player.top - (gb_obiekt.top + gb_obiekt.height)),
							std::abs(gb_player.left - (gb_obiekt.left + gb_obiekt.width)),std::abs(gb_obiekt.top - (gb_player.top + gb_player.height)) };
			size_t j = 0;
			for (size_t i = 1; i < 4; i++)
			{
				if (tab[j] > tab[i])
					j = i;
			}
			switch (j)
			{
			case 0:
			{
				
				//player->setVelocityX(3);
				player->setPosition(gb_obiekt.left - gb_player.width / 2, player->getPosition().y);
				//player->setCurrentPlayerState(PlayerState::on_ground);
				player->setVelocityX(-20);
				break;
			}
			case 1:
			{
				
				player->setPosition(player->getPosition().x, gb_obiekt.top - player->getGlobalBounds().height / 2);
				player->setCurrentPlayerState(PlayerState::on_ground);
				player->setVelocityY(-20);
				break;
			}
			case 2:
			{
			
				player->setPosition((gb_obiekt.left + gb_obiekt.width) + gb_player.width / 2, player->getPosition().y);
				player->setVelocityX(20);
			
				break;
			}
			case 3:
			{
			
				player->setPosition(player->getPosition().x, gb_obiekt.top - player->getGlobalBounds().height / 2);
				player->setCurrentPlayerState(PlayerState::on_ground);
				player->setVelocityY(-20);
				break;
			}
			}
	}
}

void White::update()
{
	float odleglosc = player->getPosition().x - Object::sprite.getPosition().x;
	sf::FloatRect sprite_gb = Object::sprite.getGlobalBounds();
	int tema = shoot_clock.getElapsedTime().asMilliseconds();
	if ((std::abs(odleglosc) < 500 && ((odleglosc < 0 && kierunek == -1) || (odleglosc > 0 && kierunek == 1))) &&
		(shoot_clock.getElapsedTime().asMilliseconds() >= 900) &&
		(player->getPosition().y > sprite_gb.top && player->getPosition().y < (sprite_gb.top + sprite_gb.height)))
	{
		//shoot
		Game::addProjectile(Rmanager, obiekty_player_collision, to_add_to_upd_obiekty, "enemyprojectile", sprite.getPosition().x + (120 * kierunek), player->getPosition().y-20, sf::Vector2f(kierunek * 4.6f, 0));
		shoot_clock.restart();
	}
}
