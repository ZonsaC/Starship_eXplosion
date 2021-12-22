#include "game.h"
#include "screens.h"

#include <math.h>
#include <sstream>
#include <fstream>


// Constructor / Destructor
Screens::Screens()
{
}

Screens::Screens(sf::RenderWindow* pointerWindow)
{
    initValues(pointerWindow);
    initPointstext();
    initVariables();
    initStartscreen();
    initStartbutton();
    initLeaderboard();
    initStarttext();
    initEndscreen();
    initRetrybutton();
    initParallax();
}

Screens::~Screens()
{
}


//Functions
void Screens::initVariables()
{
    isHeld = false;
    isHeld2 = false;

    startBool = true;
    retryBool = false;
    reloadBool = false;
    leaderboardBool = false;

    Hue = 0;
    increaseSpeed = 0.025f;
    curIncSpeed = 0.f;
    curfadeIn = 0.f;
}

void Screens::initValues(sf::RenderWindow* pointerWindow)
{
    window = pointerWindow;
    videoMode.width = window->getSize().x;
    videoMode.height = window->getSize().y;
}

void Screens::initStartscreen()
{
    //load image
    t_startScreen.loadFromFile("assets/graphics/menu.png");
    startScreen.setTexture(t_startScreen);

    //set origin + pos
    startScreen.setOrigin(startScreen.getGlobalBounds().width / 2, startScreen.getGlobalBounds().height / 2);
    startScreen.setPosition(videoMode.width / 2, videoMode.height / 2);
}

void Screens::initStartbutton()
{
    //load image
    t_startButton.loadFromFile("assets/graphics/button.png");
    startButton.setTexture(t_startButton);

    //set origin + pos
    startButton.setOrigin(startButton.getGlobalBounds().width / 2, startButton.getGlobalBounds().height / 2);
    startButton.setPosition(startScreen.getPosition().x - 310, startScreen.getPosition().y + 200);
}

void Screens::initLeaderboard()
{
    t_leaderboardButton.loadFromFile("assets/graphics/leaderboardButton.png");
    leaderboardButton.setTexture(t_leaderboardButton);
    leaderboardButton.setOrigin(leaderboardButton.getGlobalBounds().width / 2, leaderboardButton.getGlobalBounds().height / 2);
    leaderboardButton.setPosition(startScreen.getPosition().x + 380, startScreen.getPosition().y + 200);

    t_leaderboard.loadFromFile("assets/graphics/leaderboard.png");
    leaderboard.setTexture(t_leaderboard);
    leaderboard.setOrigin(leaderboard.getGlobalBounds().width / 2, leaderboard.getGlobalBounds().height / 2);
    leaderboard.setPosition(videoMode.width / 2, videoMode.height / 2);

    leaderboardUsername.setFont(f_startText);
    leaderboardUsername.setCharacterSize(50.f);

    leaderboardPoint.setFont(f_startText);
    leaderboardPoint.setCharacterSize(50.f);
}

void Screens::initStarttext()
{
    f_startText.loadFromFile("assets/fonts/spaceXrebron.ttf");
    startText.setFont(f_startText);
    startText.setString("Start");
    startText.setCharacterSize(80);
    startText.setFillColor(sf::Color::White);

    startText.setOrigin(startText.getLocalBounds().left + startText.getLocalBounds().width / 2,
                        startText.getLocalBounds().top + startText.getLocalBounds().height / 2);
    startText.setPosition(startButton.getPosition().x, startButton.getPosition().y);
}

void Screens::initEndscreen()
{
    //Init Endtext
    endText.setFont(f_startText);
    endText.setCharacterSize(200);
    endText.setString("Game Over");

    endText.setOrigin(endText.getLocalBounds().left + endText.getLocalBounds().width / 2,
                      endText.getLocalBounds().top + endText.getLocalBounds().height / 2);
    endText.setPosition(videoMode.width / 2, videoMode.height / 2 - 100);

    //Init EnterUsername
    enterUsername.setFont(f_startText);
    enterUsername.setCharacterSize(40);

    enterUsername.setPosition(videoMode.width / 2 - 150, videoMode.height / 2 + 200);
}

