#ifndef __SCREENS_H
#define __SCREENS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>


class Screens
{
public:
    bool startBool;
    bool endBool;
    bool retryBool;

    // Constructor / Destructor
    Screens();
    Screens(sf::RenderWindow*);
    ~Screens();

    //Functions
    void initValues(sf::RenderWindow*);

    //Update
    void updateScreens(bool, int);
    void updateEndtext();

    void updateMousepos();

    //Render
    void renderScreens(sf::RenderTarget& target);

    

private:
    sf::Vector2i mousePos;

    sf::VideoMode videoMode;
    sf::RenderWindow* window;


    //Startscreen
    sf::Text startText;

    sf::Font f_startText;

    sf::Sprite startScreen;
    sf::Sprite startButton;
    bool isHeld;

    sf::Texture t_startScreen;
    sf::Texture t_startButton;

    //Endscreen
    int Hue;
    float curIncSpeed;
    float increaseSpeed;

    sf::Text endText;

    //Retry Button
    sf::Text retryText;
    sf::Sprite retryButton;

    //Points
    sf::Text pointsText;
    int points;


    //Inits
    void initVariables();
    void initStartscreen();
    void initStartbutton();
    void initStarttext();
    void initEndscreen();
    void initRetrybutton();
    void initPointstext();

};



#endif