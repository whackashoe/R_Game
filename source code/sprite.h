#ifndef SPRITE_H
#define SPRITE_H
#include "globals.h"
#include "tilemap.h"
class CAnimation
{
public:
    int *animList;
    int framesNum;
    void set
        (int *newAnimList, int newFramesNum);
};
class CSprite
{
public:
    bool active;
    int width;
    int height;
    int style;
    int life;

    int posX, posY;
    int velX, velY;
    int oldX, oldY;
    int refX, refY;
    int screenX, screenY;

    int maxSpeed, gravity;
    SBITMAP *ActiveImage, *SpriteImage, *SpriteImageMirror;
    int numFrames;
    CAnimation anims[MAX_ANIMS];

    int animSpeed;
    int animSpeedTick;
    int animTick;
    int animNum;
    int animDirection;
    bool animLoop;
    bool animBlock;

    /////////////////////////////

    void moveSprite(int Vx, int Vy);

    void setPosition(int Px, int Py);
    void convertPosition();
    void advanceAnimations();
    void setAnimation(int newAnimNum, int newAnimSpeed, int direction, bool block, bool loop);
    void kill();
};
#endif