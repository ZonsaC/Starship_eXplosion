#include "game.h"
#include "enemy.h"

enemy::enemy() 
{
    initEnemy();
}

enemy::~enemy()
{

}

void enemy::renderAsteroids(sf::RenderTarget& target) 
{
    target.draw(asteroid);
}

void enemy::initEnemy(){
    texture.loadFromFile("assets/graphics/enemy.png");
    asteroid.setTexture(texture);
}
