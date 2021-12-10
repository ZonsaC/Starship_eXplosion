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

    void windowValues(int, int);
    void spawnBullet();

    void renderShip(sf::RenderTarget& target);
    void renderBullet(sf::RenderTarget& target);
    void updateShip();
    void updateBullet();


    starship();
    ~starship();

private:
    sf::Sprite ship;
    sf::Texture texture;

    sf::Sprite bullet;
    sf::Texture bulletTexture;
    std::vector<sf::Sprite> bullets;

    bool spawnBulletBool = false;
    int xMovement;
    int yMovement;


    void initShip();
    void initBullet();

    void controlShip();


};






#endif