#include "Enemy.h"

//Init
void Enemy::initVariables()
{
	this->p_pointCount = rand() % 6 + 3;
	this->p_hp = this->p_hpMax;
	this->p_hpMax = static_cast<int>(this->p_pointCount);
	this->p_damage = this->p_pointCount;
	this->p_points = this->p_pointCount;
	this->p_type = 0;
	this->p_speed = static_cast<float>(this->p_pointCount * 0.2f);
}

void Enemy::initShape()
{
	this->p_shape.setRadius(this->p_pointCount * 3.f);
	this->p_shape.setPointCount(this->p_pointCount);
	this->p_shape.setFillColor(sf::Color(rand() % 225 + 30, rand() % 225 + 30, rand() % 225 + 30));
}

//constructors
Enemy::Enemy(float pos_X, float pos_Y)
{
	this->initVariables();
	this->initShape();
	this->p_shape.setPosition(pos_X, pos_Y);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->p_shape.getGlobalBounds();
}

const int Enemy::getPoints() const
{
	return this->p_points;
}

const int Enemy::getDamages() const
{
	return this->p_damage;
}

//methodes
void Enemy::update()
{
	this->p_shape.move(0.f, this->p_speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->p_shape);
}
