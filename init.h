#ifndef __INIT_H__
#define __INIT_H__

#ifdef __MAIN__
    SDL_Renderer *ren=NULL;
    SDL_Window* win=NULL;
    float current=0.0f,now=0.0f;
    b2Vec2 gravity(0.0f,9.8f);
    b2World world(gravity);
    SDL_Texture**textures=NULL;
    tmx_map *map=NULL;
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    SDL_Rect persoRect={160,150,45,45};
    Game::Player *p=NULL;
    Map::Map *m=NULL;
    int quit=0;
    int KEY[SDL_NUM_SCANCODES];
#else
    extern SDL_Renderer *ren;
    extern SDL_Window* win;
    extern float current;
    extern float now;
    extern b2Vec2 gravity;
    extern b2World world;
    extern SDL_Texture**textures;
    extern tmx_map *map;
    extern float32 timeStep;
    extern int32 velocityIterations;
    extern int32 positionIterations;
    extern SDL_Rect persoRect;
    extern Game::Player *p;
    extern Map::Map *m;
    extern int quit;
    extern int KEY[SDL_NUM_SCANCODES];
#endif

void* load(const char*);
namespace Game{
    void Init();
    void Quit();
    int Update(SDL_Event);
    void Render();
    void Loop();
}
#endif