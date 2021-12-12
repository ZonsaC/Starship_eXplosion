#ifndef __ENEMY_H
#define __ENEMY_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
class Enemy
{
private:
sf::VideoMode videoMode;
sf::Texture texture;
sf::Sprite asteroid;
std::vector<sf::Sprite> asteroids;
int maxAsteroid = 4;
int length = 0;
int asteroidSpawnTimer = 0;
int asteroidSpawnTimerMax = 100;
void initAsteroid();


public:
    void windowValues(int, int);
    Enemy();
    Enemy(int, int);
    ~Enemy();
    
    void spawnAsteroid();
    void updateAsteroids();
    void renderAsteroids(sf::RenderTarget& target);

};




#endif