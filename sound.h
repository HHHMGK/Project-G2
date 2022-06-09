#pragma once
#include <SDL2/SDL_mixer.h>
#include "constants.h"

Mix_Music *bgMusic;
Mix_Chunk *pShoot, *pHit, *bHit, *bShoot, *menuSFX;

void loadSounds() {
    bgMusic = Mix_LoadMUS("assets/backgroundMusic.wav");
    menuSFX = Mix_LoadWAV("assets/menuSFX.wav");
    // pShoot = Mix_LoadWAV("assets/pShoot.wav");
    // pHit = Mix_LoadWAV("assets/pHit.wav");
    // bHit = Mix_LoadWAV("assets/bHit.wav");
    // bShoot = Mix_LoadWAV("assets/bShoot.wav");
}
void toogleBGMusic() {
    if(Mix_PlayingMusic() == 0) 
        Mix_PlayMusic(bgMusic, -1);
    else
        if(Mix_PausedMusic() == 1)
            Mix_ResumeMusic();
        else 
            Mix_PauseMusic();
}
void restartBGMusic() {
    if(Mix_PlayingMusic() == 1)
        Mix_HaltMusic();
    Mix_PlayMusic(bgMusic, -1);
    Mix_VolumeMusic(volume);
}
void playSFX(Mix_Chunk *sfx) {
    Mix_VolumeChunk(menuSFX,volume);
    Mix_PlayChannel(-1, sfx, 0);
}

void changeVolume() {
    volume=min(max(0,volume),128);
    cout<<volume<<endl;
    Mix_VolumeMusic(volume);
    Mix_VolumeChunk(menuSFX,volume);
}