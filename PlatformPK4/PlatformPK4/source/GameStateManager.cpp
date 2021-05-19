#include "GameStateManager.h"
#include "Menu.h"
#include "Pause.h"
#include "EndGame.h"
GameStateManager::GameStateManager(sf::RenderWindow* okno_p, ResourceManager* manager_p):okno(okno_p), manager(manager_p)
{
	pause = nullptr;
	game = nullptr;
		menu= new Menu(okno_p, manager_p,this);
		current_gamestate = menu;
	previous_gamestate = nullptr;
}

void GameStateManager::ChangeGameState(enum_Game_State x)
{
	switch (x)
	{
	case enum_Game_State::new_game:
	{
		if (esc_clock.getElapsedTime().asMilliseconds() >= 400)
		{
			esc_clock.restart();
			previous_gamestate = current_gamestate;
			game = new Game(okno, manager, this);
			current_gamestate = game;
		}
		break;
	}
	case enum_Game_State::pause:
	{if (esc_clock.getElapsedTime().asMilliseconds() >= 400)
	{
		previous_gamestate = current_gamestate;
		if (!pause)
			current_gamestate = new Pause(okno, manager, this);
		else
			current_gamestate = pause;
		esc_clock.restart();
	}
		break;
	}
	case enum_Game_State::resume_game:
	{
		if (esc_clock.getElapsedTime().asMilliseconds() >= 400)
		{
			GameState* temp = previous_gamestate;
			previous_gamestate = current_gamestate;
			current_gamestate = temp;
			esc_clock.restart();
		}
		break;
	}
	case enum_Game_State::menu:
	{
		if (esc_clock.getElapsedTime().asMilliseconds() >= 400)
		{
			previous_gamestate = current_gamestate;
			current_gamestate = new Menu(okno, manager, this);
			
			esc_clock.restart();
		}
		break;
	}
	case enum_Game_State::end:
	{
		if (esc_clock.getElapsedTime().asMilliseconds() >= 400)
		{
			previous_gamestate = current_gamestate;
			current_gamestate = new EndGame(okno, manager, this,game->isWon());

			esc_clock.restart();
		}
		break;
	}
	}
}

GameState* GameStateManager::getCurrentGamestate()
{
	return current_gamestate;
}

GameState* GameStateManager::getPreviousGamestate()
{
	return previous_gamestate;
}

bool GameStateManager::isCurrentGamestatePause()
{
	if(current_gamestate=pause)
	return 1;
	else return 0;
}

