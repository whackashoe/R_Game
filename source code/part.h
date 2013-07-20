#ifndef PART_H
#define PART_H
#include "preheader.h"
#include "sprite.h"
#define ASH_FRAMES 3
#define DUST_FRAMES 3
#define RAIN_FRAMES 1
#define FLOW_FRAMES 4
#define SAND_FRAMES 1
#define LEAFS_FRAMES 3
#define JETS_FRAMES 5
#define EXPLOSION_FRAMES 17
#define PUFF_FRAMES 8
#define BLOOD_FRAMES 5


#define P_ASH 100
#define ASH_GRAVITY (-1 << FIX)
#define ASH_MAXSPEED (15 << FIX)
#define ASH_ANIMSPEED 9

#define P_DUST 101
#define DUST_GRAVITY (-1 << FIX)
#define DUST_MAXSPEED (1 << FIX)
#define DUST_ANIMSPEED 2

#define P_RAIN 102
#define RAIN_GRAVITY (4 << FIX)
#define RAIN_MAXSPEED (28 << FIX)
#define RAIN_ANIMSPEED 13

#define P_FLOW 103
#define FLOW_GRAVITY (1 << FIX)
#define FLOW_MAXSPEED (10 << FIX)
#define FLOW_ANIMSPEED 11

#define P_SAND 104
#define SAND_GRAVITY (0 << FIX)
#define SAND_MAXSPEED (10 << FIX)
#define SAND_ANIMSPEED 36

#define P_LEAFS 105
#define LEAFS_GRAVITY (3 << FIX)
#define LEAFS_MAXSPEED (3 << FIX)
#define LEAFS_ANIMSPEED 6

#define P_JETS 106
#define JETS_GRAVITY (1 << FIX)
#define JETS_MAXSPEED (3 << FIX)
#define JETS_ANIMSPEED 2

#define P_EXPLOSION 107
#define EXPLOSION_GRAVITY (0 << FIX)
#define EXPLOSION_MAXSPEED (0 << FIX)
#define EXPLOSION_ANIMSPEED 1

#define P_PUFF 108
#define PUFF_GRAVITY (0 << FIX)
#define PUFF_MAXSPEED (0 << FIX)
#define PUFF_ANIMSPEED 2

#define P_BLOOD 109
#define BLOOD_GRAVITY (0 << FIX)
#define BLOOD_MAXSPEED (0 << FIX)
#define BLOOD_ANIMSPEED 2

static int animsAsh[1][MAX_ANIMS] =
    {
        // default
        {
            0, 1, 2}
    };
static int animsRain[1][MAX_ANIMS] =
    {
        // default
        {
            0}
    };
static int animsFlow[1][MAX_ANIMS] =
    {
        // default
        {
            0, 1, 2, 3}
    };
static int animsSand[1][MAX_ANIMS] =
    {
        // default
        {
            0}
    };
static int animsLeafs[1][MAX_ANIMS] =
    {
        // default
        {
            0, 1, 2}
    };
static int animsJets[1][MAX_ANIMS] =
    {
        // default
        {
            4, 3, 2, 1, 0}
    };
static int animsExplosion[1][MAX_ANIMS] =
    {
        // default
        {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}
    };
static int animsPuff[1][MAX_ANIMS] =
    {
        // default
        {
            0, 1, 2, 3, 4, 5, 6, 7}
    };
static int animsBlood[1][MAX_ANIMS] =
    {
        // default
        {
            0, 1, 2, 3, 4}
    };

class CPart: public CSprite
{
public:
    /////////////////////////////////
    void InitPart(SBITMAP *newImage, int newStyle, int newPosX, int newPosY,
                  int newMaxSpeed, int newGravity, int newRefX, int newRefY, int newLife, int newAnimSpeed);
};
#endif