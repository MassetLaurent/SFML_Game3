#ifndef DEF_ENEMY
#define DEF_ENEMY

#include <SFML/Graphics.hpp>

class Enemy
{
private:
	//attributes
	sf::CircleShape p_shape;

	int p_hp;
	int p_hpMax;
	int p_damage;
	int p_points;
	int p_type;

	void initShape();
	void initVariables();

public:
	//constructors
	Enemy(float pos_X, float pos_Y);
	virtual ~Enemy();

	//get

	//methodes
	void update();
	void render(sf::RenderTarget* target);
};

#endif // ! DEF_ENEMY