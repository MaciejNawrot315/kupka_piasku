#include "Menu.h"
#include"ResourceManager.h"
#include "GameStateManager.h"
#include "string"
Menu::Menu(sf::RenderWindow* okno_p, ResourceManager* resources_p, GameStateManager* gsm_p): okno(okno_p), resources(resources_p),gsm(gsm_p)

{
	float best_time;
	float last_time;
	std::ifstream plik0;
	plik0.open("..//resources//best_time.txt");
	plik0 >> best_time;
	plik0 >> last_time;
	plik0.close();

	int minuty = best_time / 60;
	int sekundy = (int)best_time % 60;
	int minuty2 = last_time / 60;
	int sekundy2 = (int)last_time % 60;
	best_time_text.setFont(*resources_p->getFont());
	best_time_text.setString("Your Best Time= "+ std::to_string(minuty)+"minutes, "+std::to_string(sekundy)+ " seconds");
	best_time_text.setCharacterSize(30);
	best_time_text.setFillColor(sf::Color::White);
	best_time_text.setPosition(200, 300);

	last_time_text.setFont(*resources_p->getFont());
	last_time_text.setString("Your Last Time= " + std::to_string(minuty2) + "minutes, " + std::to_string(sekundy2) + " seconds");
	last_time_text.setCharacterSize(30);
	last_time_text.setFillColor(sf::Color::White);
	last_time_text.setPosition(200, 350);

	first_button.setSize(sf::Vector2f(200, 100));
	first_button.setOutlineColor(sf::Color::Red);
	first_button.setOutlineThickness(5);
	first_button.setPosition(300, 100);
	first_button.setFillColor(sf::Color::Yellow);


	second_button.setSize(sf::Vector2f(200, 100));
	second_button.setOutlineColor(sf::Color::Red);
	second_button.setOutlineThickness(0);
	second_button.setPosition(300, 400);
	second_button.setFillColor(sf::Color::Yellow);

	first_button_text.setFont(*resources_p->getFont());
	first_button_text.setString("New Game");
	first_button_text.setCharacterSize(30);
	first_button_text.setFillColor(sf::Color::Black);
	first_button_text.setPosition(325, 120);

	second_button_text.setFont(*resources_p->getFont());
	second_button_text.setString("Exit");
	second_button_text.setCharacterSize(30);
	second_button_text.setFillColor(sf::Color::Black);
	second_button_text.setPosition(325, 420);
	selected_button = &first_button;
	other_button = &second_button;
}

Menu::Menu()
{
}

void Menu::update()
{

	while (okno->pollEvent(zdarzenie))
	{
		if (zdarzenie.type == sf::Event::Closed)
			okno->close();
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))&&change_clock.getElapsedTime().asMilliseconds()>=300)
	{
		sf::RectangleShape* temp = selected_button;
		selected_button =other_button;
		other_button = temp;
		other_button->setOutlineThickness(0);
		selected_button->setOutlineThickness(5);
		change_clock.restart();

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		okno->close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (selected_button == &first_button)
		{
			gsm->ChangeGameState(enum_Game_State::new_game);

		}
		else
			okno->close();
	}
}

void Menu::render()
{
	okno->clear(sf::Color::Black);
	okno->draw(first_button);
	okno->draw(first_button_text);
	okno->draw(second_button);
	okno->draw(second_button_text);
	okno->draw(best_time_text);
	okno->draw(last_time_text);
}
