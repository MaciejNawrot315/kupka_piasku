#pragma once
#include "Character.h"
enum class PlayerState {on_ground,  in_air,under_ground};
class Player : public Character
{
private:
	
	std::vector<class Projectile*>* projectiles;
	sf::Texture tekstura;
	sf::Clock clock;
	PlayerState CurrentPlayerState;
	sf::Clock damage_clock;
	sf::Clock shoot_clock;
	sf::Clock dive_clock;
	sf::Clock dive_cooldown_clock;
	//fizyka
	sf::Vector2f prev_position;
	sf::Vector2f velocity;
	float max_velocity;
	float min_velocity;
	float acceleration;
	float drag;
	float gravity_a;
	//
	
	int facing;
	int keys;
	ResourceManager* Rmanager;
	//
	

public:
	Player(class ResourceManager* manager, std::vector<class Projectile*>* proj_vec);
	void setCurrentPlayerState(PlayerState state);
	//const sf::FloatRect getGlobalBounds()const;
	const sf::Vector2f getPosition()const;
	const sf::Vector2f getPrevPosition()const;
	void setPosition(const float x, const float y);
	void scaleVelocityX(float ilosc);
	void scaleVelocityY(float ilosc);
	void setVelocityY(float ilosc);
	void setVelocityX(float ilosc);
	void reverseVelocity();
	void shoot();
	void jump();
	void move(const float x, const float y);
	void updatePhysics();
	void update();
	void updateAnimation();
	void render(sf::RenderWindow* target);
	void setHealth(int ile);
	void collision( Character* player);
	void addKeys(int ile);
	int getKeys();
	PlayerState getCurrentPlayerState();
	sf::Vector2f getVelocity();
};

