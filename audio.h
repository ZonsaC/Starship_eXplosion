#ifndef __AUDIO_H
#define __AUDIO_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <iostream>

class Audio
{
public:
    Audio();
    ~Audio();

    void updateAudio(bool, bool, bool, bool);

private:

    bool startBool;
    bool endBool;
    bool retryBool;
    bool reloadBool;

    bool playMenu;
    bool playGame;

    sf::Music menuMusik;
    sf::Music gameMusik;


    void initMenu();
    void initGame();
};
#endif