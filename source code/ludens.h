#ifndef LUDENS_H
#define LUDENS_H

#include "preheader.h"
#include "sprite.h"
#define VOLCANO_FRAMES 49
#define SWAMP_FRAMES 94
#define HERO_FRAMES 87
#define TRACKER_FRAMES 9
#define CRAB_FRAMES 17
#define LIGHT_FRAMES 9
#define BUNNY_FRAMES 12
#define EXIT_FRAMES 2
#define HEX_FRAMES 1
#define MINI_FRAMES 5
#define KODAMA_FRAMES 16
#define HUT_FRAMES 6
#define STRANGLER_FRAMES 60
#define BALL_FRAMES 8
#define DOOR_FRAMES 10
#define SWITCH_FRAMES 5
#define ELEVATOR_FRAMES 4
#define ZORTH_FRAMES 49
#define PLAZMA_FRAMES 13
#define SPRING_FRAMES 2
#define GRENADE_FRAMES 6
#define RAZOR_FRAMES 3
#define BLOCK_FRAMES 6
#define RABBIT_FRAMES 1
#define PLATFORM_FRAMES 7
#define HOVER_FRAMES 12
#define LINE_FRAMES 2
#define HIDE_FRAMES 2
#define VSPRING_FRAMES 2
#define BIKE_FRAMES 25
#define DESTRUCT_FRAMES 2
#define SECRET_FRAMES 4
#define GUSTAV_FRAMES 5
#define DOME_FRAMES 1
#define WATER_FRAMES 8
#define RIDDLER_FRAMES 1
#define DUDE_FRAMES 2
#define FISHMAN_FRAMES 3
#define TERMINAL_FRAMES 5
#define MOLE_FRAMES 8
#define SWITCH2_FRAMES 4
#define BAG_FRAMES 2
#define OLDMAN_FRAMES 1
#define CHANGER_FRAMES 1


#define ANIM_DEFAULT_SPEED 1


#define ANIM_HERO_STAND 0
#define ANIM_HERO_RUN 1
#define ANIM_HERO_JUMP 2
#define ANIM_HERO_AIR_JUMP 3
#define ANIM_HERO_WALL_CLIMB 4
#define ANIM_HERO_WALL_JUMP 5
#define ANIM_HERO_FALL 6
#define ANIM_HERO_HIT 7
#define ANIM_HERO_DIE 8
#define ANIM_HERO_OPEN_UMB 9
#define ANIM_HERO_KNOCK 10
#define ANIM_HERO_CLOSE_UMB 11
#define ANIM_HERO_UMB 12
#define ANIM_HERO_RAIN 13
#define ANIM_HERO_IDLE 14
#define ANIM_HERO_DUCK 15
#define ANIM_HERO_RIDE 16
#define ANIM_HERO_TRUMPET 17
#define ANIM_HERO_HOVER 18
#define ANIM_HERO_UMBBACK 19
#define ANIM_HERO_TRUMPETOUT 20

#define ANIM_HERO_STAND_SPEED 2
#define ANIM_HERO_IDLE_SPEED 2

#define HERO 0
#define HERO_MAXSPEED (22 << FIX)
#define HERO_GRAVITY (2 << FIX)
#define HERO_MOVE (7 << FIX)
#define HERO_AIRMOVE (5 << FIX)
#define HERO_MAXAIRMOVE (3 << FIX)
#define HERO_FLOATMOVE (5 << FIX)
#define HERO_JUMP (11 << FIX)
#define HERO_WALL (4 << FIX)
#define HERO_WALLJUMP (5 << FIX)
#define HERO_WALLBACK (5 << FIX)
#define HERO_FLOAT (1 << FIX)
#define HERO_RADIUSX (7 << FIX)
#define HERO_RADIUSY (16 << FIX)
#define HERO_RADIUSHITX (18 << FIX)
#define HERO_RADIUSDUCKY (10 << FIX)
#define HERO_SIGHT (24 << FIX)

#define ANIM_LIGHT_STEADY 0
#define ANIM_LIGHT_GLOW 1
#define ANIM_LIGHT_FRIEND 2

