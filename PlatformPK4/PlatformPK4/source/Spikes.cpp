#include "Spikes.h"
#include "Player.h"
Spikes::Spikes(ResourceManager* manager, float left, float top, int width):Wall(manager,"spikes",left,top,width,10)
{
	sprite.setTextureRect({ 0,0,width,10 });
}

void Spikes::collision(Character* character)
{
	if (Player* player = dynamic_cast<Player*>(character))
	{
		player->setHealth(-1);
		player->setVelocityY(-30);
		player->setCurrentPlayerState(PlayerState::in_air);
	}
}
