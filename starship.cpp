#include "game.h"
#include "starship.h"
#include <math.h>

//Constructor/Destructor

starship::starship() 
{
    //Init
    initVariables();
    initShip();
    initBullet();
    void windowValues(int , int );
}

starship::~starship() 
{
    
}

void starship::initVariables() 
{
    // Dont change
    spawnBulletBool = false;
    speedCur = 0.f;
    tempRotation = 0.f;

    //Parameters
    acceleration = 0.00001f; //Speed the Ship Accelerates -- Normal 0.000025f - Fast 0.00005f - Slow 0.00001f
    speedMax = 0.1f; //Max Speed the Ship travels -- Normal 0.1f

    
}


//Init Stuff

void starship::initShip()
{
    //Load Texture
    texture.loadFromFile("assets/graphics/starship.png");
    ship.setTexture(texture);

    //Change Origin
    ship.setOrigin(ship.getGlobalBounds().width / 2, ship.getGlobalBounds().height / 2);
    ship.setPosition(500 , 500);
}

void starship::initBullet() 
{
    //Load Texture
    bulletTexture.loadFromFile("assets/graphics/bullet.png");
    bullet.setTexture(bulletTexture);

    //Change Origin
    bullet.setOrigin(bullet.getGlobalBounds().width / 2, bullet.getGlobalBounds().height / 2);
}

//Functions

void starship::controlShip() 
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        ship.rotate(-1 * 0.06);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        ship.rotate(1 * 0.06);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(speedCur < speedMax)
            speedCur += acceleration;

        ship.move(sin((ship.getRotation() / 180) * 3.14) * speedCur, -1 * cos((ship.getRotation() / 180) * 3.14) * speedCur);
    }    

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spawnBulletBool == false)
    {
        
        prevTimeBullet = time.asSeconds();

        spawnBulletBool = true;

        spawnBullet(); 
    } else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) spawnBulletBool = false;
    
    //Breaking
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        tempRotation = ship.getRotation();

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(speedCur > 0)
            speedCur -= acceleration;
        if(speedCur < 0)
            speedCur += acceleration;

        ship.move(sin((tempRotation / 180) * 3.14) * speedCur, -1 * cos((tempRotation / 180) * 3.14) * speedCur);
    }
}

void starship::windowValues(int width, int height) 
{
    starship::videoMode.width = width;
    starship::videoMode.height = height;
}

void starship::spawnBullet() 
{
    bullet.setRotation(ship.getRotation());
    bullet.setPosition(ship.getPosition().x, ship.getPosition().y);

    bullets.push_back(bullet);
}


//Update Stuff

void starship::updateShip()
{
    controlShip();
    updateBullet();
}

void starship::updateBullet() 
{
    for(int i = 0; i < bullets.size(); i++)
        bullets[i].move(sin((bullets[i].getRotation() / 180) * 3.14) / 5, -1 * cos((bullets[i].getRotation() / 180) * 3.14) / 5);
}


// Render Stuff

void starship::renderShip(sf::RenderTarget& target) 
{
    //Render Bullets
    for(auto &e : this->bullets)
    {
        target.draw(e);
    }

    //Render Ship
    target.draw(ship);
}
