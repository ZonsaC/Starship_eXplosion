#include "game.h"
#include "starship.h"


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
    ship.setPosition(0, 0);
    
    
}

void starship::renderShip(sf::RenderTarget& target) 
{
    target.draw(ship);
}
