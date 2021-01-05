#include <iostream>
#include <SDL2/SDL.h>
#include <tmx/tmx.h>
#include <Box2D/Box2D.h>
#include "utils.h"
#include "game.h"

float Physics::PixelToMeter(int px){return px*0.02f;}

int Physics::MeterToPixel(float m){return (int)(m*50.0f);}

void Map::ShowImageLayer(tmx_map* map,tmx_layer* layer,SDL_Renderer* ren,int i,int j)
{
    uint32_t *gids=layer->content.gids;
    uint32_t g=gids[i*map->width+j] & TMX_FLIP_BITS_REMOVAL;
    if(layer->type!=L_OBJGR && layer->type!=L_IMAGE &&map->tiles[g]!=NULL)
    {
        tmx_image *im=map->tiles[g]->tileset->image;
        tmx_tile* tile=map->tiles[g];
        int w=(int)tile->tileset->tile_width;
        int h=(int)tile->tileset->tile_height;
        if(im!=NULL)
        {
            SDL_Rect source={(int)tile->ul_x,(int)tile->ul_y,w,h};
            SDL_Rect dest={j*w,i*h,w,h};
            SDL_Texture* text=(SDL_Texture*)im->resource_image;
            SDL_RenderCopy(ren,text,&source,&dest);
        }
    }
}

void Physics::SetPhysicBody(b2World& world,float cx,float cy,float w,float h)
{
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(cx,cy);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(w,h);
    groundBody->CreateFixture(&groundBox, 0.0f);
}

b2Body* Physics::CreateDynamicBody(b2World& world,float cx,float cy,float w,float h)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(cx,cy);
    b2Body* body = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(w,h);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    body->CreateFixture(&fixtureDef);
    return body;
}

Map::Map::Map(tmx_map* map){this->map=map;}

void Map::Map::Init(){}

void Map::Map::Update(){}

void Map::Map::Render(SDL_Renderer* ren)
{
    for(int i=0;i<map->height;i++)
    {
        for(int j=0;j<map->width;j++)
        {
            tmx_layer* l=map->ly_head;
            while(l!=NULL)
            {
                ShowImageLayer(map,l,ren,i,j);
                l=l->next;
            }
            
        }
    }
}

void Map::Map::LoadCollision(tmx_layer* layer,b2World& world)
{
    using namespace Physics;
    if(layer->type==L_OBJGR)
    {
        tmx_object* obj=layer->content.objgr->head;
        while(obj!=NULL)
        {
            int x=obj->x;
            int y=obj->y;
            int w=obj->width;
            int h=obj->height;
            Physics::SetPhysicBody(world,PixelToMeter(x+w/2),PixelToMeter(y+h/2),
            PixelToMeter(w/2),PixelToMeter(h/2));
            obj=obj->next;
        }
    }
}