#ifndef DEF_GAME
#define DEF_GAME

#include <map>
#include <vector>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:
	//window
	sf::RenderWindow* p_window;

	//ressources
	std::map<std::string, sf::Texture*> texturesMap;
	std::vector<Bullet*> p_bullets;

	//player
	Player* p_player;

	//Enemies
	std::vector<Enemy*> p_enemies;
	float p_spawnTimer;
	float p_spawnTimerMax;


	//privates methodes
	void initWindow();
	void initTextures();
	void initPlayer();
	void initEnemies();

public:
	//constructors
	Game();
	virtual ~Game();

	//methodes
	void run();
	void updatePollevent();
	void updateInputs();
	void updateBullets();
	void updateEnemies();
	void update();
	void render();
};

#endif // !DEF_GAME
