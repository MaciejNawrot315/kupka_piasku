#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "ResourceManager.h"
class Object
{
protected:
	sf::Sprite sprite;
public:
	Object(ResourceManager* manager,const std::string& texture_name, float left, float top);
	virtual void draw(sf::RenderWindow* okno);
	virtual ~Object();
	virtual void collision(class Character* character)=0;
	 sf::FloatRect getGlobalBounds();
	 virtual void update();
		
};

