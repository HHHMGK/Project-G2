#pragma once 
#include "constants.h"
#include "gameTexture.h"
#include "move_and_collision.h"
#include "bullet.h"
using namespace std;


struct boss
{
    int x,y;
    int hp;
    int phase;//0: norm, 1: 50% hp, 2: 25% hp
    int phaseUpdated = 0;
    int velX = 5,velY = 5;
    int prevShootTime = 0;
    const int eid = 1;
    const int width = 302,height = 240;

    void syncData();
    boss(int x,int y,int hp);
    void spawn(int x,int y,int hp);
    void move();
    void shoot();
    void render(SDL_Renderer* renderer);
};
boss::boss(int x = 640,int y = 200,int hp = bossMaxHP)
{
    this->x=x;
    this->y=y;
    this->hp=hp;
    velX = velY = 5;
    phase = phaseUpdated = 0;
}
void boss::spawn(int x = bossSpawnX, int y = bossSpawnY, int hp = bossMaxHP)
{
    this->x=x;
    this->y=y;
    this->hp=hp;
    velX = velY = 5;
    phase = phaseUpdated = 0;
}
pair<int,int> firePoint[12] = {{15,15}, {150,0}, {290,15}, {30,240}, {270,240},
                              {150,240}, {95,225}, {205,225}, {115,230}, {185,230}, {290,160}, {15,160}};
void boss::shoot()
{
    //center of boss
    int cx = x+width/2, cy = y+height/2;

    for(int i=0;i<12;i++)
    {
        int px = x+firePoint[i].first, py = y+firePoint[i].second;
        double vx,vy;
        calculateBulletVelocity(cx,cy,px,py,vx,vy,5);
        addBullet(px,py,vx,vy,0);
    }
}
void boss::move()
{
    phase = 0;
    if(hp < bossMaxHP/2) phase = 1;
    if(hp < bossMaxHP/4) phase = 2;
    
    double timeDiff = 2.5 - phase;
    if(SDL_GetTicks() - prevShootTime >= timeDiff*1000 && y <= SCREEN_HEIGHT/3)
    {
        prevShootTime = SDL_GetTicks();
        shoot();
    }
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
        hp-=2;
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