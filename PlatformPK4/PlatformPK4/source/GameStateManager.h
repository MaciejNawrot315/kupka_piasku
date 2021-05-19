#pragma once
#include"GameState.h"
#include "Game.h"
#include"Pause.h"
#include"Menu.h"
enum class enum_Game_State { new_game,resume_game, pause, menu,end };
class GameStateManager
{
private:
	sf::RenderWindow* okno; 
	ResourceManager* manager;

	Menu* menu;
	Pause* pause;
	Game* game;
	
	sf::Clock esc_clock;

	  GameState* current_gamestate;
	  GameState* previous_gamestate;
public:
	GameStateManager(sf::RenderWindow* okno,ResourceManager* manager);
	void ChangeGameState(enum_Game_State x);
	GameState* getCurrentGamestate();
	GameState* getPreviousGamestate();
	bool isCurrentGamestatePause();
};

