#pragma once
#include "constants.h"
#include "texture.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
using namespace std;

string defaultFont = "assets/ARIALBD.TTF";
class textTexture
{
public:
    textTexture(int x,int y,int size,string str,string fontPath,SDL_Color color);
    void render(SDL_Renderer *renderer);
    void setText(string str);
    void setTextFromNumber(int x);
    void setColor(SDL_Color color);
    void setSize(int size);
    void setFont(string path);
    void setPos(int x,int y);
private:
    int x,y;
    int size;
    ::string str;
    SDL_Color color;
    TTF_Font* font;
    string fontPath;
    SDL_Texture* texture;
};

textTexture::textTexture(int x,int y,int size,string str,string fontPath = defaultFont,SDL_Color color = {255,255,255,255})
{
    this->x=x;
    this->y=y;
    this->size=size;
    this->str=str;
    this->fontPath=fontPath;
    this->color=color;
    this->font=TTF_OpenFont(fontPath.c_str(),size);
    this->texture=NULL;
}

void textTexture::render(SDL_Renderer *renderer)
{
    if(font==NULL) 
    {
        cout<<"Font not found!"<<'\n';
        return ;
    }
    //std::cout<<"Rendering text..."<<str<<'\n';
    SDL_Surface* surface=TTF_RenderText_Solid(font,str.c_str(),color);
    texture=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_Rect rect={x,y,surface->w,surface->h};
    SDL_RenderCopy(renderer,texture,NULL,&rect);
    SDL_FreeSurface(surface);
}

void textTexture::setText(string str)
{
    this->str=str;
}
void textTexture::setTextFromNumber(int x)
{
    this->str=to_string(x);
}
void textTexture::setColor(SDL_Color color)
{
    this->color=color;
}

void textTexture::setSize(int size)
{
    this->size=size;
    this->font=TTF_OpenFont(fontPath.c_str(),size);
}

void textTexture::setFont(string path)
{
    this->fontPath=path;
    this->font=TTF_OpenFont(path.c_str(),size);
}

void textTexture::setPos(int x,int y)
{
    this->x=x;
    this->y=y;
}

void drawText(SDL_Renderer *renderer, int x, int y, int size, string s)
{
    textTexture t(x,y,size,s,defaultFont);
    t.render(renderer);
}