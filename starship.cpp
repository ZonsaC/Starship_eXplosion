#include "game.h"
#include "starship.h"
#include <math.h>

//Constructor/Destructor

starship::starship() 
{
    initVariables();
    initShip();
    initBullet();
}

starship::~starship() 
{
    
}

void starship::initVariables() 
{
    spawnBulletBool = false;
    acceleration = 0.000025f;
    speedMax = 0.1f;
    speedCur = 0.f;
}

//Init Stuff

void starship::initShip()
{
    texture.loadFromFile("assets/graphics/starship.png");
    ship.setTexture(texture);

    ship.setOrigin(ship.getGlobalBounds().width / 2, ship.getGlobalBounds().height / 2);
    ship.setPosition(500 , 500);

    std::cout << videoMode.width << "\n";
    std::cout << videoMode.height << "\n";
}

void starship::initBullet() 
{
    bulletTexture.loadFromFile("assets/graphics/bullet.png");
    bullet.setTexture(bulletTexture);

    bullet.setOrigin(bullet.getGlobalBounds().width / 2, bullet.getGlobalBounds().height / 2);
}

//Functions

void starship::controlShip() 
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
        if(speedCur < speedMax)
            speedCur += acceleration;

        ship.move(sin((ship.getRotation() / 180) * 3.14) * speedCur, -1 * cos((ship.getRotation() / 180) * 3.14) * speedCur);
    }    

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(speedCur > speedMax * -1)
            speedCur -= acceleration;

        ship.move(sin((ship.getRotation() / 180) * 3.14) * speedCur, -1 * cos((ship.getRotation() / 180) * 3.14) * speedCur);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spawnBulletBool == false)
    {
        bullet.setRotation(ship.getRotation());

        spawnBulletBool = true;

        spawnBullet();

    } else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) spawnBulletBool = false;
    
    //Break
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(speedCur > 0)
            speedCur -= acceleration;
        if(speedCur < 0)
            speedCur += acceleration;

        ship.move(sin((ship.getRotation() / 180) * 3.14) * speedCur, -1 * cos((ship.getRotation() / 180) * 3.14) * speedCur);
    }
}

void starship::windowValues(int width, int height) 
{
    starship::videoMode.width = width;
    starship::videoMode.height = height;
}

void starship::spawnBullet() 
{
    bullet.setPosition(ship.getPosition().x, ship.getPosition().y);
}


//Update Stuff

void starship::updateShip()
{
    controlShip();
    updateBullet();
}

void starship::updateBullet() 
{
    bullet.move(sin((bullet.getRotation() / 180) * 3.14) / 5, -1 * cos((bullet.getRotation() / 180) * 3.14) / 5);
}


// Render Stuff

void starship::renderShip(sf::RenderTarget& target) 
{
    //Renders Ship
    target.draw(ship);
}

void starship::renderBullet(sf::RenderTarget& target) 
{
    target.draw(bullet);
}
