#include "game.h"

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
    tutorial = new Tutorial(window);
    audio = new Audio();
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
        }
    }
}

void Game::update() 
{
    //Event polling
    this->pollEvent();

    if(tutorial->tutorialDone)
    {
        audio->updateAudio(screens->startBool, starship->destroyShipBool, screens->retryBool, screens->reloadBool, starship->bulletSpawned);
        screens->updateScreens(starship->destroyShipBool, starship->points, starship->ship);
        if (!screens->startBool)
        {
            enemy->updateEnemies(screens->retryBool, starship->enemies, starship->enemiesInt, starship->enemiesHealth, starship->points, starship->Hitboxes, screens->pauseBool);
            starship->updateShip(screens->retryBool, screens->startBool, screens->reloadBool, enemy->enemies, enemy->enemiesInt, enemy->enemiesHealth, enemy->Hitboxes, screens->pauseBool);
        }
    }

    tutorial->updateTutorial();
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
    screens->renderParallax(*window);

    if(!tutorial->tutorialDone)
        tutorial->renderTutorial(*window);

    if(tutorial->tutorialDone)
    {
        screens->renderScreens(*window);
        
        if (!screens->startBool)
        {
        starship->renderShip(*window);
        enemy->renderEnemies(*window, starship->shipHitbox, starship->bulletHitboxes);
        }         
    }
    


    this->window->display();
    
}




