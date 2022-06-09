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
#include "sound.h"
using namespace std;


class GAME
{
public:
    GAME();
    ~GAME();
    void initGameEntity();
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
    loadSounds();
    loadMap();
    initMenuChoice();
    quit = false;
}
GAME::~GAME()
{
    quitSDL(window, renderer);
}
void GAME::initGameEntity()
{
    P.spawn();
    B.spawn();
    for(int i=0;i<maxBulletNumber;i++) 
        bulletList[i].active = 0;
}
void GAME::introMenu()
{
    isStartMenu = true;
    inGame = false;
    isGameOver = false;
    paused = false;
    quit = false;
    menuChoice = 1;
    choice = 0;
}
void GAME::startGame()
{
    isStartMenu = false;
    inGame = true;
    isGameOver = false;
    paused = false;
    quit = false;
    menuChoice = 1;
    choice = 0;
    initGameEntity();
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
    paused = false;
    quit = false;
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
            case SDLK_w:
            case SDLK_UP:
                menuChoice--;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                menuChoice++;
                break;
            case SDLK_RETURN:
                choice = menuChoice;
                break;
        }
    }
}
void GAME::handleEventInGame(SDL_Event &e)
{
    P.handleEvent(e);
}

void GAME::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_QUIT)
    {
        quit = true;
        return ;
    }
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        if(e.key.keysym.sym == SDLK_KP_PLUS)
            volume += 10;
        else if(e.key.keysym.sym == SDLK_KP_MINUS)
            volume-=10;
        changeVolume();
    }
    if(isStartMenu || isGameOver)
        handleEventMenu(e);
    if(inGame)
    {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE && e.key.repeat ==0)
        {
            if (paused) resumeGame();
            else pauseGame();
            return ;
        }
        if(paused) handleEventMenu(e);
        else handleEventInGame(e);
    }
}
void GAME::update()
{
    moveBullets();
    P.move();
    P.syncData();
    B.move();
    B.syncData();
}
void GAME::run()
{
    introMenu();
    render();
    while(!quit)
    {
        restartBGMusic();
        //debug();
        while(!quit && isStartMenu)
        {
            while(SDL_PollEvent(&e))
            {
                handleEvent(e);
                fixMenuChoice(1,2);
            }
            if(choice != 0) playSFX(menuSFX);
            if(choice==1) startGame();
            if(choice==2) quit = true;
            render();
        }
        if(quit) break ;
        while(!quit && inGame)
        {
            while(SDL_PollEvent(&e))
            {
                handleEvent(e);
                fixMenuChoice(1,4);
            }
            if(paused)
            {
                if(choice != 0) playSFX(menuSFX);
                if(choice==1) resumeGame();
                if(choice==2) toogleBGMusic();
                if(choice==3) ;
                if(choice==4) quit = 1;
                choice = 0;
            }
            else
                update();
            render();
            if(P.hp == 0 || B.hp == 0) endGame();
            // if(paused) cout<<"./././././././././././././\n";
            // debug();
        }
        if(quit) break ;
        while(!quit && isGameOver)
        {
            while(SDL_PollEvent(&e))
            {
                handleEvent(e);
                fixMenuChoice(1,3);
            }
            if(choice != 0) playSFX(menuSFX);
            if(choice==1) startGame();  //play again
            if(choice==2) introMenu(); //go back to menu  
            if(choice==3) quit = true;  //quit
            render();
        }
    }

}

void GAME::render()
{
    int startTime = SDL_GetTicks(); 

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    if(isStartMenu)
        drawMenuStart(renderer,menuChoice);
    if(inGame)
    {
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
    cout<<"pause: "<<paused<<endl;
    cout<<SDL_GetError()<<'\n';
}