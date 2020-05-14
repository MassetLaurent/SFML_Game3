#ifndef DEF_ENEMY
#define DEF_ENEMY

#include <SFML/Graphics.hpp>

class Enemy
{
private:
	//attributes
	sf::CircleShape p_shape;
	unsigned p_pointCount;
	int p_hp;
	int p_hpMax;
	int p_damage;
	int p_points;
	int p_type;
	float p_speed;

	void initVariables();
	void initShape();

public:
	//constructors
	Enemy(float pos_X, float pos_Y);
	virtual ~Enemy();

	//get
	const sf::FloatRect getBounds() const;
	const int getPoints() const;
	const int getDamages() const;

	//methodes
	void update();
	void render(sf::RenderTarget* target);
};

#endif // ! DEF_ENEMY