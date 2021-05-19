#include "WaterCannon.h"
#include"Player.h" 
WaterCannon::WaterCannon(ResourceManager* manager, float left, float top) :Wall(manager, "watercannon", left, top, 20, 5), state(-1), start_pos({ left,top })
{
	sprite.setTextureRect({ 0,160,20,5 });

}

void WaterCannon::collision(Character* character)
{
	
	if (Player* player = dynamic_cast<Player*>(character))
	{
		player->setHealth(-1);
		sf::FloatRect gb_obiekt = getGlobalBounds();
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

void WaterCannon::update()
{
	sprite.move(0, state * 5);
	int y = start_pos.y - sprite.getPosition().y;
		sprite.setTextureRect({ 0,160 - y,20,5 + y });
		if (y == 160||y==0)
		{
			state *= -1;
		}
}
