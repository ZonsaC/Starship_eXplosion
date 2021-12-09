#include "game.h"
#include "enemy.h"

enemy::enemy() 
{
    
}

enemy::~enemy()
{

}

void enemy::renderAsteroids(sf::RenderTarget& target) 
{
    target.draw(asteroid);
}

void enemy::initenemy(){
    texture.loadFromFile("assets/graphics/enemy.png");
    asteroid.setTexture(texture);
}
