#include "GUI.h"
#include "ResourceManager.h"
#include <string>
GUI::GUI(ResourceManager* manager):time_elapsed_seconds(0.f), time_elapsed_minutes(0)
{
	sf::Texture& texture = *manager->getTexture("fullheart");
	heartSprite.setTexture(texture);
	texture.setRepeated(true);
	heartSprite.setTextureRect({ 0,0,120,30 });
	heartSprite.setScale(1.5, 1.5);
	
	sf::Texture& texture2 = *manager->getTexture("emptyheart");
	empty_heartSprite.setTexture(texture2);
	texture2.setRepeated(true);
	empty_heartSprite.setTextureRect({ 0,0,120,30 });
	empty_heartSprite.setScale(1.5, 1.5);

	sf::Texture& texture3 = *manager->getTexture("key");
	keySprite.setTexture(texture3);
	keySprite.setPosition(360, 0);
	keySprite.setScale(2, 2);
	keyNumber.setFont(*manager->getFont());
	keyNumber.setString("0");
	keyNumber.setCharacterSize(50);
	keyNumber.setFillColor(sf::Color::White);
	keyNumber.setPosition(400, 0);

	time.setFont(*manager->getFont());
	time.setString("00:00");
	time.setCharacterSize(50);
	time.setFillColor(sf::Color::White);
	time.setPosition(600, 0);
	
}

void GUI::draw(sf::RenderWindow* okno)
{
	okno->draw(empty_heartSprite);
	okno->draw(heartSprite);
	okno->draw(keySprite);
	okno->draw(keyNumber);
	okno->draw(time);
}

void GUI::setHealth(int ile)
{
	heartSprite.setTextureRect({ 0,0,30*ile,30 });
}

void GUI::setKeys(int ile )
{
	keyNumber.setString(std::to_string(ile)+"/4");
}

void GUI::updateTime(sf::Time timet)
{
	time_elapsed_seconds += timet.asSeconds();
	if (time_elapsed_seconds >= 60.f)
	{
		time_elapsed_seconds -= 60.f;
		time_elapsed_minutes += 1;
	}
	time.setString(std::to_string(time_elapsed_minutes)+':'+std::to_string((int)time_elapsed_seconds));
}

float GUI::getTimeOfTheGame()
{
	return (time_elapsed_minutes*60.f+time_elapsed_seconds);
}
