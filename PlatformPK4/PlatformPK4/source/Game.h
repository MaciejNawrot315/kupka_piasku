#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "ResourceManager.h"
#include"GUI.h"
#include "GameState.h"
#include"Shovel.h"

class Game: public GameState
{private:
	sf::RenderWindow* okno;
	sf::View mainview;
	sf::View myGUI;
	sf::Event zdarzenie;
	class GameStateManager* gsm;
	ResourceManager* resources;
	GUI gui;
	sf::Clock time_clock;
	float best_time;
	bool afterpause;
	class Player* player;
	sf::Sprite tlo;
	sf::Texture ttlo;
	Shovel* lopatka;
	std::vector<std::shared_ptr<class Object>> obiekty_player_collision;//obiekty z ktormi postac moze kolidowac/wszystkie
	std::vector<std::weak_ptr<class Object>> upd_obiekty;//obiekty ktore trzeba updateowac co klatkê- porzeciwnicy chodz¹cy i strzelaj¹cy(bez scian, pick up'ow i kolców)
	std::vector<class Projectile*> projectiles;//pociski gracza ktore koliduj¹ z przeciwnikami i scianami(?)
	std::vector< std::weak_ptr<class Object>> enemies_and_walls;//przeciwnicy i sciany
	std::vector<std::weak_ptr<class Object>> to_add_to_upd_obiekty;
	void init_objects();
	void updateCollision(sf::FloatRect* ViewRect);
	void updatePlayer();
	void updateViews();
	bool ProjectileCollision(class Projectile* proj);
	void merge_obj_vect();
	void renderPlayer();
	void updateGUI();
	void renderGUI();
	void addWall(const std::string& name,int left, int top,int width,int height );
	void addSpikes(int left, int top, int width);
	void addWaterCannon(int left, int top);
	void addEnemy( char char_name, int left, int top,int facing =1);
	void addKey(int left, int top);
	void addHeart(int left, int top);
	void addSawCannon(int left, int top, int facing);
	
public:
	static void addProjectile(ResourceManager* manager, std::vector<std::shared_ptr<Object>>* obiekty_player_collision, std::vector<std::weak_ptr<Object>>* upd_obiekty, const std::string& name, int left, int top, sf::Vector2f velocity);

	Game(sf::RenderWindow* okno_p, ResourceManager* resources_p, GameStateManager* gsm_p);
	void update();
	void render();
	sf::RenderWindow* getOkno();
	sf::FloatRect getViewGlobalBounds(sf::View* view);
	bool isWon();
};

