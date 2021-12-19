#include "game.h"
#include "starship.h"


//Private functions
void Game::initVariables() 
{
    this->window = nullptr;
}
void Game::initWindow() 
{    
    this->window = new sf::RenderWindow(sf::VideoMode(1920 ,1080), "Window",sf::Style::Close | sf::Style::Fullscreen);

    this->texture.loadFromFile("assets/graphics/background.png");
    background.setTexture(texture);
    this->window->setFramerateLimit(120);
}


//Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();

    starship = new Starship(window);
    enemy = new Enemy(window);
    screens = new Screens(window);
}

Game::~Game()
{
    delete this->window;

}

//Accessors
const bool Game::getWindowIsOpen() const
{
    return this->window->isOpen();
}


//Functions
void Game::pollEvent()
{
while(this->window->pollEvent(this->ev))
{
    screens->pollEvent(ev);
    switch(this->ev.type)
    {
        case sf::Event::Closed:
        this->window->close();
        break;
        case sf::Event::KeyPressed:
        if (this->ev.key.code == sf::Keyboard::Escape)
            this->window->close();
        break;
        }
    }
}

void Game::update() 
{
    //Event polling
    this->pollEvent();

    screens->updateScreens(starship->destroyShipBool, starship->points);
    if (!screens->startBool)
    {
        enemy->updateEnemies(screens->retryBool, starship->bullets, starship->enemies, starship->enemiesInt, starship->enemiesHealth, starship->points);
        starship->updateShip(screens->retryBool, screens->startBool, screens->reloadBool, enemy->enemies, enemy->enemiesInt, enemy->enemiesHealth);
    }

}

void Game::render() 
{
    /*
        @return void

        * clear old frame
        * render objects
        * display frame in window
        
        Renders the game objects.
    */

    this->window->clear(sf::Color(190, 63, 63, 255));

    //Draw game objects
    this->window->draw(background);

    if (!screens->startBool)
    {
    starship->renderShip(*window);
    enemy->renderEnemies(*window);
    } 

    screens->renderScreens(*window);


    this->window->display();
    
}




