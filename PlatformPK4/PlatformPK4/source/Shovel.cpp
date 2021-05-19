#include "Shovel.h"
#include "Player.h"
Shovel::Shovel(ResourceManager* manager, float left, float top) :PickUp(manager, "lopatka", left, top), win(0)
{
}

bool Shovel::EndGame()
{
	return win;
}

void Shovel::collision(Character* character)
{
	if (Player* player = dynamic_cast<Player*>(character))
	{
		
		if (player->getKeys() >= 4)
		{
			win = true;
		}
	}
}
