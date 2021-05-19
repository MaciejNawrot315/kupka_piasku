#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include<fstream>
#include <memory>
class ResourceManager
{
private:
	using tekst = std::pair<std::string, sf::Texture*>;
	std::unordered_map<std::string, std::shared_ptr< sf::Texture>>tekstury;
	sf::Font font;
public:
	ResourceManager(const std::string&sciezka);
	std::shared_ptr< sf::Texture> getTexture(const std::string& nazwa);
	sf::Font* getFont();
};

