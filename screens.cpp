#include "game.h"
#include "screens.h"


// Constructor / Destructor
Screens::Screens() 
{
}

Screens::Screens(sf::RenderWindow* pointerWindow) 
{
    windowValues(pointerWindow);
    initVariables();
    initStartscreen();
    initStartbutton();
    initStarttext();
}

Screens::~Screens() 
{
    
}

void Screens::windowValues(sf::RenderWindow* pointerWindow) 
{
    window = pointerWindow;
    videoMode.width = window->getSize().x;
    videoMode.height = window->getSize().y;
}


//Functions
void Screens::initVariables()
{
    isHeld = false;
    startBool = false;
}
void Screens::initStartscreen()
{
    //load image
    t_startScreen.loadFromFile("assets/graphics/menu.png");
    startScreen.setTexture(t_startScreen);

    //set origin + pos
    startScreen.setOrigin(startScreen.getGlobalBounds().width / 2, startScreen.getGlobalBounds().height / 2);
    startScreen.setPosition(videoMode.width / 2, videoMode.height / 2);
}

void Screens::initStartbutton()
{
    //load image
    t_startButton.loadFromFile("assets/graphics/button.png");
    startButton.setTexture(t_startButton);

    //set origin + pos
    startButton.setOrigin(startButton.getGlobalBounds().width / 2, startButton.getGlobalBounds().height / 2);
    startButton.setPosition(startScreen.getPosition().x - 300, startScreen.getPosition().y + 200);
}

void Screens::initStarttext()
{
    f_startText.loadFromFile("assets/fonts/spaceXrebron.ttf");
    startText.setFont(f_startText);
    startText.setString("Start");
    startText.setCharacterSize(80);
    startText.setFillColor(sf::Color::White);

    startText.setOrigin(startText.getGlobalBounds().width / 2, startText.getGlobalBounds().height / 2);
    startText.setPosition(startButton.getPosition().x - 10, startButton.getPosition().y - 20);
}

//Update
void Screens::updateScreens() 
{
    
    
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(!isHeld)
        {
            isHeld = true;

            updateMousepos();
            if(startButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                startBool = true;
            }
        }

    } else isHeld = false;
}

void Screens::updateMousepos()
{
    this->mousePos = sf::Mouse::getPosition(*this->window);
}


//Render
void Screens::renderScreens(sf::RenderTarget& target) 
{
    target.draw(startScreen);
    target.draw(startButton);
    target.draw(startText);
}