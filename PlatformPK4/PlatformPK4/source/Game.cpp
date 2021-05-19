#include "Game.h"
#include "Player.h"
#include "Orange.h"
#include "Projectile.h"
#include "PickUp.h"
#include "Key.h"
#include "Heart.h"
#include <memory>
#include "Gray.h"
#include "White.h"
#include"Spikes.h"
#include "SawCannon.h"
#include"WaterCannon.h"
#include "Wall.h"
#include <iostream>
#include "GameStateManager.h"


Game::Game(sf::RenderWindow* okno_p,ResourceManager* resources_p,GameStateManager* gsm_p) : mainview({ 0.f, 0.f, 800.f, 600.f }), resources(resources_p), myGUI({ 0.f,0.f,800.f,600.f }),gui(resources),gsm(gsm_p), okno(okno_p),afterpause(false), lopatka(nullptr)
{
	
	std::ifstream plik0;
	plik0.open("..//resources//best_time.txt");
	plik0 >> best_time;
	plik0.close();
	player = new Player(resources,&projectiles);
	init_objects();
	ttlo.loadFromFile("..//resources//tlo2.png");
	
	ttlo.setRepeated(true);
	tlo.setTexture(ttlo);
	tlo.setTextureRect({ 0,0, 2400, 1800 });
	tlo.setPosition(-1200, -900);
	
}

void Game::init_objects()
{
	std::shared_ptr<Object>temp = std::make_shared<Shovel>(resources, -500, 570); //6300, -1130);
	obiekty_player_collision.push_back(temp);
	Shovel* temp2 = dynamic_cast<Shovel*>(temp.get());
	lopatka = temp2;

	addWall("polsl", -150, -700, 150, 700);
	addWall("dirt", -150, 0, 3050,250);
	addWall("polsl", 50, -450, 150, 50);
	addKey(60, -480);
	addWaterCannon(300, -5);
	addWaterCannon(450, -5);
	addWaterCannon(600, -5);
	addSpikes(620, -10, 60);
	addWall("dirt", 680, -70, 800, 70);
	addWall("dirt", 450, -195, 200, 25);
	addWall("dirt", 550, -300, 140, 25);
	addWall("dirt", 300, -380, 150, 25);
	addEnemy('o', 980, -105, 1);
	addSawCannon(1455, -50, 1);
	//addEnemy('o', 1800, -35, 1);
	addKey(1800, -30);
	addWall("dirt", 2100, -70, 800, 70);
	addEnemy('g', 2400, -100);
	//addEnemy('g', 2400, -100,-1);
	addHeart(2700, -200);
	addWall("dirt", 2650, -170, 150, 25);
	addWall("dirt", 2650, -250, 150, 25);
	addWall("dirt", 2800, -380, 100, 25);
	addWall("dirt", 2440, -420, 150, 25);
	addSpikes(2440, -430, 40);
	addWall("dirt", 2570, -540, 100, 25);
	addWall("dirt", 2800, -650, 100, 25);
	addWall("dirt", 2900, -700, 300, 800);
//	addWaterCannon(2900, -705);
	addWall("dirt", 2800, -830, 100, 25);
	addWall("dirt", 2450, -880, 125, 25);
	addWall("dirt", 3200, -700, 1000, 300);
	addKey(2460, -910);
	addSpikes(3100, -710, 80);
	addSpikes(3330, -710, 120);
	addWaterCannon(3600, -705);
	addWall("dirt", 4200, -1000, 300, 800);
	addSawCannon(4225, -750, -1);
	addSpikes(4080, -710, 120);
	addHeart(4000, -730);
	addWall("dirt", 4100, -830, 100, 25);
	addHeart(4130, -860);
	addWall("dirt", 3920, -940, 100, 25);
	addKey(3930, -970);
	addWall("dirt", 4500, -1000, 700, 300);
	addEnemy('g', 4900, -1030, -1);
	addEnemy('g', 4800, -1030, 1);
	//addEnemy('g', 4800, -1030, -1);
	addHeart(5100, -1030);
	addWall("dirt", 5200, -1100, 1200, 300);
	addEnemy('w', 5950, -1240, -1);
	addWall("dirt", 5820, -1096, 11,4);
	addWall("polsl", 6400, -1400, 300, 600);
	//addWall( "polsl", 500, 480, 300, 50);
	//addEnemy('o', 900, 565);
	//addEnemy('g', 1100, 570);
	////addEnemy('g', -1100, 570);
	//addEnemy('w', 1400, 460,-1);
	//addSpikes(600, 470, 70);
	//addWall("dirt", -1200, 600, 3000, 200);
	//addSawCannon(-1200, 550,1);
	//addWaterCannon(30, 595);
	//addKey(-300, 570);
	//addKey(-270, 570);
	//addKey(-240, 570);
	//addKey(-210, 570);
	//addHeart(-100, 570);
	

}

