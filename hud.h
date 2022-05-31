#pragma once
#include "constants.h"
#include <SDL2/SDL.h>
#include "gameTexture.h"
#include "text.h"


void drawHud(SDL_Renderer* renderer, int playerHP, int bossHP);
void drawPlayerHealth(SDL_Renderer* renderer,int HP);
void drawBossHealth(SDL_Renderer* renderer,int HP);

void drawHud(SDL_Renderer* renderer, int playerHP, int bossHP)
{
    drawPlayerHealth(renderer,playerHP);
    if(bossHP > 0) drawBossHealth(renderer,bossHP);
}

void drawPlayerHealth(SDL_Renderer* renderer, int HP)
{
    int xoff = 40,yoff = 40;
    for(int i=0;i<HP;i++)
    {
        pHealth.render(renderer,NULL,xoff,yoff,48,24);
        xoff+=78;
    }
}

void drawBossHealth(SDL_Renderer* renderer,int HP)
{
    drawText(renderer,1100,80,30,to_string(HP));
    //1160 160 1160 640
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderDrawRect(renderer,new SDL_Rect({1160,160,40,480}));
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    int yy=min(639,161+int((1-1.0*HP/bossMaxHP)*(639-161)));
    SDL_RenderFillRect(renderer,new SDL_Rect({1161,yy,38,639-yy}));
}