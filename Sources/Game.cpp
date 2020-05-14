#include "Game.h"

//Init
void Game::initWindow()
{
	this->p_window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML Game 3", sf::Style::Titlebar | sf::Style::Close);
	this->p_window->setFramerateLimit(144);
	this->p_window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->texturesMap["BULLET"] = new sf::Texture();
	this->texturesMap["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initGUI()
{
	//load font
	if (!this->p_font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "! ERROR::GAME::updateGui() = Fail to load font PixellettersFull.\n";
	
	//init points
	this->p_pointText.setFont(this->p_font);
	this->p_pointText.setCharacterSize(36);
	this->p_pointText.setFillColor(sf::Color::White);
	this->p_pointText.setString("coucou");
	this->p_pointText.setPosition(20.f, 10.f);
}

void Game::initWorld()
{
	if (!this->p_worldBackgroundTexture.loadFromFile("Textures/background1.jpg"))
		std::cout << "! ERROR::GAME::initWorld = cant load background texture\n";
	this->p_worldBackground.setTexture(this->p_worldBackgroundTexture);
}

void Game::initPlayer()
{
	this->p_player = new Player();
}

void Game::initEnemies()
{
	this->p_spawnTimerMax = 50.f;
	this->p_spawnTimer = this->p_spawnTimerMax;
}


//constructors
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();

	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->p_window;
	delete this->p_player;

	//delete all textures in the map
	for (auto &t : this->texturesMap)
	{
		delete t.second;
	}
	
	//delete all bullets in the vector
	for (auto *b : this->p_bullets)
	{
		delete b;
	}

	//delete all enemies in the vector
	for (auto *enemy : this->p_enemies)
	{
		delete enemy;
	}
}


//methodes
void Game::run()
{
	while (this->p_window->isOpen())
	{
		this->update();
		this->render();
	}	
}

	//updates methodes
void Game::update()
{
	this->updatePollevent();
	this->updateInputs();

	this->p_player->update();
	this->updateCollision();
	
	this->updateEnemies();
	this->updateBullets();
	this->updateCombat();

	this->updateGUI();
	this->updateWorld();
}

void Game::updatePollevent()
{
	sf::Event ev;

	while (this->p_window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
			this->p_window->close();

		if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)
			this->p_window->close();
	}
}

void Game::updateInputs()
{
	//move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		this->p_player->move(-1.f, 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->p_player->move(1.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		this->p_player->move(0.f, -1.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->p_player->move(0.f, 1.f);

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) && this->p_player->canAttack())
	{
		this->p_bullets.push_back(new Bullet(this->texturesMap["BULLET"],
			this->p_player->getPosition().x + (this->p_player->getBounds().width / 2.f) - 5, 
			this->p_player->getPosition().y, 
			0.f, -1.f, 2.f));
	}
}


void Game::updateCollision()
{
	//left collision
	if (this->p_player->getBounds().left < 0.f)
		this->p_player->setPosition(0.f, this->p_player->getBounds().top);
	
	//right
	if (this->p_player->getBounds().left + this->p_player->getBounds().width > this->p_window->getSize().x)
		this->p_player->setPosition(this->p_window->getSize().x - this->p_player->getBounds().width, this->p_player->getBounds().top);
	
	//up
	if (this->p_player->getBounds().top < 0.f)
		this->p_player->setPosition(this->p_player->getBounds().left, 0.f);

	//down
	if (this->p_player->getBounds().top + this->p_player->getBounds().height > this->p_window->getSize().y)
		this->p_player->setPosition(this->p_player->getBounds().left, this->p_window->getSize().y - this->p_player->getBounds().height);
}


void Game::updateEnemies()
{
	//spawning enemies
	this->p_spawnTimer += 0.5f;

	if (this->p_spawnTimer >= this->p_spawnTimerMax)
	{
		this->p_enemies.push_back(new Enemy(rand() % this->p_window->getSize().x, -20.f));
		this->p_spawnTimer = 0.f;
	}	

	//update enemies
	unsigned counter(0);

	for (auto *enemy : this->p_enemies)
	{
		enemy->update();

		if (enemy->getBounds().top > this->p_window->getSize().y)
		{
			delete this->p_enemies.at(counter);
			this->p_enemies.erase(this->p_enemies.begin() + counter);
			counter--;
		}
		counter++;
	}
}

void Game::updateBullets()
{
	unsigned counter(0);

	for (auto *b : this->p_bullets)
	{
		b->update();

		if (b->globalBounds().top + b->globalBounds().height < -1.f)
		{
			delete this->p_bullets.at(counter);
			this->p_bullets.erase(this->p_bullets.begin() + counter);
			counter--;
		}
		counter++;
	}
}

void Game::updateCombat()
{
	for (size_t i(0); i < this->p_enemies.size(); i++)
	{
		bool enemy_Deleted(false);

		for (size_t j(0); j < this->p_bullets.size() && !enemy_Deleted; j++)
		{
			if (this->p_enemies[i]->getBounds().intersects(this->p_bullets[j]->globalBounds()))
			{
				delete this->p_enemies[i];
				this->p_enemies.erase(this->p_enemies.begin() + i);
				delete this->p_bullets[j];
				this->p_bullets.erase(this->p_bullets.begin() + j);
				enemy_Deleted = true;
			}
		}
	}
}


void Game::updateGUI()
{
	this->p_pointText.setString("lol");
}

void Game::updateWorld()
{
}


	//renders methodes
void Game::render()
{
	this->p_window->clear();

	//world
	this->renderWorld();
	
	//bullets
	for (auto *bullet : this->p_bullets)
	{
		bullet->render(this->p_window);
	}

	//Enemies
	for (auto *enemy : this->p_enemies)
	{
		enemy->render(this->p_window);
	}
	
	//player
	this->p_player->render(this->p_window);

	//GUI
	this->renderGUI();
	
	//affichage
	this->p_window->display();
}

void Game::renderGUI()
{
	this->p_window->draw(this->p_pointText);
}

void Game::renderWorld()
{
	this->p_window->draw(this->p_worldBackground);
}

