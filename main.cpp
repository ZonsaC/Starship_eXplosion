#include "game.h"
#include "enemy.h"
#include "starship.h"

int main()
{
    //Init Game engine
    Game game;

    //Game loop
    while(game.getWindowIsOpen())
    {
        //Update
        game.update();

        //Render
        game.render();
    }
    return 0;
}