void Game::updateCollision(sf::FloatRect* ViewRect)
{
	
		auto iter = obiekty_player_collision.begin();
		while (iter != obiekty_player_collision.end())
		{
			if ((player->getGlobalBounds().intersects((*iter)->getGlobalBounds())))
			{
				if (Wall* temp = dynamic_cast<Wall*>(iter->get()))
				{
					

					(*iter)->collision(player);
				}
				else if (player->getCurrentPlayerState()!=PlayerState::under_ground)
				{
					(*iter)->collision(player);
					if (PickUp* temp = dynamic_cast<PickUp*>(iter->get()))
					{
						if (temp->isToDelete())
						{
							obiekty_player_collision.erase(iter);
							break;
						}
					}
				}
			}

			if (Projectile* temp = dynamic_cast<Projectile*>(iter->get()))
			{
				if (temp->getDelete() || !(temp->getGlobalBounds().intersects(*ViewRect)))
				{
					obiekty_player_collision.erase(iter);
					break;
				}
			}
			if (Character* temp = dynamic_cast<Character*>(iter->get()))
			{
				if (temp->IsDead())
				{
					obiekty_player_collision.erase(iter);
					break;
				}
			}
			iter++;
		}
	
}

void Game::updatePlayer()
{
	player->update();
	if (player->IsDead())
	{
		float temp = gui.getTimeOfTheGame();
		std::ofstream plik;
		plik.open("..//resources//best_time.txt");
		
		plik << best_time;
		plik << '\n';
		plik << temp;
		plik.close();

		gsm->ChangeGameState(enum_Game_State::end);
	}
}

void Game::updateViews()
{
	mainview.setCenter(player->getPosition().x, player->getPosition().y-150);
	
	gui.setHealth(player->getHealth());
	gui.setKeys(player->getKeys());
	if ((player->getPosition().x - tlo.getPosition().x) >= 1900)
	{
		tlo.move(700, 0);
	}
	else if (((player->getPosition().x - tlo.getPosition().x) <= 500))
	{
		tlo.move(-700, 0);
	}
	if ((player->getPosition().y - tlo.getPosition().y) >= 1100)
	{
		tlo.move(0, 200);
	}
	else if (((player->getPosition().y - tlo.getPosition().y) <= 700))
	{
		tlo.move(0, -200);
	}
	updateGUI();
}

bool Game::ProjectileCollision(Projectile* proj)
{
	auto iter = enemies_and_walls.begin();
	while (iter != enemies_and_walls.end())
	{

		if (std::shared_ptr<Object>temp = (*iter).lock())
		{
			if (proj->getGlobalBounds().intersects(temp->getGlobalBounds()))
			{

				if (Character* temp2 = dynamic_cast<Character*>(temp.get()))
				{
					temp2->setHealth(-5);
				}
				return 1;
			}
			iter++;
		}
		else
			iter = enemies_and_walls.erase(iter);
	}
	return 0;
}

void Game::merge_obj_vect()
{
	for (auto& obiekt : to_add_to_upd_obiekty)
	{
		upd_obiekty.push_back(obiekt);
	}
	to_add_to_upd_obiekty.clear();
}

void Game::update()
{
	sf::FloatRect ViewRect = getViewGlobalBounds(&mainview);
	ViewRect.left -= 1200;
	ViewRect.width += 2400;
	ViewRect.top -= 1000;
	ViewRect.height += 2000;
	updatePlayer();
	updateCollision(&ViewRect);
	updateViews();
	while (okno->pollEvent(zdarzenie))
	{
		if (zdarzenie.type == sf::Event::Closed)
			okno->close();
		else if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
		{
			gsm->ChangeGameState(enum_Game_State::pause);
			afterpause = true;
		}
	}
	if (lopatka->EndGame())
	{
		float temp = gui.getTimeOfTheGame();
		std::ofstream plik;
		plik.open("..//resources//best_time.txt");
		if (temp < best_time)
			plik << temp;
		else
			plik << best_time;
		plik << '\n';
		plik << temp;
		plik.close();

		gsm->ChangeGameState(enum_Game_State::end);
	}
	auto iter = upd_obiekty.begin();
	while (iter != upd_obiekty.end())
	{

		if (std::shared_ptr<Object>temp = (*iter).lock())
		{
			temp->update();
			iter++;
		}
		else
			iter= upd_obiekty.erase(iter);
	}


	auto iter2 = projectiles.begin();//pociski gracza
	while (iter2 != projectiles.end())
	{

		(*iter2)->update();
		if (!((*iter2)->getGlobalBounds().intersects(ViewRect)))
			iter2 = projectiles.erase(iter2);
		else if(ProjectileCollision(*iter2))
			iter2 = projectiles.erase(iter2);
		else
			iter2++;
	}
	merge_obj_vect();
}

