#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Box2D/Box2D.h>
#include <tmx/tmx.h>
#include "game.h"
#define __MAIN__
#include "init.h"

void* load(const char* path)
{
    SDL_Surface* tmp=IMG_Load(path);
    SDL_Texture* text=SDL_CreateTextureFromSurface(ren,tmp);
    SDL_QueryTexture(text,NULL,NULL,NULL,NULL);
    SDL_FreeSurface(tmp);
    return text;
}

void Game::Init()
{
    //SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    win=SDL_CreateWindow("Tiled",SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_SHOWN);
    ren=SDL_CreateRenderer(win,0,SDL_RENDERER_ACCELERATED); 

    SDL_SetHint(SDL_HINT_RENDER_VSYNC,SDL_HINT_VIDEO_DOUBLE_BUFFER);

    memset(KEY,0,sizeof(KEY));
    
    SDL_Surface* idle=IMG_Load("bin/img/player/player-idle.png");
    SDL_Surface* idle_inv=IMG_Load("bin/img/player/player-idle_inv.png");

    SDL_Surface* run=IMG_Load("bin/img/player/payer-run.png");
    SDL_Surface* run_inv=IMG_Load("bin/img/player/payer-run_inv.png");

    textures=new SDL_Texture*[4]{
        SDL_CreateTextureFromSurface(ren,idle),
        SDL_CreateTextureFromSurface(ren,idle_inv),
        SDL_CreateTextureFromSurface(ren,run),
        SDL_CreateTextureFromSurface(ren,run_inv),
    };

    for(int i=0;i<4;i++)
        SDL_QueryTexture(textures[i],NULL,NULL,NULL,NULL);

    SDL_FreeSurface(idle_inv);
    SDL_FreeSurface(idle);
    SDL_FreeSurface(run_inv);
    SDL_FreeSurface(run);

    p=new Game::Player(world,persoRect,textures);

    //Map
    tmx_img_load_func=load;
    map=tmx_load("bin/example.tmx");
    m=new Map::Map(map);

    tmx_layer* tmp=map->ly_head;
    while(tmp!=NULL){
        if(tmp->type==L_OBJGR)
            m->LoadCollision(tmp,world);
        tmp=tmp->next;
    }
}

void Game::Quit()
{
    
    tmx_map_free(map);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void Game::Loop()
{
    while(!quit)
    {
        SDL_Event e;
        SDL_PollEvent(&e);
        if(e.type==SDL_KEYDOWN)KEY[SDL_GetScancodeFromKey(e.key.keysym.sym)]=1;
        if(e.type==SDL_KEYUP)KEY[SDL_GetScancodeFromKey(e.key.keysym.sym)]=0;
        quit=Update(e);
        Render();
    }
}

int Game::GetInputKey(int k){return KEY[SDL_GetScancodeFromKey(k)];}

int Game::IsKeyPressed()
{
    for(int i=0;i<512;i++)
        if(KEY[i])return 1;
    return 0;
}