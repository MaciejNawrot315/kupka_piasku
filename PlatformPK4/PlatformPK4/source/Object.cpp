#include "Object.h"

Object::Object(ResourceManager* manager,const std::string& texture_name, float left, float top)
{
	sf::Texture& texture = *manager->getTexture(texture_name);
	sprite.setTexture(texture);
	texture.setRepeated(true);
	sprite.setPosition(left, top);
}

void Object::draw(sf::RenderWindow* okno)
{
	okno->draw(sprite);
}

Object::~Object()
{

}

sf::FloatRect Object::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

void Object::update()
{
}
