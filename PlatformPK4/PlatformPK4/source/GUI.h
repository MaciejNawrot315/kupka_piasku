#pragma once
#include <SFML/Graphics.hpp>
class GUI
{
private:
	sf::Sprite heartSprite;
	sf::Sprite empty_heartSprite;
	sf::Sprite keySprite;
	sf::Text keyNumber;
	sf::Text time;
	float time_elapsed_seconds;
	int time_elapsed_minutes;
public:
	GUI( class ResourceManager* manager);
	void draw(sf::RenderWindow* okno);
	void setHealth(int ile);
	void setKeys(int ile);
	void updateTime(sf::Time);
	float getTimeOfTheGame();
};