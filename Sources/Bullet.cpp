#include "Bullet.h"

//constructors
Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_X, float dir_Y, float movementSpeed)
{
	this->p_bulletSprite.setTexture(*texture);
	this->p_bulletSprite.setPosition(pos_x, pos_y);
	this->p_direction.x = dir_X;
	this->p_direction.y = dir_Y;
	this->p_movementSpeed = movementSpeed;
}

Bullet::~Bullet()
{
}


//get
const sf::FloatRect Bullet::globalBounds() const
{
	return this->p_bulletSprite.getGlobalBounds();
}


//methodes
void Bullet::update()
{
	this->p_bulletSprite.move(p_movementSpeed * p_direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(p_bulletSprite);
}
