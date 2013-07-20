#include "preheader.h"
#include "part.h"

void CPart::InitPart(SBITMAP *newImage, int newStyle, int newPosX, int newPosY, int newMaxSpeed,
                     int newGravity, int newRefX, int newRefY, int newLife, int newAnimSpeed)
{
    active = true;

    SpriteImage = newImage;
    SpriteImageMirror = SpriteImage;
    ActiveImage = SpriteImage;

    width = 0;
    height = 0;
    maxSpeed = newMaxSpeed;
    gravity = newGravity;

    style = newStyle;

    refX = newRefX;
    refY = newRefY;

    posX = newPosX;
    posY = newPosY;
    oldX = posX;
    oldY = posY;
    velX = velY = 0;

    animNum = -1;
    animDirection = 0;
    animBlock = false;
    animLoop = false;
    animTick = 0;

    life = newLife;

    convertPosition();

    switch (style)
    {
    case P_ASH :
        anims[ANIM_DEFAULT].set(animsAsh[ANIM_DEFAULT], ASH_FRAMES);
        break;
    case P_DUST :
        anims[ANIM_DEFAULT].set(animsAsh[ANIM_DEFAULT], DUST_FRAMES);
        break;
    case P_RAIN :
        anims[ANIM_DEFAULT].set(animsRain[ANIM_DEFAULT], RAIN_FRAMES);
        break;
    case P_FLOW :
        anims[ANIM_DEFAULT].set(animsFlow[ANIM_DEFAULT], FLOW_FRAMES);
        break;
    case P_SAND :
        anims[ANIM_DEFAULT].set(animsSand[ANIM_DEFAULT], SAND_FRAMES);
        break;
    case P_LEAFS :
        anims[ANIM_DEFAULT].set(animsLeafs[ANIM_DEFAULT], LEAFS_FRAMES);
        setAnimation(ANIM_DEFAULT, newAnimSpeed, RIGHT, false, true);
        break;
    case P_JETS :
        anims[ANIM_DEFAULT].set(animsJets[ANIM_DEFAULT], JETS_FRAMES);
        break;
    case P_EXPLOSION :
        anims[ANIM_DEFAULT].set(animsExplosion[ANIM_DEFAULT], EXPLOSION_FRAMES);
        break;
    case P_PUFF :
        anims[ANIM_DEFAULT].set(animsPuff[ANIM_DEFAULT], PUFF_FRAMES);
        break;
    case P_BLOOD :
        anims[ANIM_DEFAULT].set(animsBlood[ANIM_DEFAULT], BLOOD_FRAMES);
        break;
    default :
        anims[ANIM_DEFAULT].set(animsRain[ANIM_DEFAULT], RAIN_FRAMES);
        break;
    }

    //setAnimation(ANIM_DEFAULT, newAnimSpeed, RIGHT, false, true);
    if (style != P_LEAFS)
        setAnimation(ANIM_DEFAULT, newAnimSpeed, RIGHT, false, false);

}