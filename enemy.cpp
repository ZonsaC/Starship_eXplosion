#include "game.h"
#include "enemy.h"

enemy::enemy() 
{
    
}

enemy::~enemy()
{

}

void enemy::initAsteroid(){
    texture.loadFromFile("assets/graphics/enemy.png");
    asteroid.setTexture(texture);
    asteroid.setOrigin(asteroid.getGlobalBounds().width/2, asteroid.getGlobalBounds().height/2);
    asteroid.setPosition(0, -1*asteroid.getGlobalBounds().height);
}

void enemy::windowValues(int width, int height) 
{
    enemy::videoMode.width = width;
    enemy::videoMode.height = height;
    initAsteroid();
}

void enemy::spawnAsteroid() 
{
    
    int pos = rand() % 4;

    switch (0)
    {
    case 0:
        //oben
         for (int i = 0; i < asteroids.size(); i++)
        {
            while (asteroid.getGlobalBounds().intersects(asteroids[i].getGlobalBounds()))
            {
                length = videoMode.width + asteroid.getGlobalBounds().width;
                
                asteroid.setPosition(rand() % length + (-1*asteroid.getGlobalBounds().width/2), -1*asteroid.getGlobalBounds().height);
            }
        }    
        break;
    case 1:
        //rechts
        break;
    case 2:
        //unten
        break;
    case 3:
        //links
        break;
    }
        
    std::cout << asteroid.getPosition().x << " " << asteroid.getPosition().y << "\n";
    asteroids.push_back(asteroid);
}

void enemy::updateAsteroids() 
{
    if (asteroids.size() < maxAsteroid)
    {
        if (asteroidSpawnTimer >= asteroidSpawnTimerMax)
        {
            spawnAsteroid();
            asteroidSpawnTimer = 0;
        }else
            asteroidSpawnTimer += 1;
    }
    
    
}

void enemy::renderAsteroids(sf::RenderTarget& target) 
{
    
    for (auto &i : asteroids)
    {
        target.draw(i);
    }
    
}
