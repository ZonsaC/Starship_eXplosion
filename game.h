#ifndef __GAME_H
#define __GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <ctime>
#include "starship.h"
#include "enemy.h"
#include "screens.h"

/*
    Class that acts as the game engine.
    Wrapper class.
*/

class Game
{
private:
    Starship* starship;
    Enemy* enemy;
    Screens* screens;

    //Private function
    void initVariables();
    void initWindow();

public:
    //Window
    sf::RenderWindow* window;
    sf::Vector2i mousePos;
    sf::Event ev;
    sf::Texture texture;
    sf::Sprite background;

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