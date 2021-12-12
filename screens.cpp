#include "game.h"
#include "screens.h"

#include <math.h>


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
    initEndscreen();
}

Screens::~Screens() 
{
}


//Functions
void Screens::initVariables()
{
    isHeld = false;
    startBool = false;

    Hue = 0;
    increaseSpeed = 0.025f;
    curIncSpeed = 0.f;
}


void Screens::windowValues(sf::RenderWindow* pointerWindow) 
{
    window = pointerWindow;
    videoMode.width = window->getSize().x;
    videoMode.height = window->getSize().y;
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
    startButton.setPosition(startScreen.getPosition().x - 305, startScreen.getPosition().y + 200);
}

void Screens::initStarttext()
{
    f_startText.loadFromFile("assets/fonts/spaceXrebron.ttf");
    startText.setFont(f_startText);
    startText.setString("Start");
    startText.setCharacterSize(80);
    startText.setFillColor(sf::Color::White);

    startText.setOrigin(startText.getLocalBounds().left + startText.getLocalBounds().width / 2, 
                        startText.getLocalBounds().top + startText.getLocalBounds().height / 2);
    startText.setPosition(startButton.getPosition().x, startButton.getPosition().y);
}

void Screens::initEndscreen()
{
    endText.setFont(f_startText);
    endText.setCharacterSize(200);
    endText.setString("Game Over");

    endText.setOrigin(endText.getLocalBounds().left + endText.getLocalBounds().width / 2, 
                      endText.getLocalBounds().top + endText.getLocalBounds().height / 2);
    endText.setPosition(videoMode.width / 2, videoMode.height / 2);
}

//Update
void Screens::updateScreens(bool end) 
{
    //Init when ship is dead
    endBool = end;

    updateEndtext();
    
    //Leftclick Event
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(!isHeld)
        {
            isHeld = true;
            updateMousepos();

            //When mouse is on startButton
            if(startButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                startBool = true;
            }
        }

    } else isHeld = false;
}

void Screens::updateEndtext()
{
    //Fade in endText
    if(Hue < 255 && endBool)
        if(curIncSpeed < 255)
        {
            curIncSpeed += increaseSpeed;
            Hue = round(curIncSpeed);
            endText.setFillColor(sf::Color(255, 255, 255, Hue));
        }
}

void Screens::updateMousepos()
{
    this->mousePos = sf::Mouse::getPosition(*this->window);
}


//Render
void Screens::renderScreens(sf::RenderTarget& target) 
{
    if(!startBool){
        target.draw(startScreen);
        target.draw(startButton);
        target.draw(startText);
    }

    if(endBool)
        target.draw(endText);
}