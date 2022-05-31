#pragma once
#include "texture.h"
#include "constants.h"

LTexture pTexture,bossTexture,tile;
LTexture pHealth;

void loadAllTexture(SDL_Renderer* renderer)
{
    //player, boss
    //pTexture.loadFromFile(renderer,"./assets/player.png");
    bossTexture.loadFromFile(renderer,"./assets/CosmicNose.png");
    //terrain
    tile.loadFromFile(renderer,"./assets/tile.png");
    //hud
    pHealth.loadFromFile(renderer,"./assets/playerHealth.png");

}

