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
    sf::CircleShape Hitbox;

    sf::Clock clock;
    float ElapsedTime;
    
    bool isHold;
    bool pauseBool;
    bool showHitboxesBool = false;

    int points;
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
    void showHitboxes();


public:
    std::vector<sf::Sprite> enemies;
    std::vector<int> enemiesHealth;
    std::vector<int> enemiesInt;
    std::vector<sf::CircleShape> Hitboxes;

    sf::VideoMode videoMode;

    Enemy();
    Enemy(sf::RenderWindow*);
    ~Enemy();
    
    void updateEnemies(bool , std::vector<sf::Sprite>, std::vector<int>, std::vector<int>, int, std::vector<sf::CircleShape>, bool);
    void renderEnemies(sf::RenderTarget& target, sf::CircleShape, std::vector<sf::CircleShape>);

};




#endif