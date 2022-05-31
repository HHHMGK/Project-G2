#pragma once
#include "constants.h"
#include <SDL2/SDL.h>
#include "text.h"

void drawMenuStart(SDL_Renderer* renderer,int menuChoice)
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    textTexture name(SCREEN_WIDTH/2-50,SCREEN_HEIGHT/3,100,"?"),
                intr(SCREEN_WIDTH/2-110,SCREEN_HEIGHT/3+100,20,"Press Space to start");
    name.render(renderer);
    intr.render(renderer);
}
void drawMenuOver(SDL_Renderer* renderer,bool win)
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    string str;
    if(win) str="You Won";
    else str="You Died";
    textTexture name(SCREEN_WIDTH/2-50,SCREEN_HEIGHT/3,100,str),
                intr(SCREEN_WIDTH/2-110,SCREEN_HEIGHT/3+100,20,"Press Space to start again");
    name.render(renderer);
    intr.render(renderer);
}

void drawMenuPause(SDL_Renderer* renderer,int menuChoice)
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    textTexture name(SCREEN_WIDTH/2-50,SCREEN_HEIGHT/3,100,"Paused");
    name.render(renderer);
}

void drawMenu(SDL_Renderer* renderer, SDL_Rect choiceBoxes[], string choiceContent[], int choiceNum, int choice)
{
    for(int i=0;i<choiceNum;i++)
    {
        if(i==choice)
        {
            SDL_SetRenderDrawColor(renderer,255,0,0,255);
            SDL_RenderFillRect(renderer,&choiceBoxes[i]);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderFillRect(renderer,&choiceBoxes[i]);
        }
        drawText(renderer,choiceBoxes[i].x+choiceBoxes[i].w/2-50,choiceBoxes[i].y+choiceBoxes[i].h/2,100,choiceContent[i]);
    }

}