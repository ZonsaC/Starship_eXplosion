#ifndef __ENEMY_H
#define __ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <iostream>

class Enemy
{
private:
    sf::Texture texture;
    sf::Sprite enemy;
    std::vector<sf::Sprite> enemies;
    std::vector<int> enemiesInt;

    int maxEnemy;

    int enemySpawnTimer;
    int enemySpawnTimerMax;

    float randomEnemyScale;
    int enemySpawnPos;

    //Init Stuff
    void initVariables();
    void initEnemy();


    //Functions
    void windowValues(sf::RenderWindow*);

    void spawnEnemy();
    void moveEnemies();
    void destroyEnemies();


public:
    sf::VideoMode videoMode;
    Enemy();
    Enemy(sf::RenderWindow*);
    ~Enemy();
    
    void updateEnemies();
    void renderEnemies(sf::RenderTarget& target);

};




#endif