#include "game.h"
#include "tutorial.h"


//Constructor / Destructor
Tutorial::Tutorial()
{}

Tutorial::Tutorial(sf::RenderWindow* window) 
{
    windowValues(window);
    initVariables();
    initTutorial();
}

Tutorial::~Tutorial() 
{
}

//Functions
void Tutorial::initVariables()
{
    curFadein = 0.f;
    fadeinSpeed = 1.f;
    fadeoutSpeed = 2.f;

    curwaitTime = 0.f;

    fadeOut = false;
    tutorialDone = false;
}

void Tutorial::initTutorial()
{
    tutorialTexture.loadFromFile("assets/graphics/tutorial.png");
    tutorialScreen.setTexture(tutorialTexture);
    tutorialScreen.setOrigin(tutorialScreen.getGlobalBounds().width / 2, tutorialScreen.getGlobalBounds().height / 2);
    tutorialScreen.setPosition(videoMode.width / 2, videoMode.height / 2);
}

void Tutorial::windowValues(sf::RenderWindow* window) 
{
    videoMode.width = window->getSize().x;
    videoMode.height = window->getSize().y;
}

void Tutorial::fadein()
{

    if(curFadein < 255 && !fadeOut)
    {
        curFadein += fadeinSpeed;
        tutorialScreen.setColor(sf::Color(255, 255, 255, curFadein));
    } else
    {
        if(curwaitTime < 300.f)
        {
            fadeOut = true;
            curwaitTime += 1.f;
        } else 
        {
            curFadein -= fadeoutSpeed;
            tutorialScreen.setColor(sf::Color(255, 255, 255, curFadein));
            
        }
    }
    std::cout << curFadein << "\n";
    if(curFadein < 0)
        tutorialDone = true;
}

//Update
void Tutorial::updateTutorial() 
{
    fadein();
}

//Render
void Tutorial::renderTutorial(sf::RenderTarget& target) 
{
    target.draw(tutorialScreen);
}