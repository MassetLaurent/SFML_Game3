#ifndef DEF_PLAYER
#define DEF_PLAYER
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player
{
private:
	//attibutes
	sf::Texture p_playerTexture;
	sf::Sprite p_playerSprite;
	float p_movementSpeed;
	float p_attackCooldown;
	float p_attackCooldownMax;

	//privates methodes
	void initTexture();
	void initSprite();
	void initVariables();


public:
	//constructors
	Player();
	virtual ~Player();

	//get
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getBounds() const;

	//methodes
	void move(const float dirX, const float dirY);
	void updateAttackCooldown();
	bool canAttack();
	void update();
	void render(sf::RenderTarget* target);
};

#endif // !DEF_PLAYER
