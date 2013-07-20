#include "preheader.h"
#include "ludens.h"

void CLudens::InitLudens(int newId, SBITMAP *newImage, SBITMAP *newImageMirror, int newStyle, int newPosX, int newPosY, int newTeam, int newWidth, int newHeight,
                         int newMaxSpeed, int newGravity, int newRefX, int newRefY, int newRadiusX, int newRadiusY)
{
    active = true;

    SpriteImage = newImage;
    SpriteImageMirror = newImageMirror;
    ActiveImage = SpriteImage;

    width = newWidth;
    height = newHeight;
    maxSpeed = newMaxSpeed;
    gravity = newGravity;

    id = newId;
    style = newStyle;

    refX = newRefX;
    refY = newRefY;

    posX = newPosX;
    posY = newPosY;
    oldX = posX;
    oldY = posY;
    velX = velY = 0 << FIX;
    radiusX = newRadiusX;
    radiusY = newRadiusY;
    state = 0;
    anchor = -1;
    anchorX = 0;
    anchorY = 0;
    transferState = 0;

    beenOnGround = onGround = onWall = onCeiling = false;

    convertPosition();

    oldTarget = target = -1;
    oldAttitude = attitude = newTeam;
    interest = 0;
    counter = 0;
    ammoType = ammoCount = aimY = 0;

    for (posArchiveIndex = 0; posArchiveIndex < MAX_POSARCHIVE; posArchiveIndex++)
    {
        posArchiveX[posArchiveIndex] = posX;
        posArchiveY[posArchiveIndex] = posY;//+3*(TILE_HEIGHT << FIX);
    }
    trackIndex = 0;

    life = DEFAULT_LIVES;

    animNum = -1;
    animDirection = 0;
    animBlock = false;
    animLoop = false;
    animTick = 0;
    animSpeed = 0;
    animSpeedTick = 0;

    switch (style)
    {
    case HERO :
        anims[ANIM_HERO_STAND].set(animsHero[ANIM_HERO_STAND], 8);
        anims[ANIM_HERO_RUN].set(animsHero[ANIM_HERO_RUN], 12);
        anims[ANIM_HERO_JUMP].set(animsHero[ANIM_HERO_JUMP], 5);
        anims[ANIM_HERO_AIR_JUMP].set(animsHero[ANIM_HERO_AIR_JUMP], 3);
        anims[ANIM_HERO_WALL_CLIMB].set(animsHero[ANIM_HERO_WALL_CLIMB], 3);
        anims[ANIM_HERO_WALL_JUMP].set(animsHero[ANIM_HERO_WALL_JUMP], 3);
        anims[ANIM_HERO_FALL].set(animsHero[ANIM_HERO_FALL], 4);
        anims[ANIM_HERO_HIT].set(animsHero[ANIM_HERO_HIT], 12);
        anims[ANIM_HERO_DIE].set(animsHero[ANIM_HERO_DIE], 5);
        anims[ANIM_HERO_OPEN_UMB].set(animsHero[ANIM_HERO_OPEN_UMB], 5);
        anims[ANIM_HERO_KNOCK].set(animsHero[ANIM_HERO_KNOCK], 2);
        anims[ANIM_HERO_CLOSE_UMB].set(animsHero[ANIM_HERO_CLOSE_UMB], 4);
        anims[ANIM_HERO_UMB].set(animsHero[ANIM_HERO_UMB], 8);
        anims[ANIM_HERO_RAIN].set(animsHero[ANIM_HERO_RAIN], 5);
        anims[ANIM_HERO_IDLE].set(animsHero[ANIM_HERO_IDLE], 12);
        anims[ANIM_HERO_DUCK].set(animsHero[ANIM_HERO_DUCK], 2);
        anims[ANIM_HERO_RIDE].set(animsHero[ANIM_HERO_RIDE], 1);
        anims[ANIM_HERO_TRUMPET].set(animsHero[ANIM_HERO_TRUMPET], 3);
        anims[ANIM_HERO_HOVER].set(animsHero[ANIM_HERO_HOVER], 1);
        anims[ANIM_HERO_UMBBACK].set(animsHero[ANIM_HERO_UMBBACK], 7);
        anims[ANIM_HERO_TRUMPETOUT].set(animsHero[ANIM_HERO_TRUMPETOUT], 4);
        break;
    case LIGHT :
        anims[ANIM_LIGHT_STEADY].set(animsLight[ANIM_LIGHT_STEADY], 4);
        anims[ANIM_LIGHT_GLOW].set(animsLight[ANIM_LIGHT_GLOW], 4);
        anims[ANIM_LIGHT_FRIEND].set(animsLight[ANIM_LIGHT_FRIEND], 4);
        break;
    case TRACKER :
        anims[ANIM_TRACKER_STEADY].set(animsTracker[ANIM_TRACKER_STEADY], 6);
        anims[ANIM_TRACKER_TRACK].set(animsTracker[ANIM_TRACKER_TRACK], 4);
        anims[ANIM_TRACKER_KICK].set(animsTracker[ANIM_TRACKER_KICK], 2);
        anims[ANIM_TRACKER_DEAD].set(animsTracker[ANIM_TRACKER_DEAD], 2);
        break;
    case CRAB :
        anims[ANIM_CRAB_STAND].set(animsCrab[ANIM_CRAB_STAND], 1);
        anims[ANIM_CRAB_WALK].set(animsCrab[ANIM_CRAB_WALK], 3);
        anims[ANIM_CRAB_ATTACK].set(animsCrab[ANIM_CRAB_ATTACK], 8);
        anims[ANIM_CRAB_DANCE].set(animsCrab[ANIM_CRAB_DANCE], 8);
        break;
    case BUNNY :
        anims[ANIM_BUNNY_STAND].set(animsBunny[ANIM_BUNNY_STAND], 1);
        anims[ANIM_BUNNY_JUMP].set(animsBunny[ANIM_BUNNY_JUMP], 1);
        anims[ANIM_BUNNY_FALL].set(animsBunny[ANIM_BUNNY_FALL], 1);
        anims[ANIM_BUNNY_HIT].set(animsBunny[ANIM_BUNNY_HIT], 1);
        break;
    case BUNNY2 :
        anims[ANIM_BUNNY_STAND].set(animsBunny2[ANIM_BUNNY_STAND], 1);
        anims[ANIM_BUNNY_JUMP].set(animsBunny2[ANIM_BUNNY_JUMP], 1);
        anims[ANIM_BUNNY_FALL].set(animsBunny2[ANIM_BUNNY_FALL], 1);
        anims[ANIM_BUNNY_HIT].set(animsBunny2[ANIM_BUNNY_HIT], 1);
        break;
    case BUNNY3 :
        anims[ANIM_BUNNY_STAND].set(animsBunny3[ANIM_BUNNY_STAND], 1);
        anims[ANIM_BUNNY_JUMP].set(animsBunny3[ANIM_BUNNY_JUMP], 1);
        anims[ANIM_BUNNY_FALL].set(animsBunny3[ANIM_BUNNY_FALL], 1);
        anims[ANIM_BUNNY_HIT].set(animsBunny3[ANIM_BUNNY_HIT], 1);
        break;
    case EXIT :
        anims[ANIM_EXIT_CLOSED].set(animsExit[ANIM_EXIT_CLOSED], 1);
        anims[ANIM_EXIT_OPEN].set(animsExit[ANIM_EXIT_OPEN], 1);
        break;
    case HEX :
        anims[ANIM_HEX_DEFAULT].set(animsHex[ANIM_HEX_DEFAULT], 1);
        break;
    case KODAMA :
        anims[ANIM_KODAMA_STAND].set(animsKodama[ANIM_KODAMA_STAND], 1);
        anims[ANIM_KODAMA_RUN].set(animsKodama[ANIM_KODAMA_RUN], 8);
        anims[ANIM_KODAMA_GRAB].set(animsKodama[ANIM_KODAMA_GRAB], 1);
        anims[ANIM_KODAMA_BLINK].set(animsKodama[ANIM_KODAMA_BLINK], 2);
        anims[ANIM_KODAMA_LOOK].set(animsKodama[ANIM_KODAMA_LOOK], 2);
        anims[ANIM_KODAMA_FADE].set(animsKodama[ANIM_KODAMA_FADE], 2);
        anims[ANIM_KODAMA_FADEBLINK].set(animsKodama[ANIM_KODAMA_FADEBLINK], 1);
        anims[ANIM_KODAMA_GIVE].set(animsKodama[ANIM_KODAMA_GIVE], 5);
        anims[ANIM_KODAMA_FALL].set(animsKodama[ANIM_KODAMA_FALL], 1);
        break;
    case HUT :
        anims[ANIM_HUT_FREE].set(animsHut[ANIM_HUT_FREE], 1);
        anims[ANIM_HUT_OCCUPIED].set(animsHut[ANIM_HUT_OCCUPIED], 5);
        break;
    case STRANGLER :
        anims[ANIM_STRANGLER_STAND].set(animsStrangler[ANIM_STRANGLER_STAND], 15);
        anims[ANIM_STRANGLER_WALK].set(animsStrangler[ANIM_STRANGLER_WALK], 13);
        anims[ANIM_STRANGLER_ATTACK].set(animsStrangler[ANIM_STRANGLER_ATTACK], 20);
        anims[ANIM_STRANGLER_BLINK].set(animsStrangler[ANIM_STRANGLER_BLINK], 12);
        break;
    case BALL :
        anims[ANIM_BALL_STOP].set(animsBall[ANIM_BALL_STOP], 0);
        anims[ANIM_BALL_ROLL].set(animsBall[ANIM_BALL_ROLL], 7);
        break;
    case DOOR :
        anims[ANIM_DOOR_CLOSE].set(animsDoor[ANIM_DOOR_CLOSE], 9);
        anims[ANIM_DOOR_OPEN].set(animsDoor[ANIM_DOOR_OPEN], 1);
        //setAnimation(ANIM_DEFAULT, 1, LEFT, false, false);
        break;
    case SWITCH :
        anims[ANIM_SWITCH_ALL].set(animsSwitch[ANIM_SWITCH_ALL], 1);
        anims[ANIM_SWITCH_ON].set(animsSwitch[ANIM_SWITCH_ON], 4);
        anims[ANIM_SWITCH_WRONG].set(animsSwitch[ANIM_SWITCH_WRONG], 1);
        anims[ANIM_SWITCH_ZORTH].set(animsSwitch[ANIM_SWITCH_ZORTH], 4);
        anims[ANIM_SWITCH_CHANGE].set(animsSwitch[ANIM_SWITCH_CHANGE], 1);
        break;
    case SWITCH2 :
        anims[ANIM_SWITCH_ALL].set(animsElevSwitch[ANIM_SWITCH_ALL], 4);
        anims[ANIM_SWITCH_ON].set(animsElevSwitch[ANIM_SWITCH_ON], 4);
        anims[ANIM_SWITCH_WRONG].set(animsElevSwitch[ANIM_SWITCH_WRONG], 4);
        anims[ANIM_SWITCH_ZORTH].set(animsElevSwitch[ANIM_SWITCH_ZORTH], 4);
        anims[ANIM_SWITCH_CHANGE].set(animsElevSwitch[ANIM_SWITCH_CHANGE], 4);
        break;
    case SWITCH3 :
        anims[ANIM_SWITCH_ALL].set(animsSwitch[ANIM_SWITCH_ALL], 1);
        anims[ANIM_SWITCH_ON].set(animsSwitch[ANIM_SWITCH_ON], 4);
        anims[ANIM_SWITCH_WRONG].set(animsSwitch[ANIM_SWITCH_WRONG], 1);
        anims[ANIM_SWITCH_ZORTH].set(animsSwitch[ANIM_SWITCH_ZORTH], 4);
        anims[ANIM_SWITCH_CHANGE].set(animsSwitch[ANIM_SWITCH_CHANGE], 1);
        break;
    case ELEVATOR :
        anims[ANIM_ELEVATOR_STOP].set(animsElevator[ANIM_ELEVATOR_STOP], 1);
        anims[ANIM_ELEVATOR_GO].set(animsElevator[ANIM_ELEVATOR_GO], 3);
        break;
    case ZORTH :
        anims[ANIM_ZORTH_STAND].set(animsZorth[ANIM_ZORTH_STAND], 10);
        anims[ANIM_ZORTH_BREATH].set(animsZorth[ANIM_ZORTH_BREATH], 15);
        anims[ANIM_ZORTH_WALK].set(animsZorth[ANIM_ZORTH_WALK], 11);
        anims[ANIM_ZORTH_SHOOT].set(animsZorth[ANIM_ZORTH_SHOOT], 10);
        anims[ANIM_ZORTH_FLY].set(animsZorth[ANIM_ZORTH_FLY], 1);
        anims[ANIM_ZORTH_AIM].set(animsZorth[ANIM_ZORTH_AIM], 10);
        anims[ANIM_ZORTH_SPOT].set(animsZorth[ANIM_ZORTH_SPOT], 11);
        anims[ANIM_ZORTH_PATROLBREATH].set(animsZorth[ANIM_ZORTH_PATROLBREATH], 15);
        anims[ANIM_ZORTH_RELOAD].set(animsZorth[ANIM_ZORTH_RELOAD], 6);
        anims[ANIM_ZORTH_ONBIKE].set(animsZorth[ANIM_ZORTH_ONBIKE], 2);
        anims[ANIM_ZORTH_DIE].set(animsZorth[ANIM_ZORTH_DIE], 6);
        anims[ANIM_ZORTH_BARRIER].set(animsZorth[ANIM_ZORTH_BARRIER], 2);
        anims[ANIM_ZORTH_KICK].set(animsZorth[ANIM_ZORTH_KICK], 10);
        break;
    case PLAZMA :
        anims[ANIM_PLAZMA_DEFAULT].set(animsPlazma[ANIM_PLAZMA_DEFAULT], 6);
        anims[ANIM_PLAZMA_BOOM].set(animsPlazma[ANIM_PLAZMA_BOOM], 7);
        break;
    case GRENADE :
        anims[ANIM_GRENADE_READY].set(animsGrenade[ANIM_GRENADE_READY], 2);
        anims[ANIM_GRENADE_BOOM].set(animsGrenade[ANIM_GRENADE_BOOM], 2);
        anims[ANIM_GRENADE_UNARMED].set(animsGrenade[ANIM_GRENADE_UNARMED], 2);
        break;
    case SPRING :
        anims[ANIM_SPRING_NORMAL].set(animsSpring[ANIM_SPRING_NORMAL], 1);
        anims[ANIM_SPRING_JUMP].set(animsSpring[ANIM_SPRING_JUMP], 1);
        break;
    case RAZOR :
        anims[ANIM_RAZOR_ARMED].set(animsRazor[ANIM_RAZOR_ARMED], 2);
        anims[ANIM_RAZOR_UNARMED].set(animsRazor[ANIM_RAZOR_UNARMED], 1);
        break;
    case BLOCK :
        anims[ANIM_BLOCK_NORMAL].set(animsBlock[ANIM_BLOCK_NORMAL], 1);
        anims[ANIM_BLOCK_CRACK].set(animsBlock[ANIM_BLOCK_CRACK], 5);
        break;
    case RABBIT :
        anims[ANIM_RABBIT_STAND].set(animsRabbit[ANIM_RABBIT_STAND], 1);
        anims[ANIM_RABBIT_JUMP].set(animsRabbit[ANIM_RABBIT_JUMP], 1);
        break;
    case PLATFORM :
        anims[ANIM_PLATFORM_NORMAL].set(animsPlatform[ANIM_PLATFORM_NORMAL], 1);
        anims[ANIM_PLATFORM_CRACK].set(animsPlatform[ANIM_PLATFORM_CRACK], 6);
        break;
    case HOVER :
        anims[ANIM_HOVER_HOVER].set(animsHover[ANIM_HOVER_HOVER], 2);
        anims[ANIM_HOVER_KICKFLIP].set(animsHover[ANIM_HOVER_KICKFLIP], 11);
        break;
    case LINE :
        anims[ANIM_LINE_DEFAULT].set(animsHover[ANIM_LINE_DEFAULT], 1);
        break;
    case HIDE :
        anims[ANIM_HIDE_DEFAULT].set(animsHide[ANIM_HIDE_DEFAULT], 1);
        break;
    case VSPRING :
        anims[ANIM_VSPRING_NORMAL].set(animsVSpring[ANIM_VSPRING_NORMAL], 1);
        anims[ANIM_VSPRING_JUMP].set(animsVSpring[ANIM_VSPRING_JUMP], 1);
        break;
    case BIKE :
        anims[ANIM_BIKE_HOVER].set(animsBike[ANIM_BIKE_HOVER], 1);
        anims[ANIM_BIKE_ZORTH].set(animsBike[ANIM_BIKE_ZORTH], 19);
        anims[ANIM_BIKE_ZORTHGO].set(animsBike[ANIM_BIKE_ZORTHGO], 1);
        anims[ANIM_BIKE_ZORTHFIRE].set(animsBike[ANIM_BIKE_ZORTHFIRE], 4);
        break;
    case DESTRUCT :
        anims[ANIM_DESTRUCT_DEFAULT].set(animsDestruct[ANIM_DESTRUCT_DEFAULT], 1);
        anims[ANIM_DESTRUCT_HIDDEN].set(animsDestruct[ANIM_DESTRUCT_HIDDEN], 1);
        anims[ANIM_DESTRUCT_DESTROY].set(animsDestruct[ANIM_DESTRUCT_DESTROY], 4);
        break;
    case SECRET :
        anims[ANIM_SECRET_DEFAULT].set(animsSecret[ANIM_SECRET_DEFAULT], 4);
        break;
    case GUSTAV :
        anims[ANIM_GUSTAV_DEFAULT].set(animsGustav[ANIM_GUSTAV_DEFAULT], 1);
        anims[ANIM_GUSTAV_PLAY].set(animsGustav[ANIM_GUSTAV_PLAY], 4);
        break;
    case DOME :
        anims[ANIM_DOME_DEFAULT].set(animsDome[ANIM_DOME_DEFAULT], 1);
        break;
    case WATER :
        anims[ANIM_WATER_ROLL].set(animsWater[ANIM_WATER_ROLL], 8);
        break;
    case RIDDLER :
        anims[ANIM_RIDDLER_DEFAULT].set(animsRiddler[ANIM_RIDDLER_DEFAULT], 1);
        break;
    case DUDE :
        anims[ANIM_DUDE_DEFAULT].set(animsDude[ANIM_DUDE_DEFAULT], 1);
        break;
    case FISHMAN :
        anims[ANIM_FISHMAN_DEFAULT].set(animsFishman[ANIM_FISHMAN_DEFAULT], 1);
        break;
    case STEP :
        anims[ANIM_STEP_DEFAULT].set(animsDestruct[ANIM_STEP_DEFAULT], 1);
        anims[ANIM_STEP_HIDDEN].set(animsDestruct[ANIM_STEP_HIDDEN], 1);
        break;
    case TERMINAL :
        anims[ANIM_TERMINAL_DEFAULT].set(animsTerminal[ANIM_TERMINAL_DEFAULT], 2);
        anims[ANIM_TERMINAL_DESTROYED].set(animsTerminal[ANIM_TERMINAL_DESTROYED], 3);
        break;
    case MOLE :
        anims[ANIM_MOLE_WEST].set(animsMole[ANIM_MOLE_WEST], 1);
        anims[ANIM_MOLE_SOUTH].set(animsMole[ANIM_MOLE_SOUTH], 1);
        anims[ANIM_MOLE_EAST].set(animsMole[ANIM_MOLE_EAST], 1);
        anims[ANIM_MOLE_NORTH].set(animsMole[ANIM_MOLE_NORTH], 1);
        anims[ANIM_MOLE_DRILL_WEST].set(animsMole[ANIM_MOLE_DRILL_WEST], 2);
        anims[ANIM_MOLE_DRILL_SOUTH].set(animsMole[ANIM_MOLE_DRILL_SOUTH], 2);
        anims[ANIM_MOLE_DRILL_EAST].set(animsMole[ANIM_MOLE_DRILL_EAST], 2);
        anims[ANIM_MOLE_DRILL_NORTH].set(animsMole[ANIM_MOLE_DRILL_NORTH], 2);
        break;
    case BAG :
        anims[ANIM_BAG_DEFAULT].set(animsBag[ANIM_BAG_DEFAULT], 1);
        anims[ANIM_BAG_MONEY].set(animsBag[ANIM_BAG_MONEY], 1);
        break;
    case OLDMAN :
        anims[ANIM_OLDMAN_DEFAULT].set(animsOldman[ANIM_OLDMAN_DEFAULT], 1);
        break;
    case CHANGER :
        anims[ANIM_CHANGER_DEFAULT].set(animsChanger[ANIM_CHANGER_DEFAULT], 1);
        break;
    }

     if (style == TERMINAL)
	    setAnimation(ANIM_DEFAULT, ANIM_TERMINAL_SPEED, LEFT, false, true);
	 else
		setAnimation(ANIM_TERMINAL_DEFAULT, ANIM_DEFAULT_SPEED, LEFT, false, true);
}