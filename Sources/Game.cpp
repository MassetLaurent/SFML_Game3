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

			//std::cout << this->p_bullets.size() << "\n";
		}
			counter++;
	}
}

void Game::updateEnemies()
{
	if (this->p_spawnTimer >= this->p_spawnTimerMax)
	{
		this->p_enemies.push_back(new Enemy(rand() % this->p_window->getSize().x, 10.f));
		this->p_spawnTimer = 0.f;
	}
	this->p_spawnTimer += 0.5f;

	for (auto *enemy : this->p_enemies)
	{
		enemy->update();
	}
}

void Game::update()
{
	this->updatePollevent();
	this->updateInputs();
	this->updateBullets();
	this->p_player->update();
	this->updateEnemies();
}

void Game::render()
{
	this->p_window->clear();

	//player
	this->p_player->render(this->p_window);

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

	//affichage
	this->p_window->display();
}


