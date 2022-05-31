#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include "constants.h"
#include "texture.h"
#include "gameTexture.h"


int mapT[nRow][nCol];
void loadMap()
{
    std::ifstream map("assets/map.csv");
    std::string line,dat;
    int i=0,j=0;
    while(getline(map,line))
    {
        std::stringstream s(line);
        while(getline(s,dat,','))
        {
            mapT[i][j]=atoi(dat.c_str());
            j++;
        }
        i++;
        j=0;
    }
}
/*
class terrain
{
public:
    terrain(int x,int y,int type);
    void render(SDL_Renderer* renderer);
private:
    int x,y;
    int type;
};
terrain::terrain(int x=0,int y=0,int type=0)
{
    this->x = x;
    this->y = y;
    this->type = type;
}
void terrain::render(SDL_Renderer* renderer)
{
    tile.render(renderer,&tType[type],x,y);
}*/
SDL_Rect tType[3] = {{0,0,40,40},{40,0,40,40},{80,0,40,40}};
void renderTerrain(SDL_Renderer* renderer)
{
    for(int i=0;i<nRow;i++)
    {
        for(int j=0;j<nCol;j++)
        {
            /*terrain t(j*tSize,i*tSize,mapT[i][j]);
            t.render(renderer);*/
            tile.render(renderer,&tType[mapT[i][j]],j*tSize,i*tSize,tSize,tSize);
        }
    }
}

