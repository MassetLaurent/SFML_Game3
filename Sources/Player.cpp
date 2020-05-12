#include "Player.h"

void Player::initTexture()
{
	if (!this->p_playerTexture.loadFromFile("Textures/ship2.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE could not load texture file\n";
	}
}

void Player::initSprite()
{
	this->p_playerSprite.setTexture(this->p_playerTexture);

	//resize the sprite
	this->p_playerSprite.scale(sf::Vector2f(0.1f, 0.1f));
}

//constructors
Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->p_movementSpeed = 5.f;
}

Player::~Player()
{
}

const sf::Vector2f& Player::getPosition()
{
	return this->p_playerSprite.getPosition();
}



//get


//methodes
void Player::move(const float dirX, const float dirY)
{
	this->p_playerSprite.move(this->p_movementSpeed * dirX, this->p_movementSpeed * dirY);
}

void Player::update()
{
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->p_playerSprite);
}
