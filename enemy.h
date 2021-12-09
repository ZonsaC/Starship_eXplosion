#ifndef __ENEMY_H
#define __ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
class enemy
{
    private:
    
    sf::Sprite asteroid;
    sf::Texture spriteAsteroid;

    void enemy::initenemy();
    
    public:
        enemy();
        ~enemy();


};




#endif