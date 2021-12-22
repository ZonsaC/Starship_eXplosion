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
    initShield();
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
    shipDestroyedAnimation = false;
    bulletSpawned = false;

    shieldActive = false;

    upgradeChoice = 0;
    points = 0;
    upoints = 0;
    speedCur = 0.f;
    tempRotation = 0.f;
    spreadTempRotation = 0.f;
    attack = 0.f;
    curDestroyTexture = 0.f;
    rotationSpread = 0.f;
    ElapsedTime = 0.f;
    curDeathTexture = 0;
    enemyDeathDelay = 0.f;

    upgradeAttackspeed = 1.f;
    upgradeMovementspeed = 1.f;
    upgradeBulletScale = 1.f;
    upgradeSmallerShip = 1.f;
    upgradeSpread = 0;
    upgrades.clear();
    upgradesInt.clear();
    SperrUpgrade.clear();
    bullets.clear();
    bulletHitboxes.clear();
    enemyDeaths.clear();
    curDeathTextureInt.clear();

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

    //Change Ship
    ship.setScale(1, 1);
    ship.setOrigin(ship.getLocalBounds().left + ship.getLocalBounds().width / 2,
                   ship.getLocalBounds().top + ship.getLocalBounds().height / 2);
    ship.setPosition(videoMode.width / 2 , videoMode.height / 2);
    ship.setRotation(0.f);

    shipHitbox.setRadius(ship.getGlobalBounds().width * 0.45);
}

void Starship::initBullet() 
{
    //Load Texture
    bulletTexture.loadFromFile("assets/graphics/bullet.png");
    bullet.setTexture(bulletTexture);

    //Change Origin
    bullet.setOrigin(bullet.getGlobalBounds().width / 2, bullet.getGlobalBounds().height / 2);

    bulletHitbox.setOrigin(bullet.getOrigin());
    bulletHitbox.setFillColor(sf::Color::Transparent);
    bulletHitbox.setOutlineThickness(1.f);
    bulletHitbox.setOutlineColor(sf::Color::Magenta);
}

void Starship::initShield()
{
    shieldTexture.loadFromFile("assets/graphics/shield.png");
    upgradeShield.setTexture(shieldTexture);
    upgradeShield.setOrigin(upgradeShield.getGlobalBounds().width / 2, upgradeShield.getGlobalBounds().height / 2);
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

    bulletSpawned = false;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spawnBulletBool == false || upgradeAutofire)
    {
        spawnBulletBool = true;
        
        if(attackV){
            attack = 0;
            bulletSpawned = true;
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

    bulletHitbox.setRadius(bullet.getGlobalBounds().width / 2 * 0.7);
    bulletHitbox.setRotation(bullet.getRotation());
    bulletHitbox.setPosition(bullet.getPosition());

    bulletHitboxes.push_back(bulletHitbox);
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
        float dx = Hitboxes[i].getPosition().x - shipHitbox.getPosition().x;
        float dy = Hitboxes[i].getPosition().y - shipHitbox.getPosition().y;

        if(shipHitbox.getPosition().x > videoMode.width || 
           shipHitbox.getPosition().y > videoMode.height || 
           shipHitbox.getPosition().x <= 0 || 
           shipHitbox.getPosition().y <= 0 || 
           std::sqrt((dx * dx) + ( dy * dy)) <= (Hitboxes[i].getRadius()) + (shipHitbox.getRadius()) ||
           shipDestroyedAnimation)
            if(!shieldActive)
            {
                shipDestroyedAnimation = true;
                
                if(curDestroyTexture < texture.getSize().x * 4)
                {
                    curDestroyTexture += destroyTextureSpeed * 2;
                    if(static_cast<int>(curDestroyTexture) % 65 == 0)
                    {
                        this->texture.loadFromFile("assets/graphics/starship.png", sf::IntRect(curDestroyTexture ,0 , 65, 75));
                        ship.setTexture(this->texture);
                    }
                }
            destroyShipBool = true;
            }else {
                enemyDeaths.push_back(enemies[i]);
                curDeathTextureInt.push_back(0);
                enemies.erase(enemies.begin() + i);
                enemiesInt.erase(enemiesInt.begin() + i);
                enemiesHealth.erase(enemiesHealth.begin() + i);
                Hitboxes.erase(Hitboxes.begin() + i);
                shieldActive = false;
                for(int j = 0; j < SperrUpgrade.size(); j++)
                {
                    if(SperrUpgrade[j] == 7)
                    {
                        SperrUpgrade.erase(SperrUpgrade.begin() + j);
                    }
                }
            }

    }
}

