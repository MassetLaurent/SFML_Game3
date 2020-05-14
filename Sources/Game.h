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

	//GUI
	sf::Font p_font;
	sf::Text p_pointText;

	//world
	sf::Texture p_worldBackgroundTexture;
	sf::Sprite p_worldBackground;

	//player
	Player* p_player;

	//Enemies
	std::vector<Enemy*> p_enemies;
	float p_spawnTimer;
	float p_spawnTimerMax;

	//privates methodes
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();

	void initPlayer();
	void initEnemies();

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
