#ifndef __TUTORIAL_H
#define __TUTORIAL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

class Tutorial
{
public:
Tutorial();
Tutorial(sf::RenderWindow*);
~Tutorial();

bool tutorialDone;

void updateTutorial();
void renderTutorial(sf::RenderTarget& target);
void fadein();
void skipTutorial();

private:

float curFadein;
float fadeinSpeed;
float fadeoutSpeed;
float waitTime;
float curwaitTime;
float Hue;
bool fadeOut;

sf::Texture tutorialTexture;
sf::Sprite tutorialScreen;

sf::Font font;
sf::Text skipText;

void initVariables();
void initTutorial();
void windowValues(sf::RenderWindow*);
sf::VideoMode videoMode;

};


#endif