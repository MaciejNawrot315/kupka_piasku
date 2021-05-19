#include"Game.h"
#include "GameStateManager.h"
int main()
{
   
    sf::RenderWindow okno;
    okno.create(sf::VideoMode(800, 600), "Platformowka");
    okno.setFramerateLimit(60);
    ResourceManager resources = {"..//resources//lista.csv"};
    GameStateManager gsm = {&okno,&resources};
    while (okno.isOpen())
    {
        gsm.getCurrentGamestate()->update();
        gsm.getCurrentGamestate()->render();
        okno.display();
    }
    
    return 0;
}