void Starship::spreadBullets(sf::Sprite b) 
{
    /*

        Spreads Bullets
        Adds Bullets to vector

    */

    spreadTempRotation = rand() % 360;
    for(int i = 0; i < upgradeSpread; i++)
    {
        spreadTempRotation += 360 / upgradeSpread;
        bullet.setRotation(spreadTempRotation);
        bullet.setPosition(b.getPosition());

        bulletHitbox.setRotation(bullet.getRotation());
        bulletHitbox.setPosition(bullet.getPosition());

        bulletHitboxes.push_back(bulletHitbox);
        bullets.push_back(bullet);
    }
}

void Starship::enemyBulletIntersect()
{
    for(int i = 0; i < bullets.size(); i++)
        for(int j = 0; j < enemies.size(); j++)
        {
            float dx = Hitboxes[j].getPosition().x - bulletHitboxes[i].getPosition().x;
            float dy = Hitboxes[j].getPosition().y - bulletHitboxes[i].getPosition().y;
            if(std::sqrt((dx * dx) + ( dy * dy)) <= (Hitboxes[j].getRadius()) + (bulletHitboxes[i].getRadius()))
            {
                enemiesHealth[j] -= 1;

                if(upgradeSpread > 0 && enemiesHealth[j] == 0.f)
                    spreadBullets(bullets[i]);

                if(enemiesHealth[j] == 0.f)
                {
                    if(points < 100)
                    {   
                        points = points + 1;
                        upoints = upoints + 1;
                    } else if(points < 200)
                    {
                        points = points + 3;
                        upoints = upoints + 3; 
                    } else {
                        points = points + 5;
                        upoints = upoints + 5;
                    }
                        

                    enemyDeaths.push_back(enemies[j]);
                    curDeathTextureInt.push_back(0);
                    enemies.erase(enemies.begin() + j);
                    enemiesInt.erase(enemiesInt.begin() + j);
                    enemiesHealth.erase(enemiesHealth.begin() + j);
                    Hitboxes.erase(Hitboxes.begin() + j);
                }

                bullets.erase(bullets.begin() + i);
                bulletHitboxes.erase(bulletHitboxes.begin() + i);
            }
        }

}

void Starship::setShipHitbox()
{

    shipHitbox.setOrigin(shipHitbox.getLocalBounds().left + shipHitbox.getLocalBounds().width / 2,
                         shipHitbox.getLocalBounds().top + shipHitbox.getLocalBounds().height / 2);
    shipHitbox.setRotation(ship.getRotation());
    shipHitbox.setPosition(ship.getPosition());
    shipHitbox.setFillColor(sf::Color::Transparent);
    shipHitbox.setOutlineThickness(1.f);
    shipHitbox.setOutlineColor(sf::Color::Yellow);
}

void Starship::AnimateEnemyDeath()
{

    if(enemyDeaths.size() != 0)
    {
        if(enemyDeathDelay > 2.f)
        {
            enemyDeathDelay = 0.f;

            for(int i = 0; i < enemyDeaths.size(); i++)
            {
                if(curDeathTextureInt[i] == 870)
                {
                    enemyDeaths.erase(enemyDeaths.begin() + i);
                    curDeathTextureInt.erase(curDeathTextureInt.begin() + i);
                    break;
                }

                curDeathTextureInt[i] += 174;
                enemyDeathTexture.loadFromFile("assets/graphics/enemy.png", sf::IntRect(curDeathTextureInt[i] ,0 , 174, 174));
                enemyDeaths[i].setTexture(enemyDeathTexture);;
            }
        }else
        {
            enemyDeathDelay += 1.f;
        }
    }
}


