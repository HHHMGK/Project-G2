#pragma once

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FPS = 60;
const double PI = 3.14159265358979323846;

//tile
const int tSize=40;
const int nRow = SCREEN_HEIGHT/tSize;
const int nCol = SCREEN_WIDTH/tSize;

//player
const int pVel=10;
const int pSize=10;
const int playerSpawnX = SCREEN_WIDTH/2;
const int playerSpawnY = SCREEN_HEIGHT/2;

//boss
const int bossMaxHP = 1000;

//bullet
const int bSize=3;
const int maxBulletNumber = 300;
const int bVel=11;