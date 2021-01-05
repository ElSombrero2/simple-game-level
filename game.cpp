#include <iostream>
#include "all.h"

using namespace std;

int Game::Update(SDL_Event e)
{
    world.Step(timeStep, velocityIterations, positionIterations);
    if(e.type==SDL_QUIT)return 1;
    p->EventHandler(e);
    now=SDL_GetTicks();
    return 0;
}

void Game::Render()
{
    if(now-current>=SECOND/FRAME)
    {
        p->Update();
        m->Render(ren);
        current=now;
        p->Render(ren);
    }else SDL_Delay(SECOND/FRAME-(now-current));
    SDL_RenderPresent(ren);
}
