#include "game.h"
#include "starship.h"
#include <math.h>

starship::starship() 
{
    initShip();
}

starship::~starship() 
{
    
}

void starship::initShip()
{
    texture.loadFromFile("assets/graphics/starship.png");
    ship.setTexture(texture);
    ship.setPosition(500 , 500);
    ship.setOrigin(32.5f, 37.5f);
}

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
        ship.move(-1 * sin((ship.getRotation() / 180) * 3.14) / 10,cos((ship.getRotation() / 180) * 3.14) / 10);
    }
}

void starship::windowValues(int width, int height) 
{
    std::cout << width << "\n";
    std::cout << height << "\n";
}

void starship::updateShip()
{
    controlShip();
}

void starship::renderShip(sf::RenderTarget& target) 
{
    //Renders Ship
    target.draw(ship);
}
