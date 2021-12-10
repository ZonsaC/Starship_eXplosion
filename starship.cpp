#include "game.h"
#include "starship.h"
#include <math.h>

//Constructor/Destructor

starship::starship() 
{
    initShip();
    initBullet();
}

starship::~starship() 
{
    
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
        ship.rotate(-1 * 0.04);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        ship.rotate(1 * 0.04);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        ship.move(sin((ship.getRotation() / 180) * 3.14) / 10, -1 * cos((ship.getRotation() / 180) * 3.14) / 10);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        ship.move(-1 * sin((ship.getRotation() / 180) * 3.14) / 10, cos((ship.getRotation() / 180) * 3.14) / 10);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spawnBulletBool == false)
    {
        bullet.setRotation(ship.getRotation());

        spawnBulletBool = true;

        spawnBullet();

    } else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        spawnBulletBool = false;
    
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
