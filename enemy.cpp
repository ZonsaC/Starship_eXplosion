#include "game.h"
#include "enemy.h"

enemy::enemy() 
{
    
}

enemy::~enemy()
{

}

void enemy::initenemy(){
    texture.loadFromFile("assets/graphics/enemy.png");
    asteroid.setTexture(texture);
}
