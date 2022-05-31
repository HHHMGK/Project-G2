#pragma once
#include "constants.h"
#include "terrain.h"
#include "player_bullet.h"

bool checkCollideTerrainX(int x,int y,int objectSize,int& txc)
{
    int tx,ty = y/tSize;
    int maxPixel = std::min(x+objectSize,SCREEN_WIDTH);
    while(x <= maxPixel)
    {
        tx = x/tSize;
        if(mapT[ty][tx]!=0) 
        {
            txc = tx;
            //std::cout<<"Coll X at: "<<ty<<' '<<txc<<"    or "<<y<<' '<<x<<'\n';
            return 1;
        }
        x+=tSize;
    }
    return 0;
}
bool checkCollideTerrainY(int x,int y,int objectSize,int& tyc)
{
    int tx = x/tSize,ty;
    int maxPixel = std::min(y+objectSize,SCREEN_HEIGHT);
    while(y <= maxPixel)
    {
        ty = y/tSize;
        if(mapT[ty][tx]!=0) 
        {
            tyc = ty;
            //std::cout<<"Coll Y at "<<tyc<<' '<<tx<<"    or "<<y<<' '<<x<<'\n';
            return 1;
        }
        y+=tSize;
    }
    return 0;
}
void nextPos(int &x,int &y,double velX,double velY,int objectSize,bool &hitWall,bool &hitEnemy)
{
    int tx,ty;
    if(velX < 0) //go left
    {
        if(checkCollideTerrainX(x + velX,y,objectSize,tx)) 
            x = (tx+1)*tSize,
            hitWall = 1;
        else x += velX;
    }
    else if(velX > 0) //go right
    {
        if(checkCollideTerrainX(x + velX + objectSize,y,objectSize,tx)) 
            x = tx*tSize - objectSize,
            hitWall = 1;
        else x += velX;
    }
    if(velY < 0) //go up
    {
        if(checkCollideTerrainY(x,y+velY,objectSize,ty)) 
            y = (ty+1)*tSize,
            hitWall = 1;
        else y += velY;
    }
    else if(velY > 0) //go down
    {
        if(checkCollideTerrainY(x,y + velY + objectSize,objectSize,ty)) 
            y = ty*tSize - objectSize,
            hitWall = 1;
        else y += velY;
    }
    x=std::min(std::max(x,0),SCREEN_WIDTH-pSize);
    y=std::min(std::max(y,0),SCREEN_HEIGHT-pSize);
}

struct entity
{
    bool wasHit = 0;
    SDL_Rect hitbox;
}eList[2];
/*bool checkCollideRect(SDL_Rect a,SDL_Rect b)
{
    std::cout<<a.x<<' '<<a.y<<' '<<a.w<<' '<<a.h<<'\n';
    std::cout<<b.x<<' '<<b.y<<' '<<b.w<<' '<<b.h<<'\n';
    if(a.x + a.w < b.x || a.x > b.x + b.w) return 0;
    if(a.y + a.h < b.y || a.y > b.y + b.h) return 0;
    return 1;
}*/
bool checkBulletHitEntity(int x,int y,int exclusion)
{
    SDL_Rect bRect={x,y,bSize,bSize};
    for(int i=0;i<2;i++)
        if(i != exclusion && SDL_HasIntersection(&bRect,&eList[i].hitbox))
        {
            eList[i].wasHit = 1;
            return 1;
        }
    return 0;
}
bool checkHitEntity(int id,int hid)
{
    return SDL_HasIntersection(&eList[id].hitbox,&eList[hid].hitbox);
}