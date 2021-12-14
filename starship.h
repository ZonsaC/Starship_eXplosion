#ifndef __STARSHIP_H
#define __STARSHIP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>


class Starship
{
public:
    bool destroyShipBool;
    unsigned points;
    sf::VideoMode videoMode;

    //Functions
    void windowValues(int, int);
    void spawnBullet();
    void destroyShip();
    void getPoints();

    //Render
    void renderShip(sf::RenderTarget& target);

    //Update
    void updateShip(bool, bool);
    void updateBullet();
    void controlShip();

    //Constructor/Destructor
    Starship();
    Starship(int, int);
    ~Starship();

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
    bool isHold;
    float destroyTextureSpeed;
    float curDestroyTexture;
    bool attackV;
    float attack;
    float attackSpeed;
    bool spawnBulletBool;
    float speedMax;
    float acceleration;
    float speedCur;
    float tempRotation;

    //Init
    void initVariables();
    void initShip();
    void initBullet();
};
#endif