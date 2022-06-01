#pragma once
#include "constants.h"
#include <SDL2/SDL.h>
#include <vector>
#include "text.h"

vector<SDL_Rect> cBox[3];
vector<string> cContent[3];
string fontHeader = "assets/OpenSans-ExtraBold.TTF";
string fontContent = "assets/OpenSans-Regular.TTF";
void initMenuChoice()
{
    //start menu
    cBox[0].push_back({550,335,180,50});
    cBox[0].push_back({550,335+50+85,180,50});
    cContent[0].push_back("Start");
    cContent[0].push_back("Quit");
    //pause menu
    cBox[1].push_back({550,240,180,50});
    cBox[1].push_back({550,240+50+65,180,50});
    cBox[1].push_back({550,240+2*50+2*65,180,50});
    cBox[1].push_back({550,240+3*50+3*65,180,50});
    cContent[1].push_back("Resume");
    cContent[1].push_back("Music");
    cContent[1].push_back("Sound");
    cContent[1].push_back("Quit");
    //over menu
    cBox[2].push_back({550,300,180,50});
    cBox[2].push_back({550,300+50+85,180,50});
    cBox[2].push_back({550,300+2*50+2*85,180,50});
    cContent[2].push_back("Again");
    cContent[2].push_back("Menu");
    cContent[2].push_back("Quit");

}
void drawMenu(SDL_Renderer* renderer, vector<SDL_Rect> choiceBoxes, vector<string> choiceContent, int choice)
{
    drawText(renderer,0,0,30,to_string(choice));
    int choiceNum = choiceBoxes.size();
    for(int i=0;i<choiceNum;i++)
    {
        if(i==choice-1)
        {
            drawTextCenter(renderer,choiceBoxes[i].x,choiceBoxes[i].y,40,choiceContent[i],choiceBoxes[i].w,choiceBoxes[i].h,{255,0,0,255},fontContent);
            // SDL_SetRenderDrawColor(renderer,255,0,0,180);
            // SDL_RenderDrawRect(renderer,&choiceBoxes[i]);
        }
        else
            drawTextCenter(renderer,choiceBoxes[i].x,choiceBoxes[i].y,40,choiceContent[i],choiceBoxes[i].w,choiceBoxes[i].h,{255,255,255,255},fontContent);
    }
}

void drawMenuStart(SDL_Renderer* renderer,int menuChoice)
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    drawText(renderer,420,150,67,"Cosmic Nose");
    drawMenu(renderer,cBox[0],cContent[0],menuChoice);
}
void drawMenuPause(SDL_Renderer* renderer,int menuChoice)
{
    SDL_Texture* faded;
    faded = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);
    SDL_SetTextureBlendMode(faded,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(faded,200);
    SDL_SetRenderTarget(renderer,faded);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    drawText(renderer,515,95,67,"Paused");
    drawMenu(renderer,cBox[1],cContent[1],menuChoice);
    SDL_SetRenderTarget(renderer,NULL);
    SDL_RenderCopy(renderer,faded,NULL,NULL);
    SDL_DestroyTexture(faded);
}
void drawMenuOver(SDL_Renderer* renderer,bool win,int menuChoice)
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    if(win) drawText(renderer,490,150,67,"You Win",{82, 113, 255, 255});
    else drawText(renderer,490,150,67,"You Died",{255, 0, 0, 255});
    drawMenu(renderer,cBox[2],cContent[2],menuChoice);
}
