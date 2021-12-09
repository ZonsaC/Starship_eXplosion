#include "game.h"

//Private functions
void Game::initVariables() 
{
    this->window = nullptr;
}
void Game::initWindow() 
{
    this->videoMode.width = 1280;
    this->videoMode.height = 720;

    this->window = new sf::RenderWindow(this->videoMode, "Window", sf::Style::Titlebar | sf::Style::Close);
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

    this->window->clear(sf::Color(255, 0, 0, 255));

    //Draw game objects

    this->window->display();
}