#define LIGHT 1
#define LIGHT_MAXSPEED (5 << FIX)
#define LIGHT_MAXSPEED2 (13 << FIX)
#define LIGHT_GRAVITY (0 << FIX)
#define LIGHT_MOVE (1 << FIX)
#define LIGHT_SIGHT (5 << FIX)

#define ANIM_TRACKER_STEADY 0
#define ANIM_TRACKER_TRACK 1
#define ANIM_TRACKER_KICK 2
#define ANIM_TRACKER_DEAD 3

#define TRACKER 2
#define TRACKER_MAXSPEED (8 << FIX)
#define TRACKER_MAXSPEED2 (18 << FIX)
#define TRACKER_GRAVITY (0 << FIX)
#define TRACKER_MOVE (1 << FIX)
#define TRACKER_SIGHT (6 << FIX)
#define TRACKER_INTEREST 560
#define TRACKER_DEADTIME 2

#define ANIM_CRAB_STAND 0
#define ANIM_CRAB_WALK 1
#define ANIM_CRAB_ATTACK 2
#define ANIM_CRAB_DANCE 3

#define CRAB 3
#define CRAB_MAXSPEED (12 << FIX)
#define CRAB_MAXSPEED2 (6 << FIX)
#define CRAB_GRAVITY (1 << FIX)
#define CRAB_MOVE (5 << FIX)
#define CRAB_MOVECHASE (10 << FIX)
#define CRAB_SIGHTX (10 << FIX)
#define CRAB_SIGHTY (1 << FIX)
#define CRAB_SIGHTCLOSEX (4 << FIX)

#define ANIM_EXIT_CLOSED 0
#define ANIM_EXIT_OPEN 1

#define EXIT 4

#define ANIM_HEX_DEFAULT 0

#define HEX 5

#define ANIM_BUNNY_STAND 0
#define ANIM_BUNNY_JUMP 1
#define ANIM_BUNNY_FALL 2
#define ANIM_BUNNY_HIT 3

#define BUNNY 6
#define BUNNY2 7
#define BUNNY3 8
#define BUNNY_MAXSPEED (10 << FIX)
#define BUNNY_GRAVITY (1 << FIX)
#define BUNNY_JUMP (10 << FIX)
#define BUNNY_MOVE (1 << FIX)
#define BUNNY_SIGHT (3 << FIX)

#define ANIM_KODAMA_STAND 0
#define ANIM_KODAMA_RUN 1
#define ANIM_KODAMA_GRAB 2
#define ANIM_KODAMA_BLINK 3
#define ANIM_KODAMA_LOOK 4
#define ANIM_KODAMA_FADE 5
#define ANIM_KODAMA_FADEBLINK 6
#define ANIM_KODAMA_GIVE 7
#define ANIM_KODAMA_FALL 8

#define KODAMA 9
#define KODAMA_MAXSPEED (14 << FIX)
#define KODAMA_GRAVITY (1 << FIX)
#define KODAMA_MOVE (4 << FIX)
#define KODAMA_SIGHTX (10 << FIX)
#define KODAMA_SIGHTY (4 << FIX)

#define ANIM_HUT_FREE 0
#define ANIM_HUT_OCCUPIED 1

#define HUT 10

#define ANIM_STRANGLER_STAND 0
#define ANIM_STRANGLER_WALK 1
#define ANIM_STRANGLER_ATTACK 2
#define ANIM_STRANGLER_BLINK 3

#define STRANGLER 11
#define STRANGLER_MAXSPEED (8 << FIX)
#define STRANGLER_MAXSPEED2 (1 << FIX)
#define STRANGLER_GRAVITY (5 << FIX)
#define STRANGLER_MOVE (2 << FIX)
//#define STRANGLER_SIGHTX (12 << FIX)
#define STRANGLER_SIGHTX (19 << FIX)
#define STRANGLER_SIGHTY (2 << FIX)

#define ANIM_BALL_STOP 0
#define ANIM_BALL_ROLL 1

#define BALL 12
#define BALL_MAXSPEED (13 << FIX)
#define BALL_MAXSPEED2 (6 << FIX)
#define BALL_GRAVITY (5 << FIX)
#define BALL_MOVE (1 << FIX)

#define ANIM_DOOR_CLOSE 0
#define ANIM_DOOR_OPEN 1

#define DOOR 13

