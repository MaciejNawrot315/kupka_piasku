#include "ResourceManager.h"
#include <exception>
ResourceManager::ResourceManager(const std::string& sciezka)
{
	std::ifstream fin(sciezka,std::ios::in);
	std::string temp,temp2;
	
	while (std::getline(fin, temp,','))
	{

		std::getline(fin, temp2);
		std::shared_ptr< sf::Texture> polsl = std::make_shared< sf::Texture>();
		polsl->loadFromFile(temp2);
		tekstury.insert(std::make_pair(temp, polsl));
	}
	font.loadFromFile("..//resources//LucidaSansRegular.TTF");

}

std::shared_ptr< sf::Texture> ResourceManager::getTexture(const std::string& nazwa)
{ 
	auto temp = tekstury.find(nazwa);
	if (temp == tekstury.end())
	{
		throw std::runtime_error("nie znaleziono tekstury o takiej nazwie");
		return nullptr;

	}
	return temp->second;
	
}

sf::Font* ResourceManager::getFont()
{
	return &font;
}
