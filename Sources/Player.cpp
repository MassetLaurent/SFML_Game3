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

void Player::initVariables()
{
	this->p_movementSpeed = 3.f;
	this->p_attackCooldownMax = 20.f;
	this->p_attackCooldown = this->p_attackCooldownMax;
}


//constructors
Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();
}

Player::~Player()
{
}


//get
const sf::Vector2f& Player::getPosition()
{
	return this->p_playerSprite.getPosition();
}


//methodes
void Player::move(const float dirX, const float dirY)
{
	this->p_playerSprite.move(this->p_movementSpeed * dirX, this->p_movementSpeed * dirY);
}

void Player::updateAttackCooldown()
{
	if (this->p_attackCooldown < this->p_attackCooldownMax)
		this->p_attackCooldown += 0.5f;
}

bool Player::canAttack()
{
	if (this->p_attackCooldown >= this->p_attackCooldownMax)
	{
		this->p_attackCooldown = 0.f;
		return true;
	}

		return false;
}

void Player::update()
{
	this->updateAttackCooldown();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->p_playerSprite);
}
