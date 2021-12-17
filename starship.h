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
    void spreadBullets();

    //Render
    void renderShip(sf::RenderTarget&);
    void renderUpgrades(sf::RenderTarget&);

    //Update
    void updateShip(bool, bool, bool);
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
    sf::Texture upgradeTextureMovementspeed;
    sf::Texture upgradeTextureBulletScale;
    sf::Texture upgradeTextureSpread;

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
    
    //to Test Spreadsystem
    bool isHold2 = false;

    //Variables that help upgrades
    int upgradeChoice;
    float rotationSpread;
    bool bulletSpread;

    //Variables that change Game behavior
    float upgradeAttackspeed;
    float upgradeMovementspeed;
    float upgradeBulletScale;
    int upgradeSpread;
    bool upgradeAutofire;

    //Init
    void initVariables();
    void initShip();
    void initBullet();
};
#endif