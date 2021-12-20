#include "game.h"
#include "enemy.h"
#include "math.h"

Enemy::Enemy() 
{  
}

Enemy::Enemy(sf::RenderWindow* window) 
{
    windowValues(window);

    initVariables();
    initEnemy();
}

Enemy::~Enemy()
{

}

void Enemy::initVariables()
{
    isHold = false;

    maxEnemy = 10;

    enemySpawnTimer = 0;
    enemySpawnTimerMax = 5000;

    randomEnemyScale = 0;
    enemySpawnPos = 0;
    enemiesHealth.clear();
    enemiesInt.clear();
    enemies.clear();
    Hitboxes.clear();
}

void Enemy::initEnemy(){
    texture.loadFromFile("assets/graphics/enemy.png");
    enemy.setTexture(texture);
}


//Funktionen

void Enemy::windowValues(sf::RenderWindow* window) 
{
    videoMode.width = window->getSize().x;
    videoMode.height = window->getSize().y;
}

void Enemy::spawnEnemy() 
{
    randomEnemyScale = rand() % 100 + 50;

    enemy.setScale(randomEnemyScale / 100, randomEnemyScale / 100);
    enemy.setOrigin(enemy.getLocalBounds().left + enemy.getLocalBounds().width / 2,
                    enemy.getLocalBounds().top + enemy.getLocalBounds().height / 2);

    //Spawns Enemy
    enemySpawnPos = rand() % 4;
    switch (enemySpawnPos)
    {
        case 0:
            //oben
                enemy.setPosition(rand() % static_cast<int>(videoMode.width + enemy.getGlobalBounds().width * 2) + (-1 * enemy.getGlobalBounds().width), (-1 * enemy.getGlobalBounds().height / 2));
                enemy.setRotation(rand() % 40 + 160);
            break;
        case 1:
            //rechts
                enemy.setPosition((videoMode.width + enemy.getGlobalBounds().width / 2), rand() % static_cast<int>(videoMode.height + enemy.getGlobalBounds().height * 2) + (-1 * enemy.getGlobalBounds().height));
                enemy.setRotation(rand() % 40 + 250);
            break;
        case 2:
            //unten
                enemy.setPosition(rand() % static_cast<int>(videoMode.width + enemy.getGlobalBounds().width * 2) + (-1 * enemy.getGlobalBounds().width),  (videoMode.height + enemy.getGlobalBounds().height));
                enemy.setRotation(rand() % 40 + 340);
            break;
        case 3:
            //links
                enemy.setPosition((-1 * enemy.getGlobalBounds().width / 2), rand() % static_cast<int>(videoMode.height + enemy.getGlobalBounds().height * 2) + (-1 * enemy.getGlobalBounds().height));
                enemy.setRotation(rand() % 40 + 70);
            break;
    }
    

    if(points < 50)
    {
        enemiesHealth.push_back(1);
        enemy.setColor(sf::Color(255, 255, 255));
    } else
    if(points < 100)
    {
        enemiesHealth.push_back(2);
        enemy.setColor(sf::Color(190, 190, 255));
    } else
    if(points < 150)
    {
        enemiesHealth.push_back(3);
        enemy.setColor(sf::Color(160, 140, 255));
    } else
    if(points < 200)
    {
        enemiesHealth.push_back(5);
        enemy.setColor(sf::Color(160, 140, 150));
    }else
    {
        enemiesHealth.push_back(10);
        enemy.setColor(sf::Color(160, 70, 110));
    }

    //Set Hitbox
    Hitbox.setRadius(enemy.getGlobalBounds().width / 2 * 0.7);
    Hitbox.setFillColor(sf::Color::Transparent);
    Hitbox.setOutlineThickness(1.f);
    Hitbox.setOutlineColor(sf::Color::Red);
    Hitbox.setOrigin(Hitbox.getRadius(), Hitbox.getRadius());

    Hitbox.setRotation(enemy.getRotation());
    Hitbox.setPosition(enemy.getPosition());


    Hitboxes.push_back(Hitbox);
    enemiesInt.push_back(enemySpawnPos);
    enemies.push_back(enemy);
}

