#include <iostream>
#include "all.h"

int main(int argc,char**argv)
{
    Game::Init(); 
    SDL_Event e;
    Game::Loop();
    Game::Quit();
    return 0;
}