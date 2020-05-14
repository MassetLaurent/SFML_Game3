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

void Game::initVariables()
{
	this->p_points = 0;
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

	this->p_player->setPosition((this->p_window->getSize().x / 2) - (this->p_player->getBounds().width / 2),
		this->p_window->getSize().y - (this->p_player->getBounds().height / 2));
}

void Game::initEnemies()
{
	this->p_spawnTimerMax = 50.f;
	this->p_spawnTimer = this->p_spawnTimerMax;
}

void Game::initGUI()
{
	//load font
	if (!this->p_font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "! ERROR::GAME::updateGui() = Fail to load font PixellettersFull.\n";
	
	//init points
	this->p_pointText.setFont(this->p_font);
	this->p_pointText.setCharacterSize(24);
	this->p_pointText.setFillColor(sf::Color::White);
	this->p_pointText.setString("0");
	this->p_pointText.setPosition(20.f, 20.f);

	//init game over text
	this->p_gameOverText.setFont(this->p_font);
	this->p_gameOverText.setCharacterSize(96);
	this->p_gameOverText.setFillColor(sf::Color::Red);
	this->p_gameOverText.setString("GAME OVER !");
	this->p_gameOverText.setStyle(sf::Text::Underlined | sf::Text::Bold);
	this->p_gameOverText.setPosition(
		(this->p_window->getSize().x / 2.f) - (this->p_gameOverText.getGlobalBounds().width / 2.f), 
		(this->p_window->getSize().y / 2.f) - (this->p_gameOverText.getGlobalBounds().height + 20.f)
	);

	//player health barre
	this->p_playerHpBar.setSize(sf::Vector2f(200.f, 10.f));
	this->p_playerHpBar.setFillColor(sf::Color::Red);
	this->p_playerHpBar.setPosition(20.f, 10.f);

	//player health barre background
	this->p_playerHpBarBack = this->p_playerHpBar;
	this->p_playerHpBarBack.setFillColor(sf::Color::Transparent);
	this->p_playerHpBarBack.setOutlineThickness(1.f);
	this->p_playerHpBarBack.setOutlineColor(sf::Color::Yellow);
}


//constructors
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initVariables();
	this->initWorld();
	this->initPlayer();
	this->initEnemies();
	this->initGUI();
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
		this->updatePollevent();
		if(this->p_player->getHp() > 0)
			this->update();

		this->render();
	}	
}

	//updates methodes
void Game::update()
{
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
	else if (this->p_player->getBounds().left + this->p_player->getBounds().width > this->p_window->getSize().x)
		this->p_player->setPosition(this->p_window->getSize().x - this->p_player->getBounds().width, this->p_player->getBounds().top);
	
	//up
	if (this->p_player->getBounds().top < 0.f)
		this->p_player->setPosition(this->p_player->getBounds().left, 0.f);

	//down
	else if (this->p_player->getBounds().top + this->p_player->getBounds().height > this->p_window->getSize().y)
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

		//if enemy go out of the screen
		if (enemy->getBounds().top > this->p_window->getSize().y)
		{
			delete this->p_enemies.at(counter);
			this->p_enemies.erase(this->p_enemies.begin() + counter);
		}

		//if enemy hit player
		else if (enemy->getBounds().intersects(this->p_player->getBounds()))
		{
			//remove health for the player
			this->p_player->takeDamage(enemy->getDamages());
			
			//remove point in score
			this->p_points -= enemy->getPoints();

			if (this->p_points < 0)
				this->p_points = 0;

			delete this->p_enemies.at(counter);
			this->p_enemies.erase(this->p_enemies.begin() + counter);
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
				//give point for player
				this->p_points += this->p_enemies[i]->getPoints();

				//delete enemy and bullet
				delete this->p_enemies[i];
				this->p_enemies.erase(this->p_enemies.begin() + i);
				delete this->p_bullets[j];
				this->p_bullets.erase(this->p_bullets.begin() + j);
				enemy_Deleted = true;
			}
		}
	}
}

void Game::updateWorld()
{
}

void Game::updateGUI()
{
	//player hp bar
	float percent = static_cast<float>(this->p_player->getHp()) / this->p_player->getHpMax();

	this->p_playerHpBar.setSize(sf::Vector2f(this->p_playerHpBarBack.getSize().x * percent, this->p_playerHpBarBack.getSize().y));

	//point counter text
	std::stringstream ss; 

	ss << "Points : " << this->p_points << std::endl;

	this->p_pointText.setString(ss.str());
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
	this->p_window->draw(this->p_playerHpBarBack);
	this->p_window->draw(this->p_playerHpBar);

	if(this->p_player->getHp() <= 0)
		this->p_window->draw(this->p_gameOverText);
}

void Game::renderWorld()
{
	this->p_window->draw(this->p_worldBackground);
}

