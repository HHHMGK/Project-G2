#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "constants.h"


bool initSDL(SDL_Window* &window, SDL_Renderer* &renderer, std::string WINDOW_TITLE = "GAME")
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout<<"SDL_Init Error: "<<SDL_GetError()<<std::endl;
        return 0;
    }

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout<<"Window Init Error: "<<SDL_GetError()<<std::endl;
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::cout<<"Renderer Init Error: "<<SDL_GetError()<<std::endl;
        return 0;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (IMG_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout<<"IMG Init Error: "<<IMG_GetError()<<std::endl;
        return 0;
    }
    if (TTF_Init() != 0)
    {
        std::cout<<"TTF Init Error: "<<TTF_GetError()<<std::endl;
        return 0;
    }
    return 1;
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if ( SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}