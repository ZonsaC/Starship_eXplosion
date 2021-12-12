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

    // Constructor / Destructor
    Screens();
    Screens(sf::RenderWindow*);
    ~Screens();

    //Functions
    void windowValues(sf::RenderWindow*);

    //Update
    void updateScreens(bool);
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

    //Inits
    void initVariables();
    void initStartscreen();
    void initStartbutton();
    void initStarttext();
    void initEndscreen();

};



#endif