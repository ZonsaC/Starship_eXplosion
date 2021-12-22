#ifndef __SCREENS_H
#define __SCREENS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <fstream>


class Screens
{
public:
    std::string username;
    std::string filename = "Leaderboard.txt";
    
    bool startBool;
    bool endBool;
    bool retryBool;
    bool reloadBool;
    bool leaderboardBool;

    // Constructor / Destructor
    Screens();
    Screens(sf::RenderWindow*);
    ~Screens();

    //Functions
    void initValues(sf::RenderWindow*);
    void StoreInFile();
    void LoadFromFile();
    void LoadLeaderboardValues();

    //Poll Event
    void pollEvent(sf::Event);

    //Update
    void updateScreens(bool, int, sf::Sprite);
    void updateEndtext();
    void updateParallax(sf::Sprite);
    

    void updateMousepos();

    //Render
    void renderScreens(sf::RenderTarget& target);
    void renderParallax(sf::RenderTarget& target);


private:
    sf::Vector2i mousePos;

    sf::VideoMode videoMode;
    sf::RenderWindow* window;

    sf::Clock clock;
    float ElapsedTime;


    //Startscreen
    sf::Text startText;

    sf::Font f_startText;

    sf::Sprite startScreen;
    sf::Sprite startButton;

    sf::Sprite leaderboardButton;
    sf::Sprite leaderboard;
    sf::Text leaderboardUsername;
    sf::Text leaderboardPoint;
    std::vector<sf::Text> leaderboardUsernames;
    std::vector<sf::Text> leaderboardPoints;
    sf::Text tempText;


    bool isHeld;
    bool isHeld2;
    bool isHeld3;
    
    float curfadeIn;

    sf::Texture t_startScreen;
    sf::Texture t_startButton;
    sf::Texture t_leaderboardButton;
    sf::Texture t_leaderboard;

    //Endscreen
    int Hue;
    float curIncSpeed;
    float increaseSpeed;

    sf::Text endText;
    sf::Text enterUsername;
    

    //Retry Button
    sf::Text retryText;
    sf::Sprite retryButton;

    //Points
    sf::Text pointsText;
    int points;

    //Parallax
    sf::Sprite parallax;
    sf::Texture parallaxTexture;


    void startFadein();

    //Inits
    void initVariables();
    void initStartscreen();
    void initStartbutton();
    void initLeaderboard();
    void initStarttext();
    void initEndscreen();
    void initRetrybutton();
    void initPointstext();
    void initParallax();

};



#endif