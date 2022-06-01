#include <iostream>
#include <windows.h>
#include "game.h"

int main(int argc, char* args[])
{
    //FreeConsole();
    cout<<"Game start\n";
    GAME game;
    game.run();
    return 0;
}