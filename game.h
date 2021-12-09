#ifndef __GAME_H
#define __GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include "starship.h"
#include "enemy.h"

/*
    Class that acts as the game engine.
    Wrapper class.
*/

class Game : public starship, public enemy
{
private:
    //Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;


    //Private function
    void initVariables();
    void initWindow();

public:
    //Constructors / Destructors
    Game();
    virtual ~Game();

    //Accessors
    const bool getWindowIsOpen() const;

    //Functions
    void pollEvent();
    void update();
    void render();
};

#endif