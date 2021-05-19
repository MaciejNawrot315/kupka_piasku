#pragma once
#include "Menu.h"

class EndGame: public Menu
{
private:
	sf::Text last_time_text;
	sf::Text gameover_text;
public:
	EndGame(sf::RenderWindow* okno_p, class ResourceManager* resources_p, class GameStateManager* gsm_p, bool wasWon);
	void update();
	void render();
};

