#include "game.h"
#include "Starship.h"
#include <math.h>

//Constructor/Destructor
Starship::Starship()
{
}

Starship::Starship(int width, int height) 
{
    windowValues(width, height);
    //Init
    initVariables();
    initBullet(); 
    initShip();
}

Starship::~Starship() 
{
    
}

void Starship::initVariables() 
{
    // Dont change
    spawnBulletBool = false;
    destroyShipBool = false;
    attackV = false;
    speedCur = 0.f;
    tempRotation = 0.f;
    attack = 0.f;
    curDestroyTexture = 0.f;

    

    //Parameters
    acceleration = 0.000025f; //Speed the Ship Accelerates -- Normal 0.000025f - Fast 0.00005f - Slow 0.00001f
    speedMax = 0.1f; //Max Speed the Ship travels -- Normal 0.1f
    attackSpeed = 2000.f; //Max Attackspeed - HigherNumber = LongerWaittime 
    destroyTextureSpeed = 0.5f; //Texture changespeed when destroyed
}


//Init Stuff

void Starship::initShip()
{
    //Load Texture
    this->texture.loadFromFile("assets/graphics/starship.png", sf::IntRect(0 ,0 , 65, 75));
    ship.setTexture(this->texture);

    //Change Origin
    ship.setOrigin(ship.getLocalBounds().width / 2, ship.getLocalBounds().height / 2);
    ship.setPosition(videoMode.width / 2 , videoMode.height / 2);
    ship.setRotation(0.f);
}

void Starship::initBullet() 
{
    //Load Texture
    bulletTexture.loadFromFile("assets/graphics/bullet.png");
    bullet.setTexture(bulletTexture);

    //Change Origin
    bullet.setOrigin(bullet.getGlobalBounds().width / 2, bullet.getGlobalBounds().height / 2);
}

//Functions

void Starship::controlShip() 
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

    if(attack >= attackSpeed)
        {
            attackV = true;
        } else 
        {
            attack += 1;
            attackV = false;
        }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spawnBulletBool == false)
    {
        spawnBulletBool = true;

        if(attackV){
            attack = 0;
            spawnBullet();
        }
            

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

void Starship::windowValues(int width, int height) 
{
    Starship::videoMode.width = width;
    Starship::videoMode.height = height;
}

void Starship::spawnBullet() 
{
    bullet.setRotation(ship.getRotation());
    bullet.setPosition(ship.getPosition().x, ship.getPosition().y);

    bullets.push_back(bullet);
}

void Starship::destroyShip()
{
    if(ship.getPosition().x > videoMode.width || ship.getPosition().y > videoMode.height || ship.getPosition().x <= 0 || ship.getPosition().y <= 0){

        if(curDestroyTexture < texture.getSize().x * 4)
        {
            curDestroyTexture += destroyTextureSpeed;
            if(static_cast<int>(curDestroyTexture) % 65 == 0)
            {
                this->texture.loadFromFile("assets/graphics/starship.png", sf::IntRect(curDestroyTexture ,0 , 65, 75));
                ship.setTexture(this->texture);
            }
        }
        destroyShipBool = true;
    }
}

//Update Stuff

void Starship::updateShip(bool retry)
{
    if(retry)
    {
        initVariables();
        initBullet(); 
        initShip();
        destroyShipBool = false;
    }

    if(!destroyShipBool)
    {
        controlShip();
        updateBullet();
    } 
    destroyShip();
}

void Starship::updateBullet() 
{
    for(int i = 0; i < bullets.size(); i++)
    {
        //Move Bullets
        bullets[i].move(sin((bullets[i].getRotation() / 180) * 3.14) / 5, -1 * cos((bullets[i].getRotation() / 180) * 3.14) / 5);

        //Destroy Bullets outside of screen
        if(bullets[i].getPosition().x > videoMode.width + 30 || bullets[i].getPosition().y > videoMode.height + 30 || bullets[i].getPosition().x <= -30 || bullets[i].getPosition().y <= -30){
            bullets.erase(bullets.begin() + i);
        }
    }
        

}


// Render Stuff

void Starship::renderShip(sf::RenderTarget& target) 
{
    //Render Bullets
    for(auto &e : this->bullets)
    {
        target.draw(e);
    }

    //Render Ship
    target.draw(ship);
}
