#ifndef __STARSHIP_H
#define __STARSHIP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>


class starship
{
public:
    sf::VideoMode videoMode;

    //Functions
    void windowValues(int, int);
    void spawnBullet();

    //Render
    void renderShip(sf::RenderTarget& target);
    void renderBullet(sf::RenderTarget& target);

    //Update
    void updateShip();
    void updateBullet();
    void controlShip();

    //Constructor/Destructor
    starship();
    ~starship();

private:
    //Ship
    sf::Sprite ship;
    sf::Texture texture;

    //Bullets
    sf::Sprite bullet;
    sf::Texture bulletTexture;
    std::vector<sf::Sprite> bullets;
    sf::Time time;

    //Variables
    int prevTimeBullet;
    int attackSpeed;
    bool spawnBulletBool;
    float speedMax;
    float acceleration;
    float speedCur;

    //Init
    void initVariables();
    void initShip();
    void initBullet();
};
#endif