#define ANIM_SWITCH_ALL 0
#define ANIM_SWITCH_ON 1
#define ANIM_SWITCH_WRONG 2
#define ANIM_SWITCH_ZORTH 3
#define ANIM_SWITCH_CHANGE 4

#define SWITCH 14

#define ANIM_ELEVATOR_STOP 0
#define ANIM_ELEVATOR_GO 1

#define ELEVATOR 15
#define ELEVATOR_MAXSPEED (4 << FIX)
#define ELEVATOR_MOVE (1 << FIX)
#define ELEVATOR_WAITTIME 12

#define ANIM_ZORTH_STAND 0
#define ANIM_ZORTH_BREATH 1
#define ANIM_ZORTH_WALK 2
#define ANIM_ZORTH_SHOOT 3
#define ANIM_ZORTH_FLY 4
#define ANIM_ZORTH_AIM 5
#define ANIM_ZORTH_SPOT 6
#define ANIM_ZORTH_PATROLBREATH 7
#define ANIM_ZORTH_RELOAD 8
#define ANIM_ZORTH_ONBIKE 9
#define ANIM_ZORTH_DIE 10
#define ANIM_ZORTH_BARRIER 11
#define ANIM_ZORTH_KICK 12

#define ZORTH 16
#define ZORTH_MAXSPEED (10 << FIX)
#define ZORTH_GRAVITY (2 << FIX)
#define ZORTH_MOVE (1 << FIX)
#define ZORTH_FLYMOVE (3 << FIX)
#define ZORTH_MAXFALLSPEED (7 << FIX)
#define ZORTH_SIGHTX (25 << FIX)
#define ZORTH_SIGHTY (10 << FIX)
#define ZORTH_CLOSESIGHTX (4 << FIX)
#define ZORTH_MEDIUMSIGHTX (15 << FIX)
#define ZORTH_GRENADESIGHTX (9 << FIX)
#define ZORTH_INTEREST 1800
#define ZORTH_INTEREST2 400
#define ZORTH_INTEREST_MOMENT 120
#define ZORTH_AMMOPLAZMA 1
#define ZORTH_AMMOGRENADE 2
#define ZORTH_AMMOSLOWGRENADE 3
#define ZORTH_AMMORAZOR 4

#define ANIM_PLAZMA_DEFAULT 0
#define ANIM_PLAZMA_BOOM 1

#define PLAZMA 17
#define PLAZMA_MAXSPEED (16 << FIX)
#define PLAZMA_MAXSPEED2 (20 << FIX)
#define PLAZMA_GRAVITY (0 << FIX)
#define PLAZMA_MOVE (3 << FIX)
#define PLAZMA_MOVEY (1 << FIX)

#define SWITCH2 18

#define ANIM_GRENADE_READY 0
#define ANIM_GRENADE_BOOM 1
#define ANIM_GRENADE_UNARMED 2

#define GRENADE 19
#define GRENADE_MAXSPEED (10 << FIX)
#define GRENADE_GRAVITY (1 << FIX)
#define GRENADE_MOVE (10 << FIX)
#define GRENADE_MOVEY (1 << FIX)
#define GRENADE_LIFE 8
#define GRENADE_ARMEDTIME 4
#define GRENADE_EXPLODERADIUS (80 << FIX)

#define ANIM_SPRING_NORMAL 0
#define ANIM_SPRING_JUMP 1

#define SPRING 20
#define SPRING_MAXSPEED (10 << FIX)
#define SPRING_GRAVITY (2 << FIX)

#define ANIM_RAZOR_ARMED 0
#define ANIM_RAZOR_UNARMED 1

#define RAZOR 21
#define RAZOR_MAXSPEED (10 << FIX)
#define RAZOR_MAXSPEEDX (5 << FIX)
#define RAZOR_GRAVITY (1 << FIX)
#define RAZOR_MOVE (1 << FIX)
#define RAZOR_LIFE 34
#define RAZOR_ARMEDTIME 21

#define SWITCH3 22

#define ANIM_BLOCK_NORMAL 0
#define ANIM_BLOCK_CRACK 1

#define BLOCK 23
#define BLOCK_MAXSPEED (10 << FIX)
#define BLOCK_GRAVITY (2 << FIX)

#define ANIM_RABBIT_STAND 0
#define ANIM_RABBIT_JUMP 1

