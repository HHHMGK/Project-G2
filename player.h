#pragma once
#include "constants.h"
#include <SDL2/SDL.h> 
#include "texture.h"
#include "terrain.h"
#include "bullet.h"
#include "move_and_collision.h"

struct player
{
    int x,y,hp;
    int velX,velY;
    bool shoot;
    int hitTime;
    bool invisible =0 ;
    const int eid = 0;// entity id
    const int width = pSize,height = pSize;

    player(int x, int y, int hp);
    void spawn(int x, int y, int hp);
    //~player();
    void handleEvent(SDL_Event &e);
    void move();
    void render(SDL_Renderer* renderer);
    void syncData();
    bool struck();
};

player::player(int x = 0, int y = 0, int hp=maxHP)
{
    this->x=x;
    this->y=y;
    this->hp=hp;
    velX=velY=0;
    shoot=0;
    invisible = 0;
    hitTime = 0;
}
void player::spawn(int x = playerSpawnX, int y = playerSpawnY, int hp=maxHP)
{
    this->x=x;
    this->y=y;
    this->hp=hp;
    velX=velY=0;
    shoot=0;
    invisible = 0;
    hitTime = 0;
}
void player::handleEvent(SDL_Event &e) 
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_RIGHT:
            case SDLK_d:
                velX+=pVel;
                break;
            case SDLK_LEFT:
            case SDLK_a: 
                velX-=pVel;
                break;
            // case SDLK_UP:
            // case SDLK_w: 
            //     velY-=pVel;
            //     break;
            // case SDLK_DOWN:
            // case SDLK_s: 
            //     velY+=pVel;
            //     break;
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
        calculateBulletVelocity(x,y,px,py,vx,vy);
        addBullet(x,y,vx,vy);
        //std::cout<<tan<<'\n';
        //std::cout<<"bam bam bam "<<vx<<" "<<vy<<" "<<x<<" "<<y<<" "<<px<<" "<<py<<std::endl;
    }
}
void player::syncData()
{
    if(invisible && SDL_GetTicks() - hitTime >= 2000) invisible=0;
    if((eList[eid].wasHit || struck()) && invisible ==0)
    {
        hp--;
        invisible = 1;
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