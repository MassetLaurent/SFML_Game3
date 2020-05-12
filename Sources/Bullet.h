#ifndef DEF_BULLET
#define DEF_BULLET

#include <iostream>
#include <SFML/Graphics.hpp>

class Bullet
{
private:
	//attributes
	sf::Sprite p_bulletSprite;
	sf::Vector2f p_direction;

	float p_movementSpeed;

	//private methodes
	void initTexture();
	void initSprite();

public:
	//constructor
	Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_X, float dir_Y, float movementSpeed);
	virtual ~Bullet();

	//get
	const sf::FloatRect globalBounds() const;

	//methodes
	void update();
	void render(sf::RenderTarget* target);
};
#endif // !DEF_BULLET