void Screens::initRetrybutton()
{
    //Inits Button
    retryButton.setTexture(t_startButton);
    retryButton.setOrigin(retryButton.getGlobalBounds().width / 2, retryButton.getGlobalBounds().height / 2);
    retryButton.setPosition(endText.getPosition().x, endText.getPosition().y + 200);

    //Inits Text
    retryText.setFont(f_startText);
    retryText.setString("Retry");
    retryText.setCharacterSize(80);
    retryText.setFillColor(sf::Color::White);
    retryText.setOrigin(retryText.getLocalBounds().left + retryText.getLocalBounds().width / 2,
                        retryText.getLocalBounds().top + retryText.getLocalBounds().height / 2);
    retryText.setPosition(retryButton.getPosition());

}

void Screens::initPointstext()
{
    pointsText.setFont(f_startText);
    pointsText.setCharacterSize(40);
    pointsText.setPosition(10, 0);
}

void Screens::initParallax()
{
    parallaxTexture.loadFromFile("assets/graphics/parallax.png");
    parallax.setTexture(parallaxTexture);
    parallax.setOrigin(parallax.getGlobalBounds().width / 2, parallax.getGlobalBounds().height / 2);
    parallax.setPosition(videoMode.width / 2, videoMode.height / 2);
}



//Poll Event
void Screens::pollEvent(sf::Event ev)
{
    //Enter Username
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !isHeld2 && username.size() > 0)
    {
        isHeld2 = true;
        username.erase(username.size() - 1);

    } else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) isHeld2 = false;

    if(endBool)
        if (ev.type == sf::Event::TextEntered && !sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
        {
            if (ev.text.unicode < 128)
            {
                username += (static_cast<char>(ev.text.unicode));
            }
        }

    enterUsername.setString("Enter Username: \n" + username);

    //Confirm Username
    if(endBool && !startBool)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !isHeld3)
        {
            isHeld3 = true;
            StoreInFile();

            initVariables();
            initLeaderboard();
            reloadBool = false;
            retryBool = true;
        }

        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) isHeld3 = false;
    }

}

void Screens::StoreInFile()
{
    if(username.size() == 0)
        username += "Unknown";

    std::fstream f;
    f.open(filename, std::ios::app);
    f << points << std::endl;
    f << username << std::endl;
    f.close();
}

void Screens::LoadFromFile()
{
    leaderboardPoints.clear();
    leaderboardUsernames.clear();

    std::string line;
    std::ifstream input(filename);

    int lineCount = 0;
    while(std::getline(input, line))
    {
        if(!line.size() == 0)
        {
            lineCount += 1;
            if(lineCount % 2 != 0)
            {
                leaderboardPoint.setString(line);
                leaderboardPoints.push_back(leaderboardPoint);
            }

            if(lineCount % 2 == 0)
            {
                leaderboardUsername.setString(line);
                leaderboardUsernames.push_back(leaderboardUsername);
            }
        }
    }

    bool sorted = false;
    if(leaderboardPoints.size() > 1)
        if(leaderboardPoints.size() == leaderboardUsernames.size())
        {
            while(!sorted)
            {
                for(int i = 0; i < leaderboardPoints.size() - 1; i++)
                {
                    std::string str = leaderboardPoints[i].getString();
                    std::string str2 = leaderboardPoints[i + 1].getString();
                    if(atoi(str.c_str()) < atoi(str2.c_str()))
                    {
                        tempText = leaderboardPoints[i];
                        leaderboardPoints[i] = leaderboardPoints[i + 1];
                        leaderboardPoints[i + 1] = tempText;

                        tempText = leaderboardUsernames[i];
                        leaderboardUsernames[i] = leaderboardUsernames[i + 1];
                        leaderboardUsernames[i + 1] = tempText;
                    }
                }

                for(int i = 0; i < leaderboardPoints.size() - 1; i++)
                {
                    std::string str = leaderboardPoints[i].getString();
                    std::string str2 = leaderboardPoints[i + 1].getString();
                    if(atoi(str.c_str()) < atoi(str2.c_str()))
                    {
                        sorted = false;
                        break;
                    } else {
                        sorted = true;
                    }
                }
            }
        }  
}

