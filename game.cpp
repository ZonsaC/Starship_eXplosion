#include "game.h"
#include "starship.h"


//Private functions
void Game::initVariables() 
{
    this->window = nullptr;
}
void Game::initWindow() 
{

    this->videoMode.width = 1280;
    this->videoMode.height = 720;
    
    starship::windowValues(videoMode.width, videoMode.height);

    this->window = new sf::RenderWindow(this->videoMode, "Window", sf::Style::Titlebar | sf::Style::Close);

    //this->window->setFramerateLimit(140);
}


//Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();

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
    starship::updateShip();
    enemy::updateAsteroids();

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
    starship::renderShip(*window);
    enemy::renderAsteroids(*window);
    this->window->display();
    
}




