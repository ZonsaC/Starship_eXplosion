#include "audio.h"
#include "game.h"

Audio::Audio() 
{
    initMenu();
    initGame();
}

Audio::~Audio() 
{
    
}

void Audio::initMenu()
{
    menuMusik.openFromFile("assets/audio/main.wav");
    menuMusik.setVolume(10.f);
    menuMusik.setLoop(true);
}

void Audio::initGame()
{
    gameMusik.openFromFile("assets/audio/game.wav");
    gameMusik.setVolume(10.f);
    gameMusik.setLoop(true);
}

void Audio::updateAudio(bool sB, bool eB, bool rB, bool rlB)
{
    startBool = sB;
    endBool = eB;
    retryBool = rB;
    reloadBool = rlB;

    if(startBool && !playMenu)
    {
        playMenu = true;
        playGame = false;
        menuMusik.play();
        gameMusik.stop();
    } 
    if(!startBool)
    {
        playMenu = false;
        menuMusik.stop();
    }


    if(!startBool && !playGame)
    {
        std::cout << "LMAOOOOOOOOOOOOOOOOOOOOOOOOOO";
        playGame = true;
        gameMusik.play();
    }
        
        
}