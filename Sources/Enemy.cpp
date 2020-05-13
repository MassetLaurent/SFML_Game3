#include "Enemy.h"

//Init
void Enemy::initShape()
{
	this->p_shape.setRadius(rand() % 20 + 7);
	this->p_shape.setPointCount(rand() % 6 + 3);
}

void Enemy::initVariables()
{
	this->p_hp = this->p_hpMax;
	this->p_hpMax = 10;
	this->p_damage = 1;
	this->p_points = 5;
	this->p_type = 0;
}


//constructors
Enemy::Enemy(float pos_X, float pos_Y)
{
	this->initShape();
	this->initVariables();
	this->p_shape.setPosition(pos_X, pos_Y);
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->p_shape);
}


//methodes