#define RABBIT 24
#define RABBIT_MAXSPEED (8 << FIX)
#define RABBIT_GRAVITY (1 << FIX)
#define RABBIT_JUMP (5 << FIX)
#define RABBIT_MOVE (6 << FIX)
#define RABBIT_SIGHT (5 << FIX)

#define ANIM_PLATFORM_NORMAL 0
#define ANIM_PLATFORM_CRACK 1

#define PLATFORM 25
#define PLATFORM_MAXSPEED (0 << FIX)
#define PLATFORM_GRAVITY (0 << FIX)

#define ANIM_HOVER_HOVER 0
#define ANIM_HOVER_KICKFLIP 1

#define HOVER 26
#define HOVER_MAXSPEED (12 << FIX)
#define HOVER_MAXSPEED2 (15 << FIX)
#define HOVER_GRAVITY (1 << FIX)
#define HOVER_JUMP (10 << FIX)
#define HOVER_MOVE (1 << FIX)

#define ANIM_LINE_DEFAULT 0

#define LINE 27

#define ANIM_HIDE_DEFAULT 0

#define HIDE 28

#define ANIM_VSPRING_NORMAL 0
#define ANIM_VSPRING_JUMP 1

#define VSPRING 29
#define VSPRING_MAXSPEED (0 << FIX)
#define VSPRING_GRAVITY (0 << FIX)

#define ANIM_BIKE_HOVER 0
#define ANIM_BIKE_ZORTH 1
#define ANIM_BIKE_ZORTHGO 2
#define ANIM_BIKE_ZORTHFIRE 3

#define BIKE 30
#define BIKE_MAXSPEED (9 << FIX)
#define BIKE_MAXSPEED2 (18 << FIX)
#define BIKE_GRAVITY (1 << FIX)
#define BIKE_JUMP (2 << FIX)
#define BIKE_MOVE (1 << FIX)
#define BIKE_SHOOTFREQ 46
#define BIKE_CRASHSPEED (8 << FIX)

#define ANIM_DESTRUCT_DEFAULT 0
#define ANIM_DESTRUCT_HIDDEN 1
#define ANIM_DESTRUCT_DESTROY 2

#define DESTRUCT 31
#define ANIM_SECRET_DEFAULT 0
#define SECRET 32
#define ANIM_GUSTAV_DEFAULT 0
#define ANIM_GUSTAV_PLAY 1
#define GUSTAV 33
#define GUSTAV_MAXSPEED (1 << FIX)

#define ANIM_DOME_DEFAULT 0
#define DOME 34

#define ANIM_WATER_ROLL 0

#define WATER 35
#define WATER_MAXSPEED (15 << FIX)
#define WATER_GRAVITY (2 << FIX)
#define WATER_MOVE (2 << FIX)

#define ANIM_RIDDLER_DEFAULT 0

#define RIDDLER 36
#define RIDDLER_SIGHT (9 << FIX)

#define ANIM_DUDE_DEFAULT 0

#define DUDE 37
#define DUDE_SIGHT (19 << FIX)

#define ANIM_FISHMAN_DEFAULT 0

#define FISHMAN 38
#define FISHMAN_SIGHT (20 << FIX)

#define ANIM_STEP_DEFAULT 0
#define ANIM_STEP_HIDDEN 1

#define STEP 39

#define ANIM_TERMINAL_SPEED 4
#define ANIM_TERMINAL_DEFAULT 0
#define ANIM_TERMINAL_DESTROYED 1

#define TERMINAL 40

#define ANIM_MOLE_WEST 0
#define ANIM_MOLE_SOUTH 1
#define ANIM_MOLE_EAST 2
#define ANIM_MOLE_NORTH 3
#define ANIM_MOLE_DRILL_WEST 4
#define ANIM_MOLE_DRILL_SOUTH 5
#define ANIM_MOLE_DRILL_EAST 6
#define ANIM_MOLE_DRILL_NORTH 7

#define MOLE 41
#define MOLE_MAXSPEED (5 << FIX)
#define MOLE_GRAVITY (0 << FIX)
#define MOLE_MOVE (1 << FIX)
#define MOLE_GO 100
#define MOLE_STOP 5

