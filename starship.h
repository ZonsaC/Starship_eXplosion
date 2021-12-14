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
    void renderShip(sf::RenderTarget&);
    void renderUpgrades(sf::RenderTarget&);

    //Update
    void updateShip(bool, bool);
    void updateBullet();
    void updateUpgrades();
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

    //Upgrades
    sf::Sprite upgrade;
    sf::Texture upgradeTextureAttackspeed;
    sf::Texture upgradeTextureAutofire;
    std::vector<sf::Sprite> upgrades;
    std::vector<int> upgradesInt;

    //Variables
    bool isHold;
    bool isUpgradeSet;
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

    bool upgradeAutofire;
    int upgradeChoice;

    float upgradeAttackspeed;

    //Init
    void initVariables();
    void initShip();
    void initBullet();
};
#endif