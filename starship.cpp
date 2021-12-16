#include "game.h"
#include "starship.h"
#include <math.h>

//Constructor/Destructor

Starship::Starship()
{
}

Starship::Starship(int width, int height) 
{
    windowValues(width, height);
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
    // Dont change
    upgradeAutofire = false;
    isUpgradeSet = false;
    spawnBulletBool = false;
    destroyShipBool = false;
    isHold = false;
    attackV = false;
    upgradeChoice = 0;
    points = 0;
    speedCur = 0.f;
    tempRotation = 0.f;
    attack = 0.f;
    curDestroyTexture = 0.f;

    upgradeAttackspeed = 1.f;
    upgradeMovementspeed = 1.f;
    upgradeBulletScale = 1.f;
    upgradeMoreBullets = 0;
    upgrades.clear();
    upgradesInt.clear();

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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        ship.rotate(-1 * 0.06);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        ship.rotate(1 * 0.06);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(speedCur < speedMax * upgradeMovementspeed)
            speedCur += acceleration;

        ship.move(sin((ship.getRotation() / 180) * 3.14) * speedCur, -1 * cos((ship.getRotation() / 180) * 3.14) * speedCur);
    }    

    if(attack >= attackSpeed / upgradeAttackspeed)
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        tempRotation = ship.getRotation();

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(speedCur > 0)
            speedCur -= acceleration;
        if(speedCur < 0)
            speedCur += acceleration;

        ship.move(sin((tempRotation / 180) * 3.14) * speedCur, -1 * cos((tempRotation / 180) * 3.14) * speedCur);
    }
}

void Starship::windowValues(int width, int height) 
{
    Starship::videoMode.width = width;
    Starship::videoMode.height = height;
}

void Starship::spawnBullet() 
{
    bullet.setRotation(ship.getRotation());
    bullet.setPosition(ship.getPosition().x, ship.getPosition().y);

    bullets.push_back(bullet);
}

void Starship::destroyShip()
{
    if(ship.getPosition().x > videoMode.width || ship.getPosition().y > videoMode.height || ship.getPosition().x <= 0 || ship.getPosition().y <= 0){

        if(curDestroyTexture < texture.getSize().x * 4)
        {
            curDestroyTexture += destroyTextureSpeed;
            if(static_cast<int>(curDestroyTexture) % 65 == 0)
            {
                this->texture.loadFromFile("assets/graphics/starship.png", sf::IntRect(curDestroyTexture ,0 , 65, 75));
                ship.setTexture(this->texture);
            }
        }
        destroyShipBool = true;
    }
}

void Starship::getPoints() 
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P) && !isHold)
    {
        isHold = true;
        points += 5;
        std::cout << points << "\n";

    } else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::P)) isHold = false;

}


//Update Stuff

void Starship::updateShip(bool retry, bool startBool)
{
    if(retry)
    {
        initVariables();
        initBullet(); 
        initShip();

        destroyShipBool = false;
    }

    if(!destroyShipBool)
    {
        controlShip();
        updateBullet();

        if(startBool){
            getPoints();
            updateUpgrades();
        }

    } 

    destroyShip();
}

void Starship::updateBullet() 
{

    for(int i = 0; i < bullets.size(); i++)
    {
        //Move Bullets
        bullets[i].scale(1 * upgradeBulletScale, 1 * upgradeBulletScale);
        bullets[i].setOrigin(bullets[i].getLocalBounds().width / 2, bullets[i].getLocalBounds().height / 2);

        bullets[i].move(sin((bullets[i].getRotation() / 180) * 3.14) / 5, -1 * cos((bullets[i].getRotation() / 180) * 3.14) / 5);

        //Destroy Bullets outside of screen
        if(bullets[i].getPosition().x > videoMode.width + 30 || bullets[i].getPosition().y > videoMode.height + 30 || bullets[i].getPosition().x <= -30 || bullets[i].getPosition().y <= -30){
            bullets.erase(bullets.begin() + i);
        }
    }       

}

void Starship::updateUpgrades() 
{

    //Chose Upgrade
    if(points % 10 != 0)
    {
        isUpgradeSet = true;
    }
    if(points % 10 == 0 && points != 0 && isUpgradeSet)
    {
        isUpgradeSet = false;

        upgradeChoice = rand() % 4 + 1;
        if(upgradeAutofire)
            while(upgradeChoice == 2)
                upgradeChoice = rand() % 4 + 1;

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
                break;

                case 3:
                    upgradeMovementspeed += 0.1f;
                break;

                case 4:
                    upgradeBulletScale += 0.000075;
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