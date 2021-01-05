#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <Box2D/Box2D.h>
#include <tmx/tmx.h>
#include "game.h"
#include "utils.h"

using namespace Game;
using namespace Physics;

Player::Player(b2World& world,SDL_Rect rect,SDL_Texture** textures)
{
    this->textures=textures;
    this->position.x=rect.x;
    this->position.y=rect.y;
    this->position.w=rect.w;
    this->position.h=rect.h;
    this->body=Physics::CreateDynamicBody(world,
    PixelToMeter(this->position.x+this->position.w/2),
    PixelToMeter(this->position.y+this->position.h/2),
    PixelToMeter(this->position.w/2),
    PixelToMeter(this->position.h/2));
    body->SetFixedRotation(true);
    direction=1;
    delay=10;
    r=0;
    vX=0.0f;
    jumpSpeed=22.0f;
}

void Player::Render(SDL_Renderer* renderer)
{
    SDL_Rect source={anim*32,0,32,32};
    if(abs(currentVelocity.x)!=0.02f && direction == -1)r=1;
    if(abs(currentVelocity.x)!=0.02f && direction == 1)r=0;
    if(abs(currentVelocity.x)>0.02f && direction == 1)r=2;
    if(abs(currentVelocity.x)>0.02f && direction == -1)r=3;
    SDL_RenderCopy(renderer,textures[r],&source,&position);
}

void Player::Update()
{
    body->SetLinearVelocity(currentVelocity);
    position.x=MeterToPixel(body->GetPosition().x)-position.w/2;
    position.y=MeterToPixel(body->GetPosition().y)-position.h/2; 
    if(body->GetPosition().x<PixelToMeter(1))body->SetTransform(b2Vec2(PixelToMeter(798),body->GetPosition().y),0);
    if(body->GetPosition().x>PixelToMeter(799))body->SetTransform(b2Vec2(PixelToMeter(2),body->GetPosition().y),0);
    if(delay>4)
    {
        anim++;
        if(anim>5 && (r==2 || r==3))anim=0;
        if(anim>3 && (r==0 || r==1))anim=0;  
        delay=0;
    }
    delay++;
}

void Player::Init()
{
    
}

void Player::EventHandler(SDL_Event e)
{
    currentVelocity=body->GetLinearVelocity();

    if(IsKeyPressed())
    {
        if(GetInputKey(SDLK_SPACE))body->ApplyForceToCenter(b2Vec2(0.0f,-jumpSpeed),true);
        if(Game::GetInputKey(SDLK_LEFT))
        {
            direction=-1;
            vX=-0.3;
        }
        if(Game::GetInputKey(SDLK_RIGHT))
        {
            direction=1;
            vX=0.3;
        }
        currentVelocity.x+=vX;
        if(abs(currentVelocity.x)>3)currentVelocity.x=3*direction;
    }else
    {
        vX=0;
        currentVelocity.x*=0.7;
    }
}