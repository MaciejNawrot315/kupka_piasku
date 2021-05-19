#include "Key.h"
#include "Player.h"
Key::Key(ResourceManager* manager, float left, float top):PickUp(manager, "key", left, top)
{
}

void Key::collision(Character* character)
{
	if (Player* player = dynamic_cast<Player*>(character))
	{
		toDelete = true;
		player->addKeys(1);
	}

}
