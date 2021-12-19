#include "game.h"
#include "starship.h"
#include <math.h>

#include <algorithm>

//Constructor/Destructor

Starship::Starship()
{
}

Starship::Starship(sf::RenderWindow* window) 
{
    windowValues(window);
    //Init
    initVariables();
    initBullet(); 
    initShip();
}

Starship::~Starship() 
{
    
}

void Starship::initVariables() 
{
    /*

        All Variables Stored

    */

    // Dont change
    destroyShipBool = false;
    upgradeAutofire = false;
    isUpgradeSet = false;
    spawnBulletBool = false;
    destroyShipBool = false;
    isHold = false;
    attackV = false;
    ValOk = false;

    bulletSpread = false;

    upgradeChoice = 0;
    points = 0;
    speedCur = 0.f;
    tempRotation = 0.f;
    attack = 0.f;
    curDestroyTexture = 0.f;
    rotationSpread = 0.f;
    ElapsedTime = 0.f;

    upgradeAttackspeed = 1.f;
    upgradeMovementspeed = 1.f;
    upgradeBulletScale = 1.f;
    upgradeSmallerShip = 1.f;
    upgradeSpread = 0;
    upgrades.clear();
    upgradesInt.clear();
    SperrUpgrade.clear();

    //Parameters
    acceleration = 0.000025f; //Speed the Ship Accelerates -- Normal 0.000025f - Fast 0.00005f - Slow 0.00001f
    speedMax = 0.07f; //Max Speed the Ship travels -- Normal 0.1f
    attackSpeed = 5000.f; //Max Attackspeed - HigherNumber = LongerWaittime 
    destroyTextureSpeed = 1.f; //Texture changespeed when destroyed
}


//Init Stuff

void Starship::initShip()
{
    //Load Texture
    this->texture.loadFromFile("assets/graphics/starship.png", sf::IntRect(0 ,0 , 65, 75));
    ship.setTexture(this->texture);

    //Change Origin
    ship.setScale(1, 1);
    ship.setOrigin(ship.getLocalBounds().width / 2, ship.getLocalBounds().height / 2);
    ship.setPosition(videoMode.width / 2 , videoMode.height / 2);
    ship.setRotation(0.f);
}

void Starship::initBullet() 
{
    //Load Texture
    bulletTexture.loadFromFile("assets/graphics/bullet.png");
    bullet.setTexture(bulletTexture);

    //Change Origin
    bullet.setOrigin(bullet.getGlobalBounds().width / 2, bullet.getGlobalBounds().height / 2);
}


//Functions

void Starship::controlShip() 
{
    /*

        Keyboard inputs
        - Controls Ship
        - Shoot on Space 
        - Movementspeed decrease on release

    */

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        ship.rotate(-1 * 0.05 * ElapsedTime);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        ship.rotate(1 * 0.05 * ElapsedTime);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(speedCur < speedMax * upgradeMovementspeed)
            speedCur += acceleration * ElapsedTime;

        ship.move(sin((ship.getRotation() / 180) * 3.14) * speedCur * ElapsedTime, -1 * cos((ship.getRotation() / 180) * 3.14) * speedCur * ElapsedTime);
        tempRotation = ship.getRotation();
    }

    if(attack * ElapsedTime >= attackSpeed / upgradeAttackspeed)
    {
        attackV = true;
    } else 
    {
        attack += 1;
        attackV = false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spawnBulletBool == false || upgradeAutofire)
    {
        spawnBulletBool = true;

        if(attackV){
            attack = 0;
            spawnBullet();
        }
    } else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) spawnBulletBool = false;
    
    //Breaking
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(speedCur > 0)
            speedCur -= acceleration * ElapsedTime * 0.5;
        if(speedCur < 0)
            speedCur = 0;

        ship.move(sin((tempRotation / 180) * 3.14) * speedCur * ElapsedTime, -1 * cos((tempRotation / 180) * 3.14) * speedCur * ElapsedTime);
    }
}

void Starship::windowValues(sf::RenderWindow* window) 
{
    /*

        Loads Window Values

    */

    videoMode.width = window->getSize().x;
    videoMode.height = window->getSize().y;
}

