#pragma once
#include "constants.h"
#include <SDL2/SDL.h> 
#include <cmath> 
#include "texture.h"
#include "terrain.h"
#include "player_bullet.h"
#include "move_and_collision.h"

struct player
{
    int x,y,hp;
    int velX,velY;
    int dir; //0 1 2 3 : right left up down
    bool shoot;
    const int eid = 0;// entity id
    const int width = pSize,height = pSize;
    int hitTime;
    bool invi =0 ;

    player(int x, int y, int hp);
    void init(int x, int y, int hp);
    //~player();
    void handleEvent(SDL_Event &e);
    void move();
    void render(SDL_Renderer* renderer);
    void syncData();
    bool struck();
};

player::player(int x = 0, int y = 0, int hp=5)
{
    this->x=x;
    this->y=y;
    this->hp=hp;
    velX=velY=0;
    shoot=0;
}
void player::init(int x = 0, int y = 0, int hp=5)
{
    this->x=x;
    this->y=y;
    this->hp=hp;
}
void player::handleEvent(SDL_Event &e) 
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_d:
                velX+=pVel;
                dir=0;
                break;
            case SDLK_a: 
                velX-=pVel;
                dir=1;
                break;
            case SDLK_w: 
                velY-=pVel;
                dir=2;
                break;
            case SDLK_s: 
                velY+=pVel;
                dir=3;
                break;
            case SDLK_o: 
                x=playerSpawnX;
                y=playerSpawnY;
                break;
        }
    }    
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_d:
                velX-=pVel;
                break;
            case SDLK_a: 
                velX+=pVel;
                break;
            case SDLK_w: 
                velY+=pVel;
                break;
            case SDLK_s: 
                velY-=pVel;
                break;
        }
    }
    if(e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
        shoot = 1;
    if(e.type == SDL_MOUSEBUTTONUP && e.key.repeat == 0)
        shoot = 0;
    
}

void player::move()
{
    bool hit = 0;//dont care
    bool hitEnemy = 0;
    nextPos(x,y,velX,velY,pSize,hit,hitEnemy);
    if(hitEnemy)
    {
        hp--;
    }
    if(shoot)
    {
        int px,py;
        double vx,vy;
        SDL_GetMouseState(&px,&py);
        double tan=7777;
        if(px != x) 
        {
            tan = (double)(py-y)*1.0/(px-x);
            vx = sqrt(bVel*bVel / (1 + tan*tan));
            vy = sqrt(bVel*bVel - vx*vx);
        }
        else
        {
            vx = 0;
            vy = bVel;
        }
        if(px < x) vx=-vx;
        if(py < y) vy=-vy; 
        addBullet(x,y,vx,vy);
        //std::cout<<tan<<'\n';
        //std::cout<<"bam bam bam "<<vx<<" "<<vy<<" "<<x<<" "<<y<<" "<<px<<" "<<py<<std::endl;
    }
}
void player::syncData()
{
    if(invi && SDL_GetTicks() - hitTime >= 2000) invi=0;
    if((eList[eid].wasHit || struck()) && invi ==0)
    {
        hp--;
        invi = 1;
        hitTime = SDL_GetTicks();
        eList[eid].wasHit=0;
    }
    eList[eid].hitbox.x=x;
    eList[eid].hitbox.y=y;
    eList[eid].hitbox.w=width;
    eList[eid].hitbox.h=height;

}

void player::render(SDL_Renderer* renderer)
{   
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer,new SDL_Rect({x,y,pSize,pSize}));
}

bool player::struck()
{
    return checkHitEntity(0,1);
}