void Game::renderPlayer()
{
	player->render(okno);
}

void Game::updateGUI()
{
	if (afterpause)
	{
		time_clock.restart();
		afterpause = false;
	}
	else
	{
		gui.updateTime(time_clock.getElapsedTime());
		time_clock.restart();
	}
}

void Game::render()
{ 
	okno->clear(sf::Color::Black);
	okno->setView(mainview);
	okno->draw(tlo);
	for (auto& obiekt : obiekty_player_collision)
	{
		obiekt->draw(okno);
	}
	for (auto& projectile : projectiles)
	{
		projectile->draw(okno);
	}
	renderPlayer();
	renderGUI();
}

void Game::renderGUI()
{
	okno->setView(myGUI);
	
	gui.draw(okno);
	

}

void Game::addWall( const std::string& name, int left, int top, int width, int height)
{
	std::shared_ptr<Object>temp0 = std::make_shared<Wall>(resources,name, left, top, width, height);
	obiekty_player_collision.push_back(temp0);
	enemies_and_walls.push_back(temp0);
	
}

void Game::addSpikes(int left, int top, int width)
{
	std::shared_ptr<Object>temp0 = std::make_shared<Spikes>(resources, left, top, width);
	obiekty_player_collision.push_back(temp0);
}

void Game::addWaterCannon(int left, int top)
{
	std::shared_ptr<Object>temp0 = std::make_shared<WaterCannon>(resources, left, top);
	obiekty_player_collision.push_back(temp0);
	upd_obiekty.push_back(temp0);

}

void Game::addEnemy( char char_name, int left, int top, int facing)
{
	std::shared_ptr<Object>temp;
	switch (char_name)
	{
	case 'o':
	{
		temp = std::make_shared<Orange>(resources, left, top, player);
		
		break;
	}
	case 'g':
	{
	temp = std::make_shared<Gray>(resources, left, top, player,&to_add_to_upd_obiekty,&obiekty_player_collision,facing);	
	break;
	}
	case 'w':
	{
		temp = std::make_shared<White>(resources, left, top,facing, player, &to_add_to_upd_obiekty, &obiekty_player_collision);
		break;
	}
	}
	obiekty_player_collision.push_back(temp);
	upd_obiekty.push_back(temp);
	enemies_and_walls.push_back(temp);
}

void Game::addKey(int left, int top)
{
	std::shared_ptr<Object>temp3 = std::make_shared<Key>(resources, left, top);
	obiekty_player_collision.push_back(temp3);
}

void Game::addHeart(int left, int top)
{
	std::shared_ptr<Object>temp4 = std::make_shared<Heart>(resources, left, top);
	obiekty_player_collision.push_back(temp4);
}

void Game::addSawCannon(int left, int top, int facing)
{
	std::shared_ptr<Object>temp0 = std::make_shared<SawCannon>(resources, left, top, facing, player, &to_add_to_upd_obiekty, &obiekty_player_collision);
	obiekty_player_collision.push_back(temp0);
	enemies_and_walls.push_back(temp0);
	upd_obiekty.push_back(temp0);
}

void Game::addProjectile(ResourceManager* manager, std::vector<std::shared_ptr<Object>>* obiekty_player_collision, std::vector<std::weak_ptr<Object>>* to_add_to_upd_obiekty, const std::string& name, int left, int top, sf::Vector2f velocity)
{
	std::shared_ptr<Object>temp2 = std::make_shared<Projectile>(manager, name, left,top,velocity);
	obiekty_player_collision->push_back(temp2);
	to_add_to_upd_obiekty->push_back(temp2);
}

sf::RenderWindow* Game::getOkno()
{
	return okno;
}

sf::FloatRect Game::getViewGlobalBounds(sf::View* view)
{
	sf::FloatRect rect;
	rect.left = view->getCenter().x - view->getSize().x / 2.f;
	rect.top= view->getCenter().y - view->getSize().y / 2.f;
	rect.width = view->getSize().x;
	rect.height = view->getSize().y;
	return rect;
}

bool Game::isWon()
{
	return lopatka->EndGame();
}
