#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
class Menu: public GameState
{
private: 	
	sf::Text best_time_text;
	   sf::Text last_time_text;
protected:
	sf::RectangleShape first_button;
	sf::Text first_button_text;
	sf::RectangleShape second_button;
	sf::Text second_button_text;
	sf::RenderWindow* okno;
	sf::Clock change_clock;
	sf::RectangleShape* selected_button;
	sf::RectangleShape*	other_button;
	sf::Event zdarzenie;
	class ResourceManager* resources;
	class GameStateManager* gsm;

public:
	Menu(sf::RenderWindow* okno_p, class ResourceManager* resources_p, class GameStateManager* gsm_p);
	Menu();
	void update();
	void render();
};

