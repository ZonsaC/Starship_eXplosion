#ifndef __SCREENS_H
#define __SCREENS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

class Screens
{
public:
Screens();
Screens(int, int);
~Screens();

void updateScreens();

void renderScreens(sf::RenderTarget& target);


private:



};



#endif