#define ANIM_BAG_DEFAULT 0
#define ANIM_BAG_MONEY 1

#define BAG 42
#define BAG_MAXSPEED (10 << FIX)
#define BAG_GRAVITY (0 << FIX)
#define BAG_GRAVITY2 (2 << FIX)

#define ANIM_OLDMAN_DEFAULT 0

#define OLDMAN 43
#define OLDMAN_SIGHT (130 << FIX)


#define ANIM_CHANGER_DEFAULT 0

#define CHANGER 44

	//
#define LASTLUDENS CHANGER

//////////////
#define AI_RUNAWAY 1
#define AI_FOLLOW 2
#define AI_NOTHING 3
#define AI_HIDDEN 4
#define AI_GIVE 5
#define AI_WAIT 6
#define AI_BACKUP 7
#define AI_PATROL 8
#define AI_ARMED 9
#define AI_BARRIER 10
//////////////

static int animsHero[21][MAX_ANIMS] =
    {
        // stand
        {
            //0, 0, 0, 1, 2, 2, 3, 3, 4, 5, 5}
            0, 0, 1, 2, 3, 3, 4, 5}
        ,
        // run
        {
            6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}
        ,
        // jump
        {
            18, 19, 20, 21, 22}
        ,
        // air jump
        {
            20, 21, 22}
        ,
        // wall climb
        {
            25, 24, 23}
        ,
        // wall jump
        {
            23, 24, 25}
        ,
        // fall
        {
            22, 22, 22, 22}
        ,
        // hit
        {
            26, 27, 28, 29, 30, 31, 32, 32, 32, 32, 32, 31}
        ,
        // die
        {
            34, 35, 36, 37, 38}
        ,
        // open umbrella
        {
            43, 44, 45, 46, 47}
        ,
        // knock
        {
            21, 22}
        ,
        // close umbrella
        {
            46, 45, 44, 43}
        ,
        // umbrella
        {
            48, 49, 50, 51, 52, 53, 54, 55}
        ,
        // rain
        {
            61, 62, 63, 64, 65
        }
        ,
        // idle
        {
            66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77
        }
        ,
        // duck
        {
            18, 19}
        ,
        // ride
        {
            58}
        ,
        // trumpet
        {
            82, 83, 84}
        ,
        // hover
        {
            13}
        ,
        // umbback
        {
            55, 56, 57, 58, 59, 60, 55}
        ,
        // trumpetout
        {
            78, 79, 80, 81}
    };
static int animsLight[3][MAX_ANIMS] =
    {
        // steady
        {
            3, 4, 5, 4}
        ,
        // glow
        {
            0, 1, 2, 1}
        ,
        // friend
        {
            6, 7, 8, 7}
    };

static int animsTracker[4][MAX_ANIMS] =
    {
        // steady
        {
            0, 1, 2, 3, 2, 1}
        ,
        // track
        {
            4, 5, 6, 5}
        ,
        // kick
        {
            7, 8}
        ,
        // dead
        {
            7, 8}
    };

static int animsCrab[4][MAX_ANIMS] =
    {
        // stand
        {
            0}
        ,
        // walk
        {
            13, 14, 16}
        ,
        // attack
        {
            7, 8, 9, 0, 10, 11, 12, 0}
        ,
        // dance
        {
            3, 4, 6, 1, 13, 14, 15, 16}
    };

static int animsBunny[4][MAX_ANIMS] =
    {
        // stand
        {
            1}
        ,
        // jump
        {
            0}
        ,
        // fall
        {
            2}
        ,
        // hit
        {
            3}
    };

static int animsBunny2[4][MAX_ANIMS] =
    {
        // stand
        {
            5}
        ,
        // jump
        {
            4}
        ,
        // fall
        {
            6}
        ,
        // hit
        {
            7}
    };

static int animsBunny3[4][MAX_ANIMS] =
    {
        // stand
        {
            9}
        ,
        // jump
        {
            8}
        ,
        // fall
        {
            10}
        ,
        // hit
        {
            11}
    };

static int animsExit[2][MAX_ANIMS] =
    {
        // closed
        {
            0}
        ,
        // opened
        {
            1}
    };

static int animsHex[1][MAX_ANIMS] =
    {
        // default
        {
            0}
    };

