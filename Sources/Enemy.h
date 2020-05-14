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
	float p_speed;

	void initShape();
	void initVariables();

public:
	//constructors
	Enemy(float pos_X, float pos_Y);
	virtual ~Enemy();

	//get
	const sf::FloatRect getBounds() const;

	//methodes
	void update();
	void render(sf::RenderTarget* target);
};

#endif // ! DEF_ENEMY