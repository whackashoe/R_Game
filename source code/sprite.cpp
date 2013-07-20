#include "preheader.h"
#include "sprite.h"

void CAnimation::set
    (int *newAnimList, int newFramesNum)
{
    animList = newAnimList;
    framesNum = newFramesNum;
}


//////////////

void CSprite::convertPosition()
{
    if (velY > (maxSpeed))
        velY = maxSpeed;
    if (velY < ( -maxSpeed))
        velY = -maxSpeed;
    if (velX > (maxSpeed))
        velX = maxSpeed;
    if (velX < ( -maxSpeed))
        velX = -maxSpeed;

    posX = posX + velX;
    posY = posY + velY;

    screenX = posX >> FIX;
    screenY = posY >> FIX;
}

void CSprite::moveSprite(int Vx, int Vy)
{
    velX += Vx;
    velY += Vy;
}

void CSprite::setPosition(int Px, int Py)
{
    posX = Px;
    posY = Py;
    convertPosition();
}

void CSprite::advanceAnimations()
{
    animSpeedTick++;
    if (animSpeedTick == animSpeed)
    {
        animSpeedTick = 0;
        animTick++;

        if (animTick > (anims[animNum].framesNum - 1))
        {
            if (animLoop)
                animTick = 0;
            else
                animTick = (anims[animNum].framesNum - 1);

            if (animBlock)
            {
                animBlock = false;
                setAnimation(ANIM_DEFAULT, 1, animDirection, false, false);
                return;
            }
            animBlock = false;
        }
    }
}

void CSprite::setAnimation(int newAnimNum, int newAnimSpeed, int direction, bool block, bool loop)
{
    if ( (newAnimNum == animNum) && (direction == animDirection))
        return;
    if (animBlock)
        return;

    animNum = newAnimNum;
    animLoop = loop;
    animTick = 0;

    if (direction == LEFT)
    {
        ActiveImage = SpriteImageMirror;
    }
    else
    {
        ActiveImage = SpriteImage;
    }

    if (animDirection != direction)
        refX = width - refX;

    animDirection = direction;

    animBlock = block;
    animSpeedTick = 0;
    animSpeed = newAnimSpeed;
}

void CSprite::kill()
{
    velX = velY = maxSpeed = gravity = 0 << FIX;
    active = false;
}