static int animsKodama[9][MAX_ANIMS] =
    {
        // stand
        {
            0}
        ,
        // run
        {
            4, 5, 6, 7, 8, 9, 10, 11}
        ,
        // grab
        {
            3}
        ,
        // blink
        {
            2, 2}
        ,
        // look
        {
            1, 1}
        ,
        // fade
        {
            12, 13}
        ,
        // faded blink
        {
            13}
        ,
        // give
        {
            2, 0, 1, 15, 15}
        ,
        // fall
        {
            15}
    };

static int animsHut[2][MAX_ANIMS] =
    {
        // free
        {
            0}
        ,
        // occupied
        {
            1, 2, 3, 4, 5}
    };

static int animsStrangler[4][MAX_ANIMS] =
    {
        // stand
        {
            20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34}
        ,
        // walk
        {
            47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59}
        ,
        // attack
        {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}
        ,
        // blink
        {
            35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46}
    };

static int animsBall[2][MAX_ANIMS] =
    {
        // stand
        {
            0}
        ,
        // roll
        {
            0, 1, 2, 3, 4, 5, 6, 7}
    };
static int animsDoor[2][MAX_ANIMS] =
    {
        // close
        {
            1, 2, 3, 4, 5, 6, 7, 8, 9
        }
        //7, 6, 5, 4, 3, 2, 1, 0}
        ,
        // open
        {
            0
            //0, 1, 2, 3, 4, 5, 6, 7
        }
    };
static int animsSwitch[5][MAX_ANIMS] =
    {
        // all
        {
            0}
        ,
        // on
        {
            0, 1, 2, 3, 4}
        ,
        // wrong
        {
            0}
        ,
        // zorth
        {
            4, 3, 2, 1, 0}
        ,
        // change
        {
            2}
    };
static int animsElevSwitch[5][MAX_ANIMS] =
    {
        // all
        {
            0}
        ,
        // on
        {
            3,2,1,0}
        ,
        // wrong
        {
            3,2,1,0}
        ,
        // zorth
        {
            3,2,1,0}
        ,
        // change
        {
            0,1,2,3}
    };
static int animsZorthSwitch[5][MAX_ANIMS] =
    {
        // all
        {
            3}
        ,
        // on
        {
            1}
        ,
        // wrong
        {
            2}
        ,
        // zorth
        {
            0}
        ,
        // change
        {
            4}
    };
static int animsElevator[2][MAX_ANIMS] =
    {
        // stop
        {
            0}
        ,
        // go
        {
            1, 2, 3}
    };
static int animsZorth[13][MAX_ANIMS] =
    {
        // stand
        {
            0, 0, 0, 1, 2, 3, 3, 3, 4, 5}
        ,
        // breath
        {
            6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}
        ,
        // walk
        {
            21, 22, 23, 23, 24, 25, 26, 27, 28, 28, 29}
        ,
        // shoot
        {
            30, 31, 32, 33, 34, 35, 36, 37, 44, 45}
        ,
        // fly
        {
            24, 25, 26}
        ,
        // aim
        {
            33, 33, 33, 33, 34, 35, 36, 33, 33, 33}
        ,
        // spot
        {
            30, 31, 32, 43, 44, 45, 16, 17, 18, 19, 20}
        ,
        // patrol breath
        {
            6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}
        ,
        // reload
        {
            38, 39, 40, 41, 42, 43}
        ,
        // onbike
        {
            46, 46}
        ,
        // die
        {
            38, 39, 40, 41, 42, 43}
        ,
        // barrier
        {
            47, 48}
        ,
        // kick
        {
            33, 33, 33, 33, 34, 35, 36, 33, 33, 33}
    };
static int animsPlazma[2][MAX_ANIMS] =
    {
        // default
        {
            0,1, 2, 3, 4, 5}
        ,
        // boom
        {
            6, 7, 8, 9, 10, 11, 12}
    };
static int animsGrenade[3][MAX_ANIMS] =
    {
        // default
        {
            0,1}
        ,
        // boom
        {
            4,5}
        ,
        // unarmed
        {
            2, 3}
    };
static int animsSpring[2][MAX_ANIMS] =
    {
        // normal
        {
            0}
        ,
        // jump
        {
            1}
    };