void Enemy::moveEnemies()
{
    for(int i = 0; i < enemies.size(); i++)
    {
        enemies[i].move(sin((enemies[i].getRotation() / 180) * 3.14) * 0.05 * ElapsedTime, -1 * cos((enemies[i].getRotation() / 180) * 3.14) * 0.05 * ElapsedTime);
        Hitboxes[i].move(sin((Hitboxes[i].getRotation() / 180) * 3.14) * 0.05 * ElapsedTime, -1 * cos((Hitboxes[i].getRotation() / 180) * 3.14) * 0.05 * ElapsedTime);
    }
}

void Enemy::destroyEnemies()
{
    for(int i = 0; i < enemies.size(); i++)
    {
        switch (enemiesInt[i])
        {
        case 0:
            if(enemies[i].getPosition().y > videoMode.height + enemies[i].getGlobalBounds().height){
                enemies.erase(enemies.begin() + i);
                enemiesInt.erase(enemiesInt.begin() + i);
                enemiesHealth.erase(enemiesHealth.begin() + i);
                Hitboxes.erase(Hitboxes.begin() + i);
            }
            break;
        case 1:
            if(enemies[i].getPosition().x < -1 * enemies[i].getGlobalBounds().width){
                enemies.erase(enemies.begin() + i);
                enemiesInt.erase(enemiesInt.begin() + i);
                enemiesHealth.erase(enemiesHealth.begin() + i);
                Hitboxes.erase(Hitboxes.begin() + i);
            }
            break;
        case 2:
            if(enemies[i].getPosition().y < -1 * enemies[i].getGlobalBounds().height){
                enemies.erase(enemies.begin() + i);
                enemiesInt.erase(enemiesInt.begin() + i);
                enemiesHealth.erase(enemiesHealth.begin() + i);
                Hitboxes.erase(Hitboxes.begin() + i);
            }
            break;
        case 3:
            if(enemies[i].getPosition().x > videoMode.width + enemies[i].getGlobalBounds().width){
                enemies.erase(enemies.begin() + i);
                enemiesInt.erase(enemiesInt.begin() + i);
                enemiesHealth.erase(enemiesHealth.begin() + i);
                Hitboxes.erase(Hitboxes.begin() + i);
            }
            break;
        }
    }
}

void Enemy::showHitboxes()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::H) && !isHold)
        {
            isHold = true;

            if(showHitboxesBool)
                showHitboxesBool = false;
            else
            if(!showHitboxesBool)
                showHitboxesBool = true;
        } else 
            if(!sf::Keyboard::isKeyPressed(sf::Keyboard::H)) isHold = false;
}

void Enemy::updateEnemies(bool retry, std::vector<sf::Sprite> e, std::vector<int> eI, std::vector<int> eH, int p, std::vector<sf::CircleShape> Hxs) 
{
    ElapsedTime = clock.getElapsedTime().asMicroseconds() * 0.007;
    clock.restart();

    points = p;
    enemies = e;
    enemiesInt = eI;
    enemiesHealth = eH;
    Hitboxes = Hxs;

    if(retry)
    {
        initVariables();
        initEnemy();
    }
        

    if (enemies.size() < maxEnemy)
    {
        if (enemySpawnTimer * ElapsedTime >= enemySpawnTimerMax)
        {
            spawnEnemy();
            enemySpawnTimer = 0;
        }else
            enemySpawnTimer += 1;
    }

    showHitboxes();
    moveEnemies();
    destroyEnemies();
}

void Enemy::renderEnemies(sf::RenderTarget& target, sf::RectangleShape shipHitbox, std::vector<sf::CircleShape> bulletHitboxes) 
{
    for (auto &i : enemies)
    {
        target.draw(i);
    }

    if(showHitboxesBool)
    {
        for (auto &i : Hitboxes)
        {
            target.draw(i);
        }
        for (auto &i : bulletHitboxes)
        {
            target.draw(i);
        }
        target.draw(shipHitbox);
    }
        
}
