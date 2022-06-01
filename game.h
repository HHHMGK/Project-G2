#pragma once
#include "constants.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "terrain.h"
#include "SDLcore.h"
#include "gameTexture.h"
#include "player.h"
#include "boss.h"
#include "menu.h"
#include "hud.h"
#include "text.h"
using namespace std;


class GAME
{
public:
    GAME();
    ~GAME();
    void introMenu();
    void startGame();
    void pauseGame();
    void resumeGame();
    void endGame();
    void fixMenuChoice(int l,int r);

    void handleEvent(SDL_Event &e);
    void handleEventMenu(SDL_Event &e);
    void handleEventInGame(SDL_Event &e);
    void update();
    void render();

    void run();

    void debug();
private:
    //game states
    bool quit;
    bool isStartMenu;
    bool inGame;
    bool paused;
    bool isGameOver;

    //for menu
    int menuChoice;
    int choice;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event e;
    player P;
    boss B;
};
GAME::GAME()
{
    if (!initSDL(window, renderer))
    {
        std::cout<<"SDL Init Error"<<std::endl;
        return ;
    }
    loadAllTexture(renderer);
    loadMap();
    initMenuChoice();

    quit = false;
    isStartMenu = false;
    inGame = false;
    paused = false;
    isGameOver = false;
    menuChoice = 1;
    choice = 0;
}
GAME::~GAME()
{
    quitSDL(window, renderer);
}
void GAME::introMenu()
{
    isStartMenu = true;
    inGame = false;
    isGameOver = false;
    menuChoice = 1;
    choice = 0;
}
void GAME::startGame()
{
    isStartMenu = false;
    inGame = true;
    isGameOver = false;
    P.init(playerSpawnX,playerSpawnY);
    menuChoice = 1;
    choice = 0;
}
void GAME::pauseGame()
{
    paused = true;
    menuChoice = 1;
    choice = 0;
}
void GAME::resumeGame()
{
    paused = false;
}
void GAME::endGame()
{
    isStartMenu = false;
    inGame = false;
    isGameOver = true;
    menuChoice = 1;
    choice = 0;
}
void GAME::fixMenuChoice(int l,int r)
{
    if(menuChoice < l) menuChoice = r;
    if(menuChoice > r) menuChoice = l;
    if(menuChoice==7) quit = true;

}
void GAME::handleEventMenu(SDL_Event &e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
                menuChoice--;
                break;
            case SDLK_DOWN:
                menuChoice++;
                break;
            case SDLK_ESCAPE:
                menuChoice = 7;
                break;
            case SDLK_RETURN:
                choice = menuChoice;
                break;
        }
    }
}
void GAME::handleEventInGame(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_ESCAPE && inGame)
        {
            if (paused) resumeGame();
            else pauseGame();
        }
    }
    if(!paused) P.handleEvent(e);
    else handleEventMenu(e);
}


void GAME::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_QUIT)
    {
        quit = true;
        return ;
    }
    if(isStartMenu || isGameOver)
        handleEventMenu(e);
    if(inGame)
    {
        if(paused) handleEventMenu(e);
        else handleEventInGame(e);
    }
}
void GAME::update()
{
    if(paused) return;
    moveBullets();
    P.move();
    P.syncData();
    B.move();
    B.syncData();
}
void GAME::run()
{
    //introMenu();
    endGame();
    render();
    while(!quit)
    {
        //debug();
        while(!quit && isStartMenu)
        {
            while(SDL_PollEvent(&e))
                handleEvent(e);
            fixMenuChoice(1,2);
            if(choice==1) startGame();
            if(choice==2) quit = true;
            render();
            //cout<<"inside:\n";debug();
        }
        if(quit) break ;
        while(!quit && inGame)
        {
            while(SDL_PollEvent(&e))
                handleEvent(e);
            update();
            render();
            if(P.hp == 0 || B.hp == 0) endGame();
        }
        if(quit) break ;
        while(!quit && isGameOver)
        {
            while(SDL_PollEvent(&e))
                handleEvent(e);
            fixMenuChoice(1,3);
            if(choice==1) startGame();  //play a gain
            if(choice==2) introMenu(); //go back to menu  
            if(choice==3) quit = true;  //quit
            render();
        }
    }

}

void GAME::render()
{
    int startTime = SDL_GetTicks(); 

    if(isStartMenu)
        drawMenuStart(renderer,menuChoice);
    if(inGame)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderTerrain(renderer);
        renderBullets(renderer);
        P.render(renderer);
        B.render(renderer);
        if(paused) 
            drawMenuPause(renderer,menuChoice);
        else
            drawHud(renderer,P.hp,B.hp);    
    }
    if(isGameOver)
    {
        if(P.hp==0) drawMenuOver(renderer,0,menuChoice);
        else drawMenuOver(renderer,1,menuChoice);
    }
    SDL_RenderPresent(renderer);

    //FPS
    int frameTime = std::max(int(SDL_GetTicks() - startTime),1);
    //cout<<1000/frameTime<<'\n';
    if(frameTime < 1000/FPS)
        SDL_Delay(1000/FPS - frameTime);
}

void GAME::debug()
{
    //print states
    cout<<"isStartMenu: "<<isStartMenu<<endl;
    cout<<"inGame: "<<inGame<<endl;
    cout<<"isGameOver: "<<isGameOver<<endl;
    cout<<"quit: "<<quit<<endl;
    cout<<SDL_GetError()<<'\n';
}