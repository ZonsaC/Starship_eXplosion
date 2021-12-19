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
    sf::Clock clock;
    float ElapsedTime;

    std::vector<sf::Sprite> enemies;
    std::vector<int> enemiesInt;
    std::vector<int> enemiesHealth;
    std::vector<sf::CircleShape> Hitboxes;
    sf::RectangleShape shipHitbox;
    sf::CircleShape bulletHitbox;
    std::vector<sf::CircleShape> bulletHitboxes;

    std::vector<sf::Sprite> bullets;

    //Functions
    void windowValues(sf::RenderWindow*);
    void spawnBullet();
    void destroyShip();
    void enemyBulletIntersect();
    void spreadBullets(sf::Sprite);
    void setShipHitbox();

    //Render
    void renderShip(sf::RenderTarget&);
    void renderUpgrades(sf::RenderTarget&);

    //Update
    void updateShip(bool, bool, bool, std::vector<sf::Sprite>, std::vector<int>, std::vector<int>, std::vector<sf::CircleShape>);
    void updateBullet();
    void updateUpgrades();
    void controlShip();

    //Constructor/Destructor
    Starship();
    Starship(sf::RenderWindow*);
    ~Starship();

private:
    //Ship
    sf::Sprite ship;
    sf::Texture texture;


    //Bullets
    sf::Sprite bullet;
    sf::Texture bulletTexture;
    sf::Time time;

    //Upgrades
    sf::Sprite upgrade;
    sf::Texture upgradeTextureAttackspeed;
    sf::Texture upgradeTextureAutofire;
    sf::Texture upgradeTextureMovementspeed;
    sf::Texture upgradeTextureBulletScale;
    sf::Texture upgradeTextureSpread;
    sf::Texture upgradeTextureSmall;

    std::vector<sf::Sprite> upgrades;
    std::vector<int> upgradesInt;

    std::vector<int> SperrUpgrade;

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
    bool ValOk;
    
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
    float upgradeSmallerShip;

    //Init
    void initVariables();
    void initShip();
    void initBullet();
};
#endif