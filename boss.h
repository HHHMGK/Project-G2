#pragma once 
#include "constants.h"
#include "gameTexture.h"
#include "move_and_collision.h"
using namespace std;


struct boss
{
    int x,y;
    int hp;
    int attackType;//0: none, 1: bullet, 2: laser
    int phase;//0: norm, 1: 50% hp, 2: 25% hp
    int phaseUpdated = 0;
    int velX = 5,velY = 5;
    const int eid = 1;
    const int width = 302,height = 240;

    void syncData();
    boss(int x,int y,int hp);
    void init(int x,int y,int hp);
    void move();
    void shoot();
    void render(SDL_Renderer* renderer);
};
boss::boss(int x = 640,int y = 200,int hp = bossMaxHP)
{
    this->x=x;
    this->y=y;
    this->hp=hp;
}
void boss::init(int x,int y,int hp)
{
    this->x=x;
    this->y=y;
    this->hp=hp;
}

void boss::move()
{
    phase = 0;
    if(hp < bossMaxHP/2) phase = 1;
    if(hp < bossMaxHP/4) phase = 2;
    
    if(phase==1 && phaseUpdated==0) velX*=1.5, velY*=1.5, phaseUpdated = 1;
    if(phase==2 && phaseUpdated==1) velX*=1.7, velY*=1.7, phaseUpdated = 2;
    x+=velX;
    y+=velY;
    if(x < 40 || x + width > SCREEN_WIDTH-40) velX=-velX;
    if(y < 40 || y + height > SCREEN_HEIGHT-40) velY=-velY;
    x=min(SCREEN_WIDTH-40,max(40,x));
    y=min(SCREEN_HEIGHT-40,max(40,y));
    //std::cout<<x<<' '<<y<<' '<<velX<<' '<<velY<<'\n';
}
void boss::syncData()
{
    if(eList[eid].wasHit)
    {
        hp-=10;
        eList[eid].wasHit=0;
    }
    eList[eid].hitbox.x=x;
    eList[eid].hitbox.y=y;
    eList[eid].hitbox.w=width;
    eList[eid].hitbox.h=height;

}

SDL_Rect bossRect[3]={{0,0,302,240},{302,0,302,240},{604,0,302,240}};
void boss::render(SDL_Renderer* renderer)
{
    if(hp <= 0) return;
    bossTexture.render(renderer,&bossRect[SDL_GetTicks()/1000%3],x,y,302,240);
}