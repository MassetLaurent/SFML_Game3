#ifndef DEF_GAME
#define DEF_GAME

#include <map>
#include <vector>
#include <sstream>

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

	//GUI
	sf::Font p_font;
	sf::Text p_pointText;
	sf::Text p_gameOverText;
	sf::RectangleShape p_playerHpBar;
	sf::RectangleShape p_playerHpBarBack;

	//world
	sf::Texture p_worldBackgroundTexture;
	sf::Sprite p_worldBackground;
	
	//player
	Player* p_player;
	int p_points;

	//Enemies
	std::vector<Enemy*> p_enemies;
	float p_spawnTimer;
	float p_spawnTimerMax;

	//privates methodes
	void initWindow();
	void initTextures();
	void initVariables();
	void initWorld();
	void initPlayer();
	void initEnemies();
	void initGUI();


public:
	//constructors
	Game();
	virtual ~Game();

	//methodes
	void run();

		//updates methodes
	void update();
	void updatePollevent();
	void updateInputs();

	void updateCollision();
	
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	
	void updateGUI();
	void updateWorld();

		//renders methodes
	void render();
	void renderWorld();
	void renderGUI();
};

#endif // !DEF_GAME
