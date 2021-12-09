#ifndef __STARSHIP_H
#define __STARSHIP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
class Game;

class starship
{
private:

    sf::Sprite ship;
    sf::Texture texture;

    void initShip();

public:

    void renderShip(sf::RenderTarget& target);
    void updateShip();

    starship();
    ~starship();
};






#endif