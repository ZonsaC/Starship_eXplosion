#include "audio.h"
#include "game.h"

Audio::Audio() 
{
    initMenu();
    initGame();
    initShotShound();
}

Audio::~Audio() 
{
    
}


//Init
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

void Audio::initShotShound()
{
    buffer.loadFromFile("assets/audio/shot.wav");
    shotSound.setBuffer(buffer);
    shotSound.setVolume(10.f);
}


//Update
void Audio::updateAudio(bool sB, bool eB, bool rB, bool rlB, bool bS)
{
    startBool = sB;
    endBool = eB;
    retryBool = rB;
    reloadBool = rlB;
    bulletSpawned = bS;

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
        playGame = true;
        gameMusik.play();
    }
        
    if(bulletSpawned)
    {
        std::cout << "Shoot" << "\n";
        shotSound.play();
    }
}