void Starship::spawnBullet() 
{
    /*

        Adds Bullet to Vector

    */
    bullet.setRotation(ship.getRotation());
    bullet.setPosition(ship.getPosition().x, ship.getPosition().y);

    bullets.push_back(bullet);
}

void Starship::destroyShip()
{
    /*

        Destroys Ship
        - Destroy Animation
        - Set destroy bool

    */

    for(int i = 0; i < enemies.size(); i++)
    {
        if(ship.getPosition().x > videoMode.width || 
           ship.getPosition().y > videoMode.height || 
           ship.getPosition().x <= 0 || 
           ship.getPosition().y <= 0 || 
           ship.getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
           {
            if(curDestroyTexture < texture.getSize().x * 4)
            {
                curDestroyTexture += destroyTextureSpeed * 10;
                if(static_cast<int>(curDestroyTexture) % 65 == 0)
                {
                    this->texture.loadFromFile("assets/graphics/starship.png", sf::IntRect(curDestroyTexture ,0 , 65, 75));
                    ship.setTexture(this->texture);
                }
            }
        destroyShipBool = true;
        }

    }
}

void Starship::spreadBullets(sf::Sprite b) 
{
    /*

        Spreads Bullets
        Adds Bullets to vector

    */

    tempRotation = rand() % 360;
    for(int i = 0; i < upgradeSpread; i++)
    {
        tempRotation += 360 / upgradeSpread;
        bullet.setRotation(tempRotation);
        bullet.setPosition(b.getPosition());

        bullets.push_back(bullet);
    }
}

void Starship::enemyBulletIntersect()
{
    for(int i = 0; i < bullets.size(); i++)
        for(int j = 0; j < enemies.size(); j++)
        {
            if(bullets[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds()))
            {
                enemiesHealth[j] -= 1;

                if(enemiesHealth[j] == 0.f)
                {
                    points++;

                    enemies.erase(enemies.begin() + j);
                    enemiesInt.erase(enemiesInt.begin() + j);
                    enemiesHealth.erase(enemiesHealth.begin() + j);
                    
                }

                if(upgradeSpread > 0)
                    spreadBullets(bullets[i]);

                bullets.erase(bullets.begin() + i);
            }
        }

}
//Update Stuff

void Starship::updateShip(bool retry, bool startBool, bool reload, std::vector<sf::Sprite> enemiesFromCpp, std::vector<int> enemiesIntfromCpp, std::vector<int> eH)
{
    /*

        Inits when restart

    */
    enemiesHealth = eH;
    enemies = enemiesFromCpp;
    enemiesInt = enemiesIntfromCpp;


    ElapsedTime = clock.getElapsedTime().asMicroseconds() * 0.007;
    clock.restart();

    enemyBulletIntersect();

    if(retry || reload)
    {
        initVariables();
        initBullet(); 
        initShip();
    }

    if(!destroyShipBool)
    {
        controlShip();
        updateBullet();
        updateUpgrades();
    } 

    destroyShip();
}

void Starship::updateBullet() 
{
    /*

        Moves Bullets
        Destroys Bullets outside from screen

    */


    for(int i = 0; i < bullets.size(); i++)
    {
        //Move Bullets
        bullets[i].scale(1 * upgradeBulletScale, 1 * upgradeBulletScale);
        bullets[i].setOrigin(bullets[i].getLocalBounds().width / 2, bullets[i].getLocalBounds().height / 2);

        bullets[i].move(sin((bullets[i].getRotation() / 180) * 3.14) / 5 * ElapsedTime, -1 * cos((bullets[i].getRotation() / 180) * 3.14) / 5 * ElapsedTime);

        //Destroy Bullets outside of screen
        if(bullets[i].getPosition().x > videoMode.width + 30 || bullets[i].getPosition().y > videoMode.height + 30 || bullets[i].getPosition().x <= -30 || bullets[i].getPosition().y <= -30){
            bullets.erase(bullets.begin() + i);
        }
    }       

}

void Starship::updateUpgrades() 
{
    /*

        Upgrade System

    */

    //Choose Upgrade
    if(points % 10 != 0)
    {
        isUpgradeSet = true;
    }
    if(points % 10 == 0 && points != 0 && isUpgradeSet)
    {
        isUpgradeSet = false;

        ValOk = false;
        while (!ValOk)
        {
            upgradeChoice = rand() % 6 + 1;
            if(!(std::find(SperrUpgrade.begin(), SperrUpgrade.end(), upgradeChoice) != SperrUpgrade.end()) || upgradeChoice == 0) ValOk = true;
        }
            

        switch(upgradeChoice)
        {
            case 1:
                upgradeTextureAttackspeed.loadFromFile("assets/graphics/upgradeAttackspeed.png");
                upgrade.setTexture(upgradeTextureAttackspeed);
            break;

            case 2:
                upgradeTextureAutofire.loadFromFile("assets/graphics/upgradeAutofire.png");
                upgrade.setTexture(upgradeTextureAutofire);
            break;

            case 3:
                upgradeTextureMovementspeed.loadFromFile("assets/graphics/upgradeMovementspeed.png");
                upgrade.setTexture(upgradeTextureMovementspeed);
            break;

            case 4:
                upgradeTextureBulletScale.loadFromFile("assets/graphics/upgradeBulletScale.png");
                upgrade.setTexture(upgradeTextureBulletScale);
            break;

            case 5:
                upgradeTextureSpread.loadFromFile("assets/graphics/upgradeSpread.png");
                upgrade.setTexture(upgradeTextureSpread);
            break;

            case 6:
                upgradeTextureSmall.loadFromFile("assets/graphics/upgradeSmallShip.png");
                upgrade.setTexture(upgradeTextureSmall);
            break;
        }

        upgrade.setOrigin(upgrade.getGlobalBounds().width / 2, upgrade.getGlobalBounds().height / 2);
        upgrade.setPosition(rand() % static_cast<int>(videoMode.width - this->upgrade.getGlobalBounds().width / 2), rand() % static_cast<int>(videoMode.height - this->upgrade.getGlobalBounds().height / 2));
            
        upgradesInt.push_back(upgradeChoice);
        upgrades.push_back(upgrade);
    }

    for(int i = 0; i < upgrades.size(); i++)
        if(ship.getGlobalBounds().intersects(upgrades[i].getGlobalBounds()))
        {
            switch(upgradesInt[i])
            {
                case 1:
                    upgradeAttackspeed += 0.5f;
                break;
                
                case 2:
                    upgradeAutofire = true;
                    SperrUpgrade.push_back(2);
                break;

                case 3:
                    upgradeMovementspeed += 0.1f;

                    if(upgradeMovementspeed > 2.2)
                    {
                        SperrUpgrade.push_back(3);
                        upgradeMovementspeed = 2.2;
                    }
                        
                break;

                case 4:
                    upgradeBulletScale += 0.005f;

                    if(upgradeBulletScale == 1.025f)
                    {
                        SperrUpgrade.push_back(4);
                    }
                        
                break;

                case 5:
                    do
                        upgradeSpread += 1;
                    while(!(360 % upgradeSpread == 0));

                    if(upgradeSpread > 36)
                    {
                        SperrUpgrade.push_back(5);
                        upgradeSpread = 36;
                    }
                        
                break;

                case 6:
                    upgradeSmallerShip -= 0.025;
                    ship.scale(upgradeSmallerShip, upgradeSmallerShip);
                    std::cout << upgradeSmallerShip << "\n";

                    if(upgradeSmallerShip < 0.85)
                    {
                        SperrUpgrade.push_back(6);
                        upgradeSmallerShip = 0.85;
                    }
                break;
            }

            upgrades.erase(upgrades.begin() + i);
            upgradesInt.erase(upgradesInt.begin() + i);
        }
}


// Render Stuff

void Starship::renderShip(sf::RenderTarget& target) 
{
    //Render Bullets
    for(auto &e : this->bullets)
    {
        target.draw(e);
    }

    //Render Ship
    target.draw(ship);

    if(!destroyShipBool)
        renderUpgrades(target);
}

void Starship::renderUpgrades(sf::RenderTarget& target)
{
    for(auto &e : this->upgrades)
    {
        target.draw(e);
    }
}