#include "Pause.h"
#include "ResourceManager.h"
#include"GameStateManager.h"
Pause::Pause(sf::RenderWindow* okno_p, ResourceManager* resources_p, GameStateManager* gsm_p)
{
	okno = okno_p;
	resources = resources_p;
	gsm=gsm_p;
	back.setSize(sf::Vector2f(300, 300));
	back.setPosition(250, 200);
	back.setFillColor({ 125,125,125,255 });

	back_shade.setSize(sf::Vector2f(800, 600));
	back_shade.setFillColor({ 125,125,125,100 });
	back_shade.setPosition(0, 0);

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
	first_button_text.setString("Resume");
	first_button_text.setCharacterSize(30);
	first_button_text.setFillColor(sf::Color::Black);
	first_button_text.setPosition(325, 260);

	second_button_text.setFont(*resources_p->getFont());
	second_button_text.setString("Exit to Main Menu");
	second_button_text.setCharacterSize(30);
	second_button_text.setFillColor(sf::Color::Black);
	second_button_text.setPosition(325, 360);
	selected_button = &first_button;
	other_button = &second_button;
}

void Pause::update()
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
		gsm->ChangeGameState(enum_Game_State::resume_game);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (selected_button == &first_button)
			gsm->ChangeGameState(enum_Game_State::resume_game);
		else
			gsm->ChangeGameState(enum_Game_State::menu);
	}
}

void Pause::render()
{
	
	gsm->getPreviousGamestate()->render();
	okno->draw(back_shade);
	okno->draw(back);
	okno->draw(first_button);
	okno->draw(first_button_text);
	okno->draw(second_button);
	okno->draw(second_button_text);

}
