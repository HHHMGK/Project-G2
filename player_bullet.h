#pragma once
#include "constants.h"
#include "texture.h"
#include "terrain.h"
#include "move_and_collision.h"

LTexture bTexture;
void loadBulletTexture(SDL_Renderer* renderer)
{
    bTexture.loadFromFile(renderer,"assets/bullet.png");
}

struct bullet
{
    int x,y;
    double velX,velY;
    bool active;
    int willHit;//0: no hit, 1: hit wall, 2: hit enemy
    void init(int x,int y,double velX,double velY);
    void move();
}bulletList[maxBulletNumber];

void bullet::init(int x,int y,double velX,double velY)
{
    this->x=x;
    this->y=y;
    this->velX=velX;
    this->velY=velY;
    willHit = 0;
    active=true;
}
void bullet::move()
{
    if(willHit)
    {
        active=false;
        return;
    }
    //check hit and move
    bool hitWall=0,hitEnemy=0;
    nextPos(x,y,velX,velY,bSize,hitWall,hitEnemy);
    if(x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT) 
    {
        active = 0;
        //std::cout<<"erhrhrhrhr \n";
        return ;
    }
    hitEnemy = checkBulletHitEntity(x,y,0);
    willHit = hitWall || hitEnemy;
}

void addBullet(int x,int y,double velX,double velY)
{
    for(int i=0;i<maxBulletNumber;i++)
        if(!bulletList[i].active)
        {
            bulletList[i].init(x,y,velX,velY);
            return;
        }
}
void moveBullets()
{
    for(int i=0;i<maxBulletNumber;i++)
        if(bulletList[i].active)
            bulletList[i].move();
}

void renderBullets(SDL_Renderer* renderer)
{
    for(int i=0;i<maxBulletNumber;i++)
        if(bulletList[i].active)
            //bTexture.render(renderer,NULL,bulletList[i].x,bulletList[i].y); 
            SDL_SetRenderDrawColor(renderer,255,255,255,255),  
            SDL_RenderFillRect(renderer,new SDL_Rect({bulletList[i].x,bulletList[i].y,bSize,bSize}));
}