//Update Stuff

void Starship::updateShip(bool retry, bool startBool, bool reload, std::vector<sf::Sprite> enemiesFromCpp, std::vector<int> enemiesIntfromCpp, std::vector<int> eH, std::vector<sf::CircleShape> Hxs)
{
    /*

        Inits when restart

    */
    enemiesHealth = eH;
    enemies = enemiesFromCpp;
    enemiesInt = enemiesIntfromCpp;
    Hitboxes = Hxs;


    ElapsedTime = clock.getElapsedTime().asMicroseconds() * 0.007;
    clock.restart();


    enemyBulletIntersect();

    if(retry || reload)
    {
        initVariables();
        initBullet(); 
        initShip();
        initShield();
    }

    if(!destroyShipBool)
    {
        controlShip();
        updateBullet();
        updateUpgrades();
    } 

    AnimateEnemyDeath();
    destroyShip();
    setShipHitbox();
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
        bulletHitboxes[i].scale(1 * upgradeBulletScale, 1 * upgradeBulletScale);

        bullets[i].setOrigin(bullets[i].getLocalBounds().width / 2, bullets[i].getLocalBounds().height / 2);
        bulletHitboxes[i].setOrigin(bullets[i].getLocalBounds().width / 2, bullets[i].getLocalBounds().height / 2);

        bullets[i].move(sin((bullets[i].getRotation() / 180) * 3.14) / 5 * ElapsedTime, -1 * cos((bullets[i].getRotation() / 180) * 3.14) / 5 * ElapsedTime);
        bulletHitboxes[i].move(sin((bulletHitboxes[i].getRotation() / 180) * 3.14) / 5 * ElapsedTime, -1 * cos((bulletHitboxes[i].getRotation() / 180) * 3.14) / 5 * ElapsedTime);

        //Destroy Bullets outside of screen
        if(bullets[i].getPosition().x > videoMode.width + 30 || bullets[i].getPosition().y > videoMode.height + 30 || bullets[i].getPosition().x <= -30 || bullets[i].getPosition().y <= -30){
            bullets.erase(bullets.begin() + i);
            bulletHitboxes.erase(bulletHitboxes.begin() + i);
        }
    }       

}

void Starship::updateUpgrades() 
{
    /*

        Upgrade System

    */

    if(shieldActive)
        upgradeShield.setPosition(ship.getPosition());

    //Choose Upgrade
    if(upoints < 10)
    {
        isUpgradeSet = true;
    }

    if(upoints >= 10 && points != 0 && isUpgradeSet)
    {
        isUpgradeSet = false;
        upoints -= 10;

        ValOk = false;
        while (!ValOk)
        {
            upgradeChoice = rand() % 7 + 1;
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

            case 7:
                upgradeTextureShield.loadFromFile("assets/graphics/upgradeShield.png");
                upgrade.setTexture(upgradeTextureShield);
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
                    upgradeBulletScale += 0.0025f;

                    if(upgradeBulletScale == 1.020f)
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
                    shipHitbox.scale(upgradeSmallerShip, upgradeSmallerShip);

                    if(upgradeSmallerShip < 0.85)
                    {
                        SperrUpgrade.push_back(6);
                        upgradeSmallerShip = 0.85;
                    }
                break;

                case 7:
                    shieldActive = true;
                    SperrUpgrade.push_back(7);
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
    for(auto &e : this->enemyDeaths)
    {
        target.draw(e);
    }

    //Render Ship
    target.draw(ship);

    renderUpgrades(target);
}

void Starship::renderUpgrades(sf::RenderTarget& target)
{
    for(auto &e : this->upgrades)
    {
        target.draw(e);
    }

    if(shieldActive)
        target.draw(upgradeShield);
}