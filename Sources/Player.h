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
	int p_hp;
	int p_hpMax;

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
	const int& getHp() const;
	const int& getHpMax() const;

	//set
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float pos_x, const float pos_y);
	void takeDamage(const int dmg);
	void setHp(const int nbHp);

	//methodes
	void move(const float dirX, const float dirY);
	void updateAttackCooldown();
	bool canAttack();
	void update();
	void render(sf::RenderTarget* target);
};

#endif // !DEF_PLAYER
