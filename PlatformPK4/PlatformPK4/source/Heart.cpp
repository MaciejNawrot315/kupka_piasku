#include "Heart.h"
#include "Player.h"
Heart::Heart(ResourceManager* manager, float left, float top) :PickUp(manager, "fullheart", left, top)
{
}

void Heart::collision(Character* character)
{
	if (Player* player = dynamic_cast<Player*>(character))
	{
		toDelete = true;
		player->setHealth(1);
	}
}
