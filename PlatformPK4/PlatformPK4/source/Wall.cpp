#include "Wall.h"
#include <cstdint>
#include "ResourceManager.h"
#include "Player.h"
Wall::Wall(ResourceManager* manager,const std::string& texture_name, float left, float top, int width, int height): Object(manager,texture_name,left,top)
{
	sprite.setTextureRect({ 0,0,width,height });
	//texture.create(50,50);
	//texture.update(pixels2);

}

void Wall::collision(Character* character)
{
	if (Player* player = dynamic_cast<Player*>(character))
	{
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
			player->scaleVelocityX(0);
			//player->setVelocityX(3);
			player->setPosition(gb_obiekt.left - gb_player.width / 2, player->getPosition().y);
			//player->setCurrentPlayerState(PlayerState::on_ground);
			
			break;
		}
		case 1:
		{
			player->scaleVelocityY(0);
			player->setPosition(player->getPosition().x, (gb_obiekt.top + gb_obiekt.height) + player->getGlobalBounds().height / 2);
		
			break;
		}
		case 2:
		{
			player->scaleVelocityX(0);
			player->setPosition((gb_obiekt.left + gb_obiekt.width) + gb_player.width / 2, player->getPosition().y);
			break;
		}
		case 3:
		{
			player->scaleVelocityY(0);
			player->setPosition(player->getPosition().x, gb_obiekt.top - player->getGlobalBounds().height / 2);
			if (player->getCurrentPlayerState() == PlayerState::in_air)
				player->setCurrentPlayerState(PlayerState::on_ground);
			break;
		}
		}
	}
}



Wall::~Wall()
{
	
}


//if (!texture.loadFromFile("..//resources//polsl.png"))
//{
//	std::cout << "nie zjaleziony png kupka1\n";
//}
//uint8_t* pixels2 = new uint8_t[50 * 50 * 4];
//for (size_t i = 0; i < 50; i++)
//{
//	for (size_t j = 0; j < 50; j++)
//	{
//		pixels2[i * 50 * 4 + j * 4] = 5 * i;
//		pixels2[i * 50 * 4 + j * 4 + 1] = 255 - 3 * i;
//		pixels2[i * 50 * 4 + j * 4 + 2] = 5 * j;
//		pixels2[i * 50 * 4 + j * 4 + 3] = 255;
//	}
//}
////texture.create(50,50);
////texture.update(pixels2);
//sprite.setTexture(texture);
//
//sprite.setPosition(500, 470);
//delete[] pixels2;