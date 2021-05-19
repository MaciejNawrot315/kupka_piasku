#include "EndGame.h"
#include "ResourceManager.h"
#include"GameStateManager.h"
EndGame::EndGame(sf::RenderWindow* okno_p, ResourceManager* resources_p, GameStateManager* gsm_p, bool wasWon)
{
	okno = okno_p;
	resources = resources_p;
	gsm = gsm_p;
	
	float last_time;
	std::ifstream plik0;
	plik0.open("..//resources//best_time.txt");
	plik0 >> last_time;
	plik0 >> last_time;
	plik0.close();

	int minuty = last_time / 60;
	int sekundy = (int)last_time % 60;
	
	last_time_text.setFont(*resources_p->getFont());
	last_time_text.setString("Your Time= " + std::to_string(minuty) + "minutes, " + std::to_string(sekundy) + " seconds");
	last_time_text.setCharacterSize(30);
	last_time_text.setFillColor(sf::Color::White);
	last_time_text.setPosition(200, 80);

	gameover_text.setFont(*resources_p->getFont());
	if(wasWon)
	gameover_text.setString("YON WON!");
	else
	gameover_text.setString("GAME OVER");
	gameover_text.setCharacterSize(70);
	gameover_text.setFillColor(sf::Color::White);
	gameover_text.setPosition(200, 10);

	first_button.setSize(sf::Vector2f(200, 50));
	first_button.setOutlineColor(sf::Color::Red);
	first_button.setOutlineThickness(5);
	first_button.setPosition(300, 250);
	first_button.setFillColor(sf::Color::Yellow);


	second_button.setSize(sf::Vector2f(200, 50));
	second_button.setOutlineColor(sf::Color::Red);
	second_button.setOutlineThickness(0);
	second_button.setPosition(300, 350);
	second_button.setFillColor(sf::Color::Yellow);

	first_button_text.setFont(*resources_p->getFont());
	first_button_text.setString("Replay");
	first_button_text.setCharacterSize(30);
	first_button_text.setFillColor(sf::Color::Black);
	first_button_text.setPosition(325, 260);

	second_button_text.setFont(*resources_p->getFont());
	second_button_text.setString("Exit to Main Menu");
	second_button_text.setCharacterSize(20);
	second_button_text.setFillColor(sf::Color::Black);
	second_button_text.setPosition(315, 360);
	selected_button = &first_button;
	other_button = &second_button;
}

void EndGame::update()
{
	while (okno->pollEvent(zdarzenie))
	{
		if (zdarzenie.type == sf::Event::Closed)
			okno->close();

	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && change_clock.getElapsedTime().asMilliseconds() >= 300)
	{
		sf::RectangleShape* temp = selected_button;
		selected_button = other_button;
		other_button = temp;
		other_button->setOutlineThickness(0);
		selected_button->setOutlineThickness(5);
		change_clock.restart();

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		gsm->ChangeGameState(enum_Game_State::menu);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (selected_button == &first_button)
			gsm->ChangeGameState(enum_Game_State::new_game);
		else
			gsm->ChangeGameState(enum_Game_State::menu);
	}
}

void EndGame::render()
{
	okno->clear(sf::Color::Black);
	okno->draw(first_button);
	okno->draw(first_button_text);
	okno->draw(second_button);
	okno->draw(second_button_text);
	okno->draw(last_time_text);
	okno->draw(gameover_text);
}
