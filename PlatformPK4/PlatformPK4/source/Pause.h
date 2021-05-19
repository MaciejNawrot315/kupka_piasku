#pragma once
#include "Menu.h"

class Pause: public Menu
{
private:
	sf::RectangleShape back;
	sf::RectangleShape back_shade;
	
public:
	Pause(sf::RenderWindow* okno_p, class ResourceManager* resources_p, class GameStateManager* gsm_p);
	void update();
	void render();
};