void Screens::startFadein()
{
    if(curfadeIn < 255.f)
    {
        curfadeIn += 0.5f;

        startScreen.setColor(sf::Color(255, 255, 255, curfadeIn));
        startButton.setColor(sf::Color(255, 255, 255, curfadeIn));
        startText.setFillColor(sf::Color(255, 255, 255, curfadeIn));
        leaderboardButton.setColor(sf::Color(255, 255, 255, curfadeIn));
    }
}

void Screens::LoadLeaderboardValues()
{
    int pos = 0;
    for(int i = 0; i < leaderboardUsernames.size(); i++)
    {
        leaderboardUsernames[i].setPosition(videoMode.width / 2 - 280, videoMode.height / 2 - 350 + pos);
        pos += 50;
    }

    pos = 0;
    for(int i = 0; i < leaderboardUsernames.size(); i++)
    {
        leaderboardPoints[i].setOrigin(leaderboardPoints[i].getGlobalBounds().width, 0);
        leaderboardPoints[i].setPosition(videoMode.width / 2 + 280, videoMode.height / 2 - 350 + pos);
        pos += 50;
    }
}

//Update
void Screens::updateScreens(bool end, int p, sf::Sprite ship)
{
    //Init when ship is dead
    endBool = end;
    points = p;

    ElapsedTime = clock.getElapsedTime().asMicroseconds() * 0.007;
    clock.restart();

    if(!endBool)
    {
        reloadBool = false;
        retryBool = false;

        curIncSpeed = 0.f;
        Hue = 0;
    }

    updateParallax(ship);

    //Leftclick Event
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(!isHeld)
        {
            isHeld = true;
            updateMousepos();

            //When mouse is on startButton
            if(startButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && startBool)
            {
                endBool = false;
                startBool = false;

                username.erase();
            }

            //When mouse is on retryButton
            if(retryButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && endBool)
            {
                endBool = false;
                retryBool = true;
            }

            if(leaderboardButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                leaderboardBool = true;
            }
        }
    } else isHeld = false;


    std::stringstream ss;
    ss << "Points: " << points;
    pointsText.setString(ss.str());
}

void Screens::updateEndtext()
{
    //Fade in endText
    if(Hue < 255 && endBool)
        if(curIncSpeed < 255)
        {
            Hue = round(curIncSpeed);
            endText.setFillColor(sf::Color(255, 255, 255, Hue));
            retryButton.setColor(sf::Color(255, 255, 255, Hue));
            retryText.setFillColor(sf::Color(255, 255, 255, Hue));
            enterUsername.setFillColor(sf::Color(255, 255, 255, Hue));

            curIncSpeed += increaseSpeed * ElapsedTime;
        }
}

void Screens::updateMousepos()
{
    this->mousePos = sf::Mouse::getPosition(*this->window);
}

void Screens::updateParallax(sf::Sprite ship)
{
    parallax.setPosition(ship.getPosition().x * 0.08, ship.getPosition().y * 0.05);
}

void Screens::closeLeaderboard()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        leaderboardBool = false;
}

//Render
void Screens::renderScreens(sf::RenderTarget& target)
{
    //Start Screen
    if(startBool || reloadBool)
    {
        startFadein();
        target.draw(startScreen);
        target.draw(startButton);
        target.draw(startText);
        target.draw(leaderboardButton);

        if(leaderboardBool)
        {
            closeLeaderboard();
            target.draw(leaderboard);
            LoadFromFile();
            LoadLeaderboardValues();
            if(leaderboardPoints.size() == leaderboardUsernames.size())
            {
                for(int i = 0; i < 14 && i < leaderboardPoints.size(); i++)
                {
                    target.draw(leaderboardUsernames[i]);
                    target.draw(leaderboardPoints[i]);
                }
            } else std::cout << "ERROR: POINTS AND USERNAMES ARENT EQUAL!" << std::endl;
        }
    }


    // While Game
    if(!startBool && !reloadBool)
    {
        target.draw(pointsText);
    }


    //End Screen
    if(endBool && !startBool)
    {
        updateEndtext();

        target.draw(endText);
        target.draw(enterUsername);
        target.draw(retryButton);
        target.draw(retryText);
    }
}

void Screens::renderParallax(sf::RenderTarget& target)
{
    target.draw(parallax);
}