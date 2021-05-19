#include "Player.h"
#include "ResourceManager.h"
#include "Projectile.h"
Player::Player(ResourceManager* manager, std::vector<class Projectile*>* proj_vec) : Character(manager, "kupka1", 20,0, 4), CurrentPlayerState(PlayerState::on_ground), max_velocity(10.f),
min_velocity(1.f), acceleration(2.7f), drag(0.87f), gravity_a(1.7f), facing(1), projectiles(proj_vec), Rmanager(manager), keys(0)

{

	clock.restart();
	damage_clock.restart();
	shoot_clock.restart();
	hitbox_size = { 40,19 };
	sprite.setOrigin(20.f, 10.f);
	current_frame = { 0, 0, 40, 19 };
	sprite.setTextureRect(current_frame);
	animation_clock.restart();
	sprite.setScale(-1, 1);
}

void Player::setCurrentPlayerState(PlayerState state)
{
	CurrentPlayerState = state;
}

const sf::Vector2f Player::getPosition() const
{
	return sprite.getPosition();
}

const sf::Vector2f Player::getPrevPosition() const
{
	return prev_position;
}

void Player::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}
void Player::scaleVelocityX(float ilosc )
{
	velocity.x*= ilosc;
}

void Player::scaleVelocityY(float ilosc )
{
		velocity.y *= ilosc;
}

void Player::setVelocityY(float ilosc)
{
	velocity.y = ilosc;
}

void Player::setVelocityX(float ilosc)
{
	velocity.x = ilosc;
}

void Player::reverseVelocity()
{
	velocity.x *= -1;
	velocity.y *= -1;
}

void Player::shoot()
{
	projectiles->push_back(new Projectile(Rmanager, "kupkap", sprite.getPosition().x + (20 * facing), sprite.getPosition().y - 10, { facing * 9.7f,0 }));
}

void Player::jump()
{
	velocity.y += -14*acceleration;
}

void Player::move(const float dir_x, const float dir_y)
{
	//acceleration
	velocity.x += dir_x * acceleration;
	//velocity.y += dir_y * acceleration;///do usuniecia bo jump

	if (std::abs(velocity.x) > max_velocity)
	{
		velocity.x = max_velocity * ((velocity.x < 0.f) ? -1.f : 1.f);
	}

}

void Player::updatePhysics()
{//drag
	velocity.y += 1.0 * gravity_a;
	velocity*= drag;
	
	//if (std::abs(velocity.y) > max_velocity)//to tez
	//{
	//	velocity.y = max_velocity * ((velocity.y < 0.f) ? -1.f : 1.f);
	//}
	
	if (std::abs(velocity.x) < min_velocity)
		velocity.x = 0.f;
	if (std::abs(velocity.y) < min_velocity)
		velocity.y = 0.f;


	sprite.move(velocity);
	
}

void Player::update()
{
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			move(-1, 0);
			facing = -1;
			sprite.setScale(1, 1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			move(1, 0);
			facing = 1;
			sprite.setScale(-1, 1);
		}
		
		
	if (CurrentPlayerState == PlayerState::on_ground)
	{
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& dive_clock.getElapsedTime().asMilliseconds() >= 800/**/)
		{
			setCurrentPlayerState(PlayerState::under_ground);
			animation_state = 0;
			updateAnimation();
			dive_clock.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//move(-1, 0);
		
			jump();
			setCurrentPlayerState(PlayerState::in_air);
			animation_state = 4;
		}
		

	}
	else if (CurrentPlayerState == PlayerState::under_ground)
	{
		if (dive_clock.getElapsedTime().asMilliseconds() >=400)
		{
			setCurrentPlayerState(PlayerState::on_ground);
			animation_state = 0;
			updateAnimation();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && shoot_clock.getElapsedTime().asMilliseconds() >= 500 && CurrentPlayerState != PlayerState::under_ground)
	{
		shoot();
		shoot_clock.restart();

		current_frame = { 0 + 40 * animation_state, 67, 40, 19 };
	
	sprite.setTextureRect(current_frame);
	animation_clock.restart();

	}
	if (clock.getElapsedTime().asMilliseconds() >=16)
	{
		updatePhysics();
		clock.restart();
	}
	if(animation_clock.getElapsedTime().asMilliseconds() >= 80)
	updateAnimation();
}

void Player::updateAnimation()
{
	if (CurrentPlayerState == PlayerState::under_ground)
	{
			current_frame = { 0,20,40,46 };
	
	}
	else if (CurrentPlayerState == PlayerState::on_ground)
	{	
		animation_state++;
		if (animation_state >= 4) { animation_state = 0; }

			current_frame = { 0+40*animation_state, 0, 40, 19};
			
	}
	else if (CurrentPlayerState == PlayerState::in_air)
	{
		if (velocity.y > 0)
		{
			animation_state = 5;
		}
		else animation_state = 4;
		current_frame = { 0 + 40 * animation_state, 0, 40, 19 };
	}
	sprite.setTextureRect(current_frame);
	animation_clock.restart();
}

void Player::render(sf::RenderWindow* target)
{
	target->draw(sprite);
}

void Player::setHealth(int ile)
{
	if (ile < 0 && damage_clock.getElapsedTime().asMilliseconds() <= 500)
	{

	}
	else {
		health += ile;
		if (health > 4)
			health = 4;
		if(ile<0)damage_clock.restart();
	}
	if (health <= 0)
		IsAlive = false;
}

void Player::collision(Character* player)
{
}

void Player::addKeys(int ile)
{
	keys += ile;
}

int Player::getKeys()
{
	return keys;
}

PlayerState Player::getCurrentPlayerState()
{
	return CurrentPlayerState;
}

sf::Vector2f Player::getVelocity()
{
	return velocity;
}
