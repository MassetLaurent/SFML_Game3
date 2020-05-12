#include "Game.h"


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



//constructors
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
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
}



//get


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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->p_bullets.push_back(new Bullet(this->texturesMap["BULLET"],
			this->p_player->getPosition().x, this->p_player->getPosition().y, 0.f, -1.f, 2.f));
	}
}

void Game::updateBullets()
{
	for (auto *b : this->p_bullets)
	{
		b->update();
	}
}

void Game::update()
{
	this->updatePollevent();
	this->updateInputs();
	this->updateBullets();
}

void Game::render()
{
	this->p_window->clear();

	//draw
	this->p_player->render(*this->p_window);

	for (auto *b : this->p_bullets)
	{
		b->render(this->p_window);
	}

	this->p_window->display();
}