static int animsRazor[2][MAX_ANIMS] =
    {
        // armed
        {
            1,2}
        ,
        // unarmed
        {
            0}
    };
static int animsBlock[2][MAX_ANIMS] =
    {
        // normal
        {
            0}
        ,
        // crack
        {
            1, 2, 3, 4, 5}
    };
static int animsRabbit[2][MAX_ANIMS] =
    {
        // stand
        {
            0}
        ,
        // jump
        {
            0}
    };
static int animsPlatform[2][MAX_ANIMS] =
    {
        // normal
        {
            0}
        ,
        // crack
        {
            1, 2, 3, 4, 5, 6}
    };
static int animsHover[2][MAX_ANIMS] =
    {
        // hover
        {
            0, 1}
        ,
        // kickflip
        {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
    };
static int animsLines[1][MAX_ANIMS] =
    {
        // default
        {
            0}
    };
static int animsHide[1][MAX_ANIMS] =
    {
        // default
        {
            0, 1}
    };
static int animsVSpring[2][MAX_ANIMS] =
    {
        // normal
        {
            0}
        ,
        // jump
        {
            1}
    };
static int animsBike[4][MAX_ANIMS] =
    {
        // hover
        {
            0}
        ,
        // zorth
        {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}
        ,
        // zorthgo
        {
            20}
        ,
        // zorthfire
        {
            21, 22, 23, 24}
    };
static int animsDestruct[3][MAX_ANIMS] =
    {
        // default
        {
            0}
        ,
        // hidden
        {
            1}
        ,
        // destroy
        {
            1,1,1,1}
    };
static int animsSecret[1][MAX_ANIMS] =
    {
        // default
        {
            0, 1, 2, 3}
    };
static int animsGustav[2][MAX_ANIMS] =
    {
        // default
        {
            0, 0},
        // play
        {
            1, 2, 3, 4}
    };
static int animsDome[2][MAX_ANIMS] =
    {
        // default
        {
            0}
    };
static int animsWater[1][MAX_ANIMS] =
    {
        // roll
        {
            0, 1, 2, 3, 4, 5, 6, 7}
    };
static int animsRiddler[1][MAX_ANIMS] =
    {
        // default
        {
            0}
    };
static int animsDude[1][MAX_ANIMS] =
    {
        // default
        {
            0}
    };
static int animsFishman[1][MAX_ANIMS] =
    {
        // default
        {
            0}
    };
static int animsTerminal[2][MAX_ANIMS] =
    {
        // default
        {
            0, 1},
        // destroyed
        {
            2, 3, 4}
    };
static int animsMole[8][MAX_ANIMS] =
    {
        // w
        {
            0}
        ,
        // s
        {
            2}
        ,
        // e
        {
            4}
        ,
        // n
        {
            6}
		,
        // drill w
        {
            0, 1}
        ,
        // drill s
        {
            2, 3}
        ,
        // drill e
        {
            4, 5}
        ,
        // drill n
        {
            6, 7}
    };
static int animsBag[2][MAX_ANIMS] =
    {
        // default
        {
            0}
		,
        // money
        {
            1}
    };
static int animsOldman[1][MAX_ANIMS] =
    {
        // default
        {
            0}
    };
static int animsChanger[1][MAX_ANIMS] =
    {
        // default
        {
            0}
    };


class CLudens: public CSprite
{
public:
    int id;
    int state;
    int radiusX, radiusY;
    bool onGround, onWall, onCeiling;
    int idleCounter;
    int wallAllowLeft, wallAllowRight;
    int anchor;
    int anchorX, anchorY;
    int transferState;
    //AI stuff
    int target, oldTarget;
    int attitude, counter, oldAttitude;
    int interest;
    int owner;
    int ammoType, ammoCount;
    int aimY;
    int posArchiveIndex, trackIndex;
    int posArchiveX[MAX_POSARCHIVE], posArchiveY[MAX_POSARCHIVE];
	bool beenOnGround;
    /////////////////////////////////
    void InitLudens(int newId, SBITMAP *newImage, SBITMAP *newImageMirror, int newStyle, int newPosX, int newPosY, int newTeam, int newWidth, int newHeight,
                    int newMaxSpeed, int newGravity, int newRefX, int newRefY, int newRadiusX, int newRadiusY);
};
#endif