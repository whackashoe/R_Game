#include "preheader.h"
#include "game.h"


void CGame::LudensAI(int num)
{
    Ludens[num].state = 0;
    int i;
    int chero, clight, ctracker, ccrab, cbunny, cbunny2, cbunny3,
    cexit, chex, ckodama, chut, cstrangler, cany, czorth, celevator,
    cdoor, cplazma, cswitch, cswitch2, cswitch3, cgrenade, crazor,
    cplatform, cterminal, cmole;
    int distX;
    int distY;
    int goX;
    int goY;


    // HERO
    if (Ludens[num].style == HERO)
    {
        chero = LudensSee(num, HERO, HERO_SIGHT, HERO_SIGHT);

        Ludens[num].target = -1;

        if (chero > -1)
            if (Map.tileSet != END_SET)
            {
                Ludens[num].target = chero;

                if ((Ludens[Ludens[num].target].posY+(100 << FIX)) < Ludens[num].posY)
                {
                    //	if (Ludens[Ludens[num].target].posX < Ludens[num].posX)
                    Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
                    //	else
                    //		Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
                }
                else
                {
                    if (Ludens[Ludens[num].target].posX > Ludens[num].posX)
                        Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
                    else
                        Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
                }

            }
    } // HERO

    // LIGHT
    if (Ludens[num].style == LIGHT)
    {
        chero = LudensSee(num, HERO, LIGHT_SIGHT, LIGHT_SIGHT);

        if ( (Ludens[num].attitude == AI_RUNAWAY))
            if (chero > -1)
            {
                if (Ludens[num].posX < Ludens[chero].posX)
                    Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
                if (Ludens[num].posX > Ludens[chero].posX)
                    Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
                if (Ludens[num].posY < Ludens[chero].posY)
                    Ludens[num].state = Ludens[num].state | UP_PRESSED;
                if (Ludens[num].posY > Ludens[chero].posY)
                    Ludens[num].state = Ludens[num].state | DOWN_PRESSED;
            }

        if ( (Ludens[num].attitude == AI_FOLLOW))
        {
            int k = Ludens[num].trackIndex;
            int distX = abs(Ludens[Ludens[num].target].posArchiveX[k] - Ludens[num].posX);
            int distY = abs(Ludens[Ludens[num].target].posArchiveY[k] - Ludens[num].posY);

            if (chero > -1)
            {
                Ludens[num].trackIndex = Ludens[Ludens[num].target].posArchiveIndex;
                goX = Ludens[Ludens[num].target].posX;
                goY = Ludens[Ludens[num].target].posY;
                distX = abs(goX - Ludens[num].posX);
                distY = abs(goY - Ludens[num].posY);
            }
            else //!visible
            {
                goX = Ludens[Ludens[num].target].posArchiveX[Ludens[num].trackIndex];
                goY = Ludens[Ludens[num].target].posArchiveY[Ludens[num].trackIndex];
                distX = abs(goX - Ludens[num].posX);
                distY = abs(goY - Ludens[num].posY);

                if ((distX < (32 << FIX))&&(distY < (32 << FIX)))
                {
                    Ludens[num].trackIndex++;
                    if (Ludens[num].trackIndex > MAX_POSARCHIVE - 1)
                        Ludens[num].trackIndex = 0;
                }
            } //end !visible

            if ( (goX) > Ludens[num].posX)
                Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
            if ( (goX)  < Ludens[num].posX)
                Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
            if ( (goY)  > Ludens[num].posY)
                Ludens[num].state = Ludens[num].state | DOWN_PRESSED;
            if ( (goY)  < Ludens[num].posY)
                Ludens[num].state = Ludens[num].state | UP_PRESSED;
        }

    } // LIGHT

    // TRACKER
    if (Ludens[num].style == TRACKER)
    {
        chero = LudensSee(num, HERO, TRACKER_SIGHT, TRACKER_SIGHT);
        ckodama = LudensSee(num, KODAMA, TRACKER_SIGHT, TRACKER_SIGHT);
        ccrab = LudensSee(num, CRAB, TRACKER_SIGHT, TRACKER_SIGHT);
        cstrangler = LudensSee(num, STRANGLER, TRACKER_SIGHT, TRACKER_SIGHT);

        cany = -1;
        if (Ludens[num].target == chero)
            cany = chero;
        if (Ludens[num].target == ckodama)
            cany = ckodama;
        if (Ludens[num].target == ccrab)
            cany = ccrab;
        if (Ludens[num].target == cstrangler)
            cany = cstrangler;

        if (Ludens[num].interest > 0)
            Ludens[num].interest--;
        if (Ludens[num].interest == 0)
        {
            Ludens[num].attitude = AI_RUNAWAY;
            Ludens[num].state = 0;
            Ludens[num].velX = Ludens[num].velY = 0;
            Ludens[num].setAnimation(ANIM_TRACKER_STEADY, 1, Ludens[num].animDirection, false, true);
            Ludens[num].target = -1;
        }

        if (Ludens[num].target == -1)
        {
            if (ccrab > -1)
                Ludens[num].target = ccrab;
            if (ckodama > -1)
                if (Ludens[ckodama].attitude != AI_HIDDEN)
                    Ludens[num].target = ckodama;
            if (chero > -1)
                Ludens[num].target = chero;
            if (cstrangler > -1)
                Ludens[num].target = cstrangler;
        }

        if (Ludens[num].target > -1)
            if (Ludens[num].attitude == AI_RUNAWAY)
                if (Ludens[num].animNum != ANIM_TRACKER_DEAD)
                {
                    Ludens[num].attitude = AI_FOLLOW;
                    Ludens[num].interest = TRACKER_INTEREST;
                    Ludens[num].trackIndex = Ludens[Ludens[num].target].posArchiveIndex;
                    Ludens[Ludens[num].target].posArchiveX[Ludens[num].trackIndex] = Ludens[Ludens[num].target].posX;
                    Ludens[Ludens[num].target].posArchiveY[Ludens[num].trackIndex] = Ludens[Ludens[num].target].posY;
                    if (Hearable(Ludens[num].posX, Ludens[num].posY))
                        Engine.Sound.PlaySample(4);
                }

        if (Ludens[num].target > -1)
            if (Ludens[num].attitude == AI_FOLLOW)
            {
                int k = Ludens[num].trackIndex;
                int distX = abs(Ludens[Ludens[num].target].posArchiveX[k] - Ludens[num].posX);
                int distY = abs(Ludens[Ludens[num].target].posArchiveY[k] - Ludens[num].posY);

                if (cany > -1)
                {
                    Ludens[num].trackIndex = Ludens[Ludens[num].target].posArchiveIndex;
                    goX = Ludens[Ludens[num].target].posX;
                    goY = Ludens[Ludens[num].target].posY;
                    distX = abs(goX - Ludens[num].posX);
                    distY = abs(goY - Ludens[num].posY);
                }
                else //!visible
                {
                    goX = Ludens[Ludens[num].target].posArchiveX[Ludens[num].trackIndex];
                    goY = Ludens[Ludens[num].target].posArchiveY[Ludens[num].trackIndex];
                    distX = abs(goX - Ludens[num].posX);
                    distY = abs(goY - Ludens[num].posY);

                    if ((distX < (48 << FIX))&&(distY < (48 << FIX)))
                    {
                        Ludens[num].trackIndex++;
                        if (Ludens[num].trackIndex > MAX_POSARCHIVE - 1)
                            Ludens[num].trackIndex = 0;

                        Ludens[num].interest = TRACKER_INTEREST;
                    }
                } //end !visible

                if ( (goX) > Ludens[num].posX)
                    Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
                if ( (goX)  < Ludens[num].posX)
                    Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
                if ( (goY)  > Ludens[num].posY)
                    Ludens[num].state = Ludens[num].state | DOWN_PRESSED;
                if ( (goY)  < Ludens[num].posY)
                    Ludens[num].state = Ludens[num].state | UP_PRESSED;
            }

    }
    // TRACKER

    // CRAB
    if (Ludens[num].style == CRAB)
    {
        bool left, right, was;
        left = right = was = false;

        chero = LudensSee(num, HERO, CRAB_SIGHTX, CRAB_SIGHTY);
        ckodama = LudensSee(num, KODAMA, CRAB_SIGHTX, CRAB_SIGHTY);
        clight = LudensSee(num, LIGHT, CRAB_SIGHTCLOSEX, CRAB_SIGHTY);

        Ludens[num].target = -1;

        if (ckodama > -1)
            if (Ludens[ckodama].attitude != AI_HIDDEN)
                Ludens[num].target = ckodama;
        if ((chero > -1)&&(clight == -1))
            Ludens[num].target = chero;
        if (clight > -1)
            if (Ludens[clight].attitude == AI_FOLLOW)
            {
                Ludens[num].counter = 4;
                if (Ludens[num].posX < Ludens[clight].posX)
                    Ludens[num].attitude = 1;
                else
                    Ludens[num].attitude = 2;
                Ludens[num].target = clight;
                Ludens[num].maxSpeed = CRAB_MAXSPEED2;
            }


        if (Ludens[num].target < 0)
        {
            //have some fun
            if (Ludens[num].counter < 0)
            {
                Ludens[num].attitude = Engine.random(4);
                Ludens[num].counter = 8;
            }
            else
            {
                if (Ludens[num].attitude == 2)
                {
                    if (!LudensCanGo(num, RIGHT, true, 2))
                    {
                        Ludens[num].attitude = 1;
                        was = true;
                    }
                }
                if (Ludens[num].attitude == 1)
                {
                    if (!LudensCanGo(num, LEFT, true, 2))
                        if (was)
                            Ludens[num].attitude = 0;
                        else
                            Ludens[num].attitude = 2;
                }

                if (Ludens[num].attitude == 1)
                    Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
                if (Ludens[num].attitude == 2)
                    Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
                if (Ludens[num].attitude == 3)
                    Ludens[num].state = Ludens[num].state | UP_PRESSED;
                if (Ludens[num].attitude == 10)
                    Ludens[num].state = Ludens[num].state | DOWN_PRESSED;
            }

            Ludens[num].counter--;
            return;
        }

        if (Ludens[num].counter > 0)
        {
            if (Ludens[num].attitude == 1)
                Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
            if (Ludens[num].attitude == 2)
                Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
            if (Ludens[num].attitude == 3)
                Ludens[num].state = Ludens[num].state | UP_PRESSED;
            if (Ludens[num].attitude == 10)
                Ludens[num].state = Ludens[num].state | DOWN_PRESSED;

            Ludens[num].counter--;
            return;
        }

        if (Ludens[num].target > -1)
        {
            if (Ludens[Ludens[num].target].posX > Ludens[num].posX)
                right = true;
            else
                left = true;

            if (left)
                if (LudensCanGo(num, LEFT, true, 2))
                    Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
            if (right)
                if (LudensCanGo(num, RIGHT, true, 2))
                    Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
        }
    } // CRAB

    // KODAMA
    if (Ludens[num].style == KODAMA)
    {
        bool left, right, was;
        left = right = was = false;

        chero = LudensSee(num, HERO, KODAMA_SIGHTX, KODAMA_SIGHTY);
        clight = LudensSee(num, LIGHT, KODAMA_SIGHTX, KODAMA_SIGHTY);
        ckodama = LudensSee(num, KODAMA, KODAMA_SIGHTX, KODAMA_SIGHTY);
        ccrab = LudensSee(num, CRAB, KODAMA_SIGHTX, KODAMA_SIGHTY);
        ctracker = LudensSee(num, TRACKER, KODAMA_SIGHTX, KODAMA_SIGHTY);
        chut = LudensSee(num, HUT, KODAMA_SIGHTX, KODAMA_SIGHTY);
        cstrangler = LudensSee(num, STRANGLER, STRANGLER_SIGHTX, STRANGLER_SIGHTY);

        Ludens[num].target = -1;
        if (ccrab > -1)
            Ludens[num].target = ccrab;
        if (ctracker > -1)
            Ludens[num].target = ctracker;
        if (cstrangler > -1)
        {
            Ludens[num].target = cstrangler;
            Ludens[num].attitude = AI_RUNAWAY;
        }
        if (chero > -1)
            Ludens[num].target = chero;
        if (chut > -1)
        {
            if (Ludens[chut].attitude != 2)
            {
                Ludens[num].attitude = AI_FOLLOW;
                //			Ludens[num].anchor = -1;
            }
            Ludens[num].target = chut;
        }

        if (Ludens[num].target < 0)
        {
            if (Ludens[num].attitude == AI_HIDDEN)
            {
                Ludens[num].attitude = AI_NOTHING;
            }
        }

        if (Ludens[num].target > -1)
        {
            if (Ludens[num].attitude == AI_FOLLOW)
            {
                if (Ludens[Ludens[num].target].posX > Ludens[num].posX)
                    right = true;
                else
                    left = true;

                if (left)
                    if (LudensCanGo(num, LEFT, true))
                        Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
                if (right)
                    if (LudensCanGo(num, RIGHT, true))
                        Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
            }

            if (Ludens[num].attitude == AI_RUNAWAY)
            {
                if (Ludens[Ludens[num].target].posX < Ludens[num].posX)
                    right = true;
                else
                    left = true;

                if (left)
                    if (LudensCanGo(num, LEFT, true))
                        Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
                    else
                        Ludens[num].attitude = AI_NOTHING;
                if (right)
                    if (LudensCanGo(num, RIGHT, true))
                        Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
                    else
                        Ludens[num].attitude = AI_NOTHING;
            }

            if (Ludens[num].attitude == AI_NOTHING)
            {
                Ludens[num].attitude = AI_HIDDEN;
                Ludens[num].setAnimation(ANIM_KODAMA_FADE, 4, Ludens[num].animDirection, false, false);
            }

            if (ckodama > -1)
                if ((Ludens[num].attitude == AI_NOTHING)&&(Ludens[ckodama].attitude == AI_HIDDEN))
                {
                    Ludens[num].attitude = AI_HIDDEN;
                    Ludens[num].setAnimation(ANIM_KODAMA_FADE, 4, Ludens[num].animDirection, false, false);
                }

            if (clight > -1)
                if (Ludens[clight].attitude == AI_FOLLOW)
                {
                    Ludens[num].attitude = AI_FOLLOW;
                }
                else
                    Ludens[num].attitude = AI_NOTHING;

            if (clight == -1)
                if (Ludens[num].attitude == AI_FOLLOW)
                    Ludens[num].attitude = AI_NOTHING;


        }
    } // KODAMA

    // STRANGLER
    if (Ludens[num].style == STRANGLER)
    {
        bool left, right, was, openDoor;
        left = right = was = openDoor = false;

        chero = LudensSee(num, HERO, STRANGLER_SIGHTX, STRANGLER_SIGHTY);
        ckodama = LudensSee(num, KODAMA, STRANGLER_SIGHTX, STRANGLER_SIGHTY);
        ccrab = LudensSee(num, CRAB, STRANGLER_SIGHTX, STRANGLER_SIGHTY);
        ctracker = LudensSee(num, TRACKER, STRANGLER_SIGHTX, STRANGLER_SIGHTY);
        czorth = LudensSee(num, ZORTH, STRANGLER_SIGHTX, STRANGLER_SIGHTY);
        cdoor = LudensSee(num, DOOR, STRANGLER_SIGHTX, STRANGLER_SIGHTY);

        Ludens[num].target = -1;

        if (ccrab > -1)
            Ludens[num].target = ccrab;
        if (chero > -1)
            Ludens[num].target = chero;
        if (ctracker > -1)
            Ludens[num].target = ctracker;
        if (ckodama > -1)
            //if (Ludens[ckodama].attitude != AI_HIDDEN)
            Ludens[num].target = ckodama;
        if (czorth > -1)
            Ludens[num].target = czorth;

		// prison door
		if (cdoor > -1)
			if ( (Ludens[cdoor].animNum == ANIM_DOOR_CLOSE)&&(Ludens[cdoor].posX < Ludens[num].posX) )
				Ludens[num].target = -1;
			else
				openDoor = true;

        if (Ludens[num].target < 0)
        {
		}

        if (Ludens[num].target > -1)
            //	if (Ludens[num].animNum != ANIM_STRANGLER_ATTACK)
        {
            if ( (Ludens[num].target != ctracker)&&(Ludens[num].target != czorth) )
            {
                if (Ludens[Ludens[num].target].posX > Ludens[num].posX)
                    right = true;
                else
                    left = true;
            }
            else
            {
                if (Ludens[Ludens[num].target].posX < Ludens[num].posX)
                    right = true;
                else
                    left = true;
            }

            if ( (Ludens[num].target == czorth)&&(openDoor) )
            {
				left = right = false;
		        if (Ludens[Ludens[num].target].posX > Ludens[num].posX)
				    right = true;
				else
					left = true;

				if (Ludens[Ludens[num].target].target > -1)
					if (Ludens[Ludens[Ludens[num].target].target].style == STRANGLER)
					{
						left = right = false;
		                if (Ludens[Ludens[num].target].posX < Ludens[num].posX)
				            right = true;
						else
							left = true;
					}
            }


            if (left)
                if (LudensCanGo(num, LEFT, true))
                    Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
            if (right)
                if (LudensCanGo(num, RIGHT, true))
                    Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
        }
    } // STRANGLER


    // BUNNY
    if ((Ludens[num].style == BUNNY)||(Ludens[num].style == BUNNY2))
    {
        chero = LudensSee(num, HERO, BUNNY_SIGHT, BUNNY_SIGHT);
        ckodama = LudensSee(num, KODAMA, BUNNY_SIGHT, BUNNY_SIGHT);
        ccrab = LudensSee(num, CRAB, BUNNY_SIGHT, BUNNY_SIGHT);
        ctracker = LudensSee(num, TRACKER, BUNNY_SIGHT, BUNNY_SIGHT);
        cstrangler = LudensSee(num, STRANGLER, BUNNY_SIGHT, BUNNY_SIGHT);

        //int cany = ((chero+1) | (ckodama+1) | (ccrab+1) | (ctracker+1) | (cstrangler+1));

        Ludens[num].target = -1;

        if (ctracker > -1)
            Ludens[num].target = ctracker;
        if (ckodama > -1)
            if (Ludens[ckodama].attitude != AI_HIDDEN)
                Ludens[num].target = ckodama;
        if (cstrangler > -1)
            Ludens[num].target = cstrangler;
        if (ccrab > -1)
            Ludens[num].target = ccrab;
        if (chero > -1)
            Ludens[num].target = chero;

        if (Ludens[num].style == BUNNY2)
            if (Ludens[num].target < 0)
            {
                return;
            }
            else
                Ludens[num].target = num;

        Ludens[num].state = Ludens[num].state | UP_PRESSED;
        if (Ludens[Ludens[num].target].posX > Ludens[num].posX)
            Ludens[num].animDirection = LEFT;
        else
            Ludens[num].animDirection = RIGHT;
    } // BUNNY

    // ELEVATOR
    if (Ludens[num].style == ELEVATOR)
    {
        if (Ludens[num].attitude == 100)
            if (LudensCanGo(num, UP, false))
                Ludens[num].state = Ludens[num].state | UP_PRESSED;

        if (Ludens[num].attitude == 101)
            if (LudensCanGo(num, DOWN, false))
                Ludens[num].state = Ludens[num].state | DOWN_PRESSED;
    } // ELEVATOR


    // ZORTH
    if (Ludens[num].style == ZORTH)
    {
        chero = LudensSee(num, HERO, ZORTH_SIGHTX, ZORTH_SIGHTY);
        czorth = LudensSee(num, ZORTH, ZORTH_SIGHTX, ZORTH_SIGHTY);
        celevator = LudensSee(num, ELEVATOR, ZORTH_CLOSESIGHTX, ZORTH_SIGHTY);
        cdoor = LudensSee(num, DOOR, ZORTH_SIGHTX, ZORTH_SIGHTY);
        cplazma = LudensSee(num, PLAZMA, ZORTH_SIGHTX, ZORTH_SIGHTY);
        cgrenade = LudensSee(num, GRENADE, ZORTH_GRENADESIGHTX, ZORTH_SIGHTY);
        cswitch = LudensSee(num, SWITCH, ZORTH_SIGHTX, ZORTH_SIGHTY);
        cswitch2 = LudensSee(num, SWITCH2, ZORTH_SIGHTX, ZORTH_SIGHTY);
        cswitch3 = LudensSee(num, SWITCH3, ZORTH_SIGHTX, ZORTH_SIGHTY);
        cplatform = LudensSee(num, PLATFORM, ZORTH_SIGHTX, ZORTH_SIGHTY);
        cterminal = LudensSee(num, TERMINAL, ZORTH_CLOSESIGHTX, ZORTH_SIGHTY);
        cstrangler = LudensSee(num, STRANGLER, ZORTH_SIGHTX, ZORTH_SIGHTY);
        cmole = LudensSee(num, MOLE, ZORTH_SIGHTX, ZORTH_SIGHTY);

        if (Ludens[num].attitude == AI_BARRIER)
        {
            if (czorth > -1)
            {
                Ludens[num].target = czorth;
                Ludens[num].interest = 40;
            }
            return;
        }


        // see mole coming at you!
        if (cmole > -1)
        {
            Ludens[num].state = 0;
			Ludens[num].attitude = AI_FOLLOW;

			if ((Ludens[cmole].posY - (48 << FIX)) < Ludens[num].posY)
				Ludens[num].counter = 2;

            if (Ludens[cmole].posX > Ludens[num].posX)
                Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
            else
                Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;

			return;
        }

        if (Ludens[num].attitude == AI_BACKUP)
            Ludens[num].attitude = Ludens[num].oldAttitude;

        // see companion
        if (czorth > -1)
        {
            if (Ludens[czorth].target > -1)
                if (Ludens[Ludens[czorth].target].style == HERO)
                {
                    Ludens[num].attitude = AI_FOLLOW;
                    Ludens[num].target = Ludens[num].oldTarget = Ludens[czorth].target;
                    Ludens[num].interest = ZORTH_INTEREST;
                    Ludens[num].trackIndex = Ludens[czorth].trackIndex;
                }

            if (czorth > num)
                if (Ludens[num].attitude != AI_BACKUP)
                {
                    Ludens[num].oldAttitude = Ludens[num].attitude;
                    Ludens[num].attitude = AI_BACKUP;
                }
        }

		// if seeking terminal, strangler, bunny3, block and spots hero
		if ( (chero > -1)&&(Ludens[num].target > -1) )
			if ( (Ludens[Ludens[num].target].style == TERMINAL)||(Ludens[Ludens[num].target].style == STRANGLER) 
				||(Ludens[Ludens[num].target].style == BUNNY3)||(Ludens[Ludens[num].target].style == BLOCK))
			{
				Ludens[num].target = -1;
			}

		// see terminal that has opened door
		if ( (cterminal > -1)&& (Ludens[cterminal].animNum != ANIM_TERMINAL_DESTROYED))
			if ( (Ludens[cterminal].target > -1)&&(Ludens[num].target != cterminal) )
				if ( (Ludens[Ludens[cterminal].target].style == DOOR)&&(Ludens[Ludens[cterminal].target].animNum == ANIM_DOOR_OPEN) )
				{					
					Ludens[num].oldTarget = Ludens[num].target;
					Ludens[num].target = cterminal;
					Ludens[num].attitude = AI_FOLLOW;
					Ludens[num].interest = ZORTH_INTEREST;
				}


        // see closed door
        if (cdoor > -1)
            if (Ludens[cdoor].animNum == ANIM_DOOR_CLOSE)
            {
                // search for door switch
             /*   if ((Ludens[num].target > -1)&&(cswitch > -1))
                    if ( ((Ludens[Ludens[num].target].posX > Ludens[cdoor].posX)&&(Ludens[cdoor].posX > Ludens[num].posX) )||
                            ( (Ludens[Ludens[num].target].posX < Ludens[cdoor].posX)&&(Ludens[cdoor].posX < Ludens[num].posX)) )
                        if (Ludens[Ludens[num].target].style != SWITCH)
                        {
                            Ludens[num].oldTarget = Ludens[num].target;
                            Ludens[num].target = cswitch;
                            Ludens[num].attitude = AI_FOLLOW;
                            Ludens[num].interest = ZORTH_INTEREST;
                        }
                if ((Ludens[num].target > -1)&&(cswitch3 > -1))
                    if ( ((Ludens[Ludens[num].target].posX > Ludens[cdoor].posX)&&(Ludens[cdoor].posX > Ludens[num].posX) )||
                            ( (Ludens[Ludens[num].target].posX < Ludens[cdoor].posX)&&(Ludens[cdoor].posX < Ludens[num].posX)) )
                        if (Ludens[Ludens[num].target].style != SWITCH3)
                        {
                            Ludens[num].oldTarget = Ludens[num].target;
                            Ludens[num].target = cswitch3;
                            Ludens[num].attitude = AI_FOLLOW;
                            Ludens[num].interest = ZORTH_INTEREST;
                        }
*/
				 if (Ludens[num].target > -1)
					if ( (Ludens[Ludens[num].target].style != SWITCH)&&(Ludens[Ludens[num].target].style != SWITCH3) )
                    if ( ((Ludens[Ludens[num].target].posX > Ludens[cdoor].posX)&&(Ludens[cdoor].posX > Ludens[num].posX) )||
                            ( (Ludens[Ludens[num].target].posX < Ludens[cdoor].posX)&&(Ludens[cdoor].posX < Ludens[num].posX)) )
					if ( (cswitch > -1)||(cswitch3 > -1) )
					{
                        Ludens[num].oldTarget = Ludens[num].target;
						Ludens[num].target = ClosestStyleLudens(num, SWITCH, SWITCH3, 0);
                        Ludens[num].attitude = AI_FOLLOW;
                        Ludens[num].interest = ZORTH_INTEREST;
					}
            }

		// target dead meat - and checked - go seek terminal
		if (Ludens[num].target > -1)
			if (!Ludens[Ludens[num].target].active)
			if ( ( abs(Ludens[Ludens[num].target].posX - Ludens[num].posX) < (TILE_WIDTH << FIX)) )
			{
				Ludens[num].target = -1;

				//if (cterminal > -1)
				{
					Ludens[num].target = ClosestStyleLudens(num, TERMINAL, TERMINAL, 0);;
					Ludens[num].attitude = AI_FOLLOW;
					Ludens[num].interest = ZORTH_INTEREST;
				}
			}

        // any target = hero ?
        cany = -1;
        if (Ludens[num].target == chero)
        {
            cany = chero;

            if (Ludens[num].attitude != AI_FOLLOW)
                Ludens[num].attitude = AI_FOLLOW;
        }
        if (Ludens[num].target == czorth)
        {
            cany = czorth;

            if (Ludens[num].attitude != AI_FOLLOW)
                Ludens[num].attitude = AI_FOLLOW;
        }
        if (Ludens[num].target == cstrangler)
        {
            cany = cstrangler;

            if (Ludens[num].attitude != AI_FOLLOW)
                Ludens[num].attitude = AI_FOLLOW;
        }


        if (Ludens[num].interest > 0)
            Ludens[num].interest--;
        if (Ludens[num].interest == 0)
        {
            Ludens[num].attitude = AI_PATROL;
            Ludens[num].state = 0;
            Ludens[num].velX = Ludens[num].velY = 0;
            Ludens[num].target = -1;
        }

		// if loses ground when on patrol on platform
		if ( (Ludens[num].attitude == AI_PATROL)&&(!Ludens[num].onGround)&&(Ludens[num].target == -1)&&(Ludens[num].beenOnGround)
			&&(Ludens[num].state == 0)&&(Ludens[num].counter < 1) )
		{
			Ludens[num].attitude = AI_FOLLOW;
			Ludens[num].interest = ZORTH_INTEREST;

			Ludens[num].target = ClosestStyleLudens(num, TERMINAL, TERMINAL, 0);
			if (Ludens[num].target > -1)
				Ludens[num].trackIndex = Ludens[Ludens[num].target].posArchiveIndex;
		}


        if (Ludens[num].target == -1)
        {
			// Hero see!
            if (chero > -1)
			{
				bool climb = false;
				if (Ludens[chero].animNum == ANIM_HERO_WALL_CLIMB) 
				{
					climb = true;
					if (abs(Ludens[chero].posY-Ludens[num].posY) < (TILE_WIDTH*3) << FIX) 
						climb = false;
				}

                if (((Ludens[num].animDirection == RIGHT)&&((Ludens[chero].posX > Ludens[num].posX)))||
                        ((Ludens[num].animDirection == LEFT)&&((Ludens[chero].posX < Ludens[num].posX))))
                    if ( (Ludens[chero].attitude != AI_HIDDEN)&&(!climb) )
                    {
                        Ludens[num].oldTarget = Ludens[num].target = chero;
                    }
			}
			// Strangler see!
            if (cstrangler > -1)
			{
				bool noDoor = true;

				if (cdoor > -1)
					if (Ludens[cdoor].animNum == ANIM_DOOR_CLOSE)
						noDoor = false;

				if (noDoor)
                if (((Ludens[num].animDirection == RIGHT)&&((Ludens[cstrangler].posX > Ludens[num].posX)))||
                        ((Ludens[num].animDirection == LEFT)&&((Ludens[cstrangler].posX < Ludens[num].posX))))
                    {
                        Ludens[num].oldTarget = Ludens[num].target = cstrangler;
                    }
			}

            // Patrol guard duty
            if (Ludens[num].attitude == AI_PATROL)
            {
				bool goLeft, goRight;
				goLeft = (LudensCanGo(num, LEFT, true));
				goRight = (LudensCanGo(num, RIGHT, true));

                if (Ludens[num].animDirection == RIGHT)
                    if (goRight)
                        Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
                    else
                    {
                        Ludens[num].setAnimation(ANIM_ZORTH_PATROLBREATH, 3, Ludens[num].animDirection, true, false);
                        //Ludens[num].animDirection = LEFT;
                    }
                if (Ludens[num].animDirection == LEFT)
                    if (goLeft)
                        Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
                    else
                    {
                        Ludens[num].setAnimation(ANIM_ZORTH_PATROLBREATH, 2, Ludens[num].animDirection, true, false);
                        //Ludens[num].animDirection = RIGHT;
                    }

				if ( (goLeft)||(goRight) )
                if ((Ludens[num].animNum == ANIM_ZORTH_PATROLBREATH)&&(Ludens[num].animTick == 14)&&(Ludens[num].animSpeedTick == 0))
                {
                    Ludens[num].setAnimation(ANIM_ZORTH_PATROLBREATH, 2, -Ludens[num].animDirection, true, false);
                    Ludens[num].animDirection = -Ludens[num].animDirection;
                }

				if ( (cterminal > -1)&&(Ludens[num].oldTarget == -1))
					Ludens[num].state = 0;
			}
        }

        /// I spotted you!
        if (Ludens[num].target > -1)
            if ((Ludens[num].attitude == AI_PATROL)||(Ludens[num].attitude == AI_NOTHING))
            {
                Ludens[num].attitude = AI_FOLLOW;
                Ludens[num].interest = ZORTH_INTEREST;
                Ludens[num].trackIndex = Ludens[Ludens[num].target].posArchiveIndex;
                if (Hearable(Ludens[num].posX, Ludens[num].posY))
                    Engine.Sound.PlaySample(16);
                Ludens[num].setAnimation(ANIM_ZORTH_SPOT, 2, Ludens[num].animDirection, true, false);
            }

        if (Ludens[num].target > -1)
            if (Ludens[num].attitude == AI_FOLLOW)
            {
                bool allowShot;

                if (cany > -1)
                {
                    Ludens[num].trackIndex = Ludens[Ludens[num].target].posArchiveIndex;
                    goX = Ludens[Ludens[num].target].posX;
                    goY = Ludens[Ludens[num].target].posY;
                    distX = abs(goX - Ludens[num].posX);
                    distY = abs(goY - Ludens[num].posY);

                    Ludens[num].state = 0;
                    //if ((Ludens[num].animNum != ANIM_ZORTH_SHOOT)&&(Ludens[num].animNum != ANIM_ZORTH_AIM))
                    if (goX > Ludens[num].posX)
                    {
                        Ludens[num].setAnimation(Ludens[num].animNum, Ludens[num].animSpeed, RIGHT, Ludens[num].animBlock, Ludens[num].animLoop);
                        Ludens[num].animDirection = RIGHT;
                    }
                    else
                    {
                        Ludens[num].setAnimation(Ludens[num].animNum, Ludens[num].animSpeed, LEFT, Ludens[num].animBlock, Ludens[num].animLoop);
                        Ludens[num].animDirection = LEFT;
                    }

                    allowShot = false;
                    if (cdoor > -1)
                        if (Ludens[cdoor].animNum == ANIM_DOOR_CLOSE)
                        {
                            if (((Ludens[num].animDirection == RIGHT)&&((Ludens[cdoor].posX < Ludens[num].posX)))||
                                    ((Ludens[num].animDirection == LEFT)&&((Ludens[cdoor].posX > Ludens[num].posX))))
                                allowShot = true;
                        }
                        else
                            allowShot = true;

                    if (cdoor == -1)
                        allowShot = true;

                    if ((czorth > -1)&&(Ludens[num].target != czorth))
                    {
                        if (((Ludens[num].animDirection == RIGHT)&&((Ludens[czorth].posX < Ludens[num].posX)))||
                                ((Ludens[num].animDirection == LEFT)&&((Ludens[czorth].posX > Ludens[num].posX))))
                            allowShot = true;
                        else
                            allowShot = false;
                    }

                    //	if (cplazma > -1)
                    //		allowShot = false;

                    if (cgrenade > -1)
                        allowShot = false;

                    if (celevator > -1)
                        allowShot = false;

                    if (distY > (32 << FIX))
                        allowShot = false;

                    if (Ludens[num].animBlock)
                        allowShot = false;

                    if (allowShot)
                    {
                        //	Ludens[num].setAnimation(ANIM_ZORTH_SHOOT, 2, Ludens[num].animDirection, false, false);
                        Ludens[num].state = FIRE_PRESSED;

                        // decide ammo
                        if (Ludens[num].ammoType == ZORTH_AMMORAZOR)
                            Ludens[num].ammoType = ZORTH_AMMOPLAZMA;

                        // duck shot!
                        if ((Ludens[cany].animNum == ANIM_HERO_DUCK)||(cplatform > -1))
                            Ludens[num].aimY = PLAZMA_MOVEY;
                        else
                            Ludens[num].aimY = 0;
                    }
                }
                else //!visible
                {
                    goX = Ludens[Ludens[num].target].posArchiveX[Ludens[num].trackIndex];
                    goY = Ludens[Ludens[num].target].posArchiveY[Ludens[num].trackIndex];
                    distX = abs(goX - Ludens[num].posX);
                    distY = abs(goY - Ludens[num].posY);

                    if ((distX < (32 << FIX))&&(distY < (32 << FIX)))
                    {
                        Ludens[num].trackIndex++;
                        if (Ludens[num].trackIndex > MAX_POSARCHIVE - 1)
                            Ludens[num].trackIndex = 0;

                        Ludens[num].interest = ZORTH_INTEREST;
                    }

                    // throw razors if lost contact
                    if ((Ludens[num].ammoCount > 0)&&(Ludens[num].posY < Ludens[Ludens[num].target].posY)
                            &&(celevator == -1)&&(cswitch2 == -1))
                        if ((!LudensCanGo(num, Ludens[num].animDirection, true))&&(Ludens[num].onGround))
                        {
                            Ludens[num].ammoType = ZORTH_AMMORAZOR;
                            //Ludens[num].setAnimation(ANIM_ZORTH_SHOOT, 1, Ludens[num].animDirection, false, false);
                            Ludens[num].state = FIRE_PRESSED;
                        }
                } //end !visible

                if ( distX > (2 << FIX))
                {
                    if ( (goX) > Ludens[num].posX)
                        if (LudensCanGo(num, RIGHT, false))
                            Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
                    if ( (goX)  < Ludens[num].posX)
                        if (LudensCanGo(num, LEFT, false))
                            Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
                }

              //  if ( (celevator == -1)&&( distX < (48 << FIX)) )
				if (Ludens[num].target > -1)
                if ( (celevator == -1)&&((distX < (48 << FIX))||(!Ludens[num].onGround))&&(Ludens[Ludens[num].target].style != TERMINAL) )
                    if ( (goY + (16 << FIX)) < Ludens[num].posY)						
                    {
                        if ( distX < (16 << FIX))
                            Ludens[num].state = UP_PRESSED;
                        else
                            Ludens[num].state = Ludens[num].state | UP_PRESSED;						

                    }
                //Ludens[num].state = Ludens[num].state | UP_PRESSED;

            }


		// --- end thoughts ---

        // see grenade coming at you!
        if (cgrenade > -1)
        {
            if ((Ludens[cgrenade].posX > Ludens[num].posX)&&(Ludens[cgrenade].velX < 0)||
                    (Ludens[cgrenade].posX < Ludens[num].posX)&&(Ludens[cgrenade].velX > 0))
            {
                Ludens[num].state = 0;
                Ludens[num].counter = 2;
                if (Ludens[cgrenade].posX > Ludens[num].posX)
                    Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
                else
                    Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
            }
        }

        // see plazma coming at you!
        if (cplazma > -1)
        {
            if ((Ludens[cplazma].posX > Ludens[num].posX)&&(Ludens[cplazma].velX < 0)||
                    (Ludens[cplazma].posX < Ludens[num].posX)&&(Ludens[cplazma].velX > 0))
            {
                Ludens[num].state = 0;
                Ludens[num].counter = 2;
                if (Ludens[cplazma].posX > Ludens[num].posX)
                    Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
                else
                    Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
            }
        }

        // see closed door, not behave stupid
        if (cdoor > -1)
            if ( (Ludens[cdoor].animNum == ANIM_DOOR_CLOSE)&&(abs(Ludens[num].posX - Ludens[cdoor].posX) < (TILE_WIDTH << FIX)) )
			if (Ludens[num].target > -1)
            {
				if ( (Ludens[num].posX > Ludens[cdoor].posX)&&(Ludens[num].animDirection == LEFT)
					&&(Ludens[num].posX > Ludens[Ludens[num].target].posX)&&(Ludens[cdoor].posX > Ludens[Ludens[num].target].posX) )
				{
					Ludens[num].state = 0;
				}

				if ( (Ludens[num].posX < Ludens[cdoor].posX)&&(Ludens[num].animDirection == RIGHT)
					&&(Ludens[num].posX < Ludens[Ludens[num].target].posX)&&(Ludens[cdoor].posX < Ludens[Ludens[num].target].posX) )
				{
					Ludens[num].state = 0;
				}
			}

    } // ZORTH


    // RABBIT
    if (Ludens[num].style == RABBIT)
    {
        chero = LudensSee(num, HERO, RABBIT_SIGHT, RABBIT_SIGHT);

        Ludens[num].target = -1;

        if (chero > -1)
        {
            Ludens[num].target = chero;

            Ludens[num].state = Ludens[num].state | UP_PRESSED;
            if (Ludens[Ludens[num].target].posX > Ludens[num].posX)
                Ludens[num].animDirection = LEFT;
            else
                Ludens[num].animDirection = RIGHT;
        }
    } // RABBIT


    // RIDDLER
    if (Ludens[num].style == RIDDLER)
    {
        chero = LudensSee(num, HERO, RIDDLER_SIGHT, RIDDLER_SIGHT);

        if (chero > -1)
        {
            if (Ludens[num].attitude < 100) //start talk
            {
                Dialog.RestartDialog();
                Dialog.SetDialog("Goodday Sir", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);
                sceneTimer = 0;
            }
            else
            {
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
                    Dialog.SetDialog("I am the riddler.", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
                    Dialog.SetDialog("If you answer correctly", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 70, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 3))
                    Dialog.SetDialog("you will win the whole game.", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 70, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 4))
                    Dialog.SetDialog("This is your one and only chance.", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 70, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 5))
                    Dialog.SetDialog("So listen carefully.", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 50, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 6))
                    Dialog.SetDialog("", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);

                if (mapNum == 7)
                {
                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 7))
                        Dialog.SetDialog("I will now think of a number", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 80, sceneTimer);
                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 8))
                        Dialog.SetDialog("from 1 to 10.", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 80, sceneTimer);
                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 9))
                        Dialog.SetDialog("Your goal is to guess that number.", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 80, sceneTimer);
                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 10))
                        Dialog.SetDialog("Ready?", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 70, sceneTimer);
                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 11))
                        Dialog.SetDialog("Lets begin.", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 70, sceneTimer);
                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 12))
                        Dialog.SetDialog("...", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 65, sceneTimer);
                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 13))
                        Dialog.SetDialog("Alright I've thought of a number what is it?", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 80, sceneTimer);
                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 14))
                        Dialog.SetDialog("", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 80, sceneTimer);

                    if (Dialog.count == 15)
                    {
                        if (Engine.key_1)
                            Dialog.SetDialog("1", DIALOG_HERO_X, DIALOG_HERO_Y, 30, sceneTimer); //15
                        if (Engine.key_2)
                            Dialog.SetDialog("2", DIALOG_HERO_X, DIALOG_HERO_Y, 30, sceneTimer); //15
                        if (Engine.key_3)
                            Dialog.SetDialog("3", DIALOG_HERO_X, DIALOG_HERO_Y, 30, sceneTimer); //15
                        if (Engine.key_4)
                            Dialog.SetDialog("4", DIALOG_HERO_X, DIALOG_HERO_Y, 30, sceneTimer); //15
                        if (Engine.key_5)
                            Dialog.SetDialog("5", DIALOG_HERO_X, DIALOG_HERO_Y, 30, sceneTimer); //15
                        if (Engine.key_6)
                            Dialog.SetDialog("6", DIALOG_HERO_X, DIALOG_HERO_Y, 30, sceneTimer); //15
                        if (Engine.key_7)
                            Dialog.SetDialog("7", DIALOG_HERO_X, DIALOG_HERO_Y, 30, sceneTimer); //15
                        if (Engine.key_8)
                            Dialog.SetDialog("8", DIALOG_HERO_X, DIALOG_HERO_Y, 30, sceneTimer); //15
                        if (Engine.key_9)
                            Dialog.SetDialog("9", DIALOG_HERO_X, DIALOG_HERO_Y, 30, sceneTimer); //15
                        if (Engine.key_0)
                            Dialog.SetDialog("10", DIALOG_HERO_X, DIALOG_HERO_Y, 30, sceneTimer); //15
                    }

                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 16))
                        Dialog.SetDialog("No.", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 30, sceneTimer);
                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 17))
                        Dialog.SetDialog("Goodbye.", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 20, sceneTimer);
                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 18))
                    {
                        Ludens[num].kill();
                    }
                }

                if (mapNum == 8)
                {
                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 7))
                        Dialog.SetDialog("Pick a number from 1 to 10.", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 70, sceneTimer);

                    if (Dialog.count == 8)
                    {
                        if (Engine.key_1)
                        {
                            Dialog.SetDialog("1", DIALOG_HERO_X, DIALOG_HERO_Y, 20, sceneTimer);
                            pick = 2;
                        }
                        if (Engine.key_2)
                        {
                            Dialog.SetDialog("2", DIALOG_HERO_X, DIALOG_HERO_Y, 20, sceneTimer);
                            pick = 3;
                        }
                        if (Engine.key_3)
                        {
                            Dialog.SetDialog("3", DIALOG_HERO_X, DIALOG_HERO_Y, 20, sceneTimer);
                            pick = 4;
                        }
                        if (Engine.key_4)
                        {
                            Dialog.SetDialog("4", DIALOG_HERO_X, DIALOG_HERO_Y, 20, sceneTimer);
                            pick = 5;
                        }
                        if (Engine.key_5)
                        {
                            Dialog.SetDialog("5", DIALOG_HERO_X, DIALOG_HERO_Y, 20, sceneTimer);
                            pick = 6;
                        }
                        if (Engine.key_6)
                        {
                            Dialog.SetDialog("6", DIALOG_HERO_X, DIALOG_HERO_Y, 20, sceneTimer);
                            pick = 7;
                        }
                        if (Engine.key_7)
                        {
                            Dialog.SetDialog("7", DIALOG_HERO_X, DIALOG_HERO_Y, 20, sceneTimer);
                            pick = 8;
                        }
                        if (Engine.key_8)
                        {
                            Dialog.SetDialog("8", DIALOG_HERO_X, DIALOG_HERO_Y, 20, sceneTimer);
                            pick = 9;
                        }
                        if (Engine.key_9)
                        {
                            Dialog.SetDialog("9", DIALOG_HERO_X, DIALOG_HERO_Y, 20, sceneTimer);
                            pick = 7000000;
                        }
                        if (Engine.key_0)
                        {
                            Dialog.SetDialog("10", DIALOG_HERO_X, DIALOG_HERO_Y, 20, sceneTimer);
                            pick = 99923909011;
                        }
                    }

                    static char buffer[10];
                    itoa(pick, buffer, 10);

                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 9))
                        Dialog.SetDialog(buffer, DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 25, sceneTimer);
                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 10))
                        Dialog.SetDialog("I win.", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 30, sceneTimer);
                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 11))
                        Dialog.SetDialog("But I'll give you another chance.", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 30, sceneTimer);
                    if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 12))
                    {
                        Dialog.SetDialog("Pick a number.", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 25, sceneTimer);
                        Dialog.count = 8;
                    }
                }

            }

            Ludens[num].attitude = 100;
            sceneTimer++;
        }
    }  // RIDDLER

    // DUDE
    if (Ludens[num].style == DUDE)
    {
        chero = LudensSee(num, HERO, DUDE_SIGHT, DUDE_SIGHT);

        if (chero > -1)
        {
            if (Ludens[num].attitude < 100) //start talk
            {
                Dialog.RestartDialog();
                Dialog.SetDialog("Hey, what's up?", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 30, sceneTimer);
                sceneTimer = 0;
            }
            else
            {
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
                    Dialog.SetDialog("Where are you running?", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);


                if ((sceneTimer > Dialog.lastTime + Dialog.duration)&&(Dialog.count == 5))
                {
                    Dialog.SetDialog("You'll spill my drink!", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 40, sceneTimer);
                    Dialog.count = 10;
                }

                if ((sceneTimer > Dialog.lastTime + Dialog.duration)&&(Dialog.count == 4))
                {
                    //		sceneLudens[0] = AddLudens(HERO, Ludens[myLudens].posX + (5 << FIX), Ludens[myLudens].posY);
                }
            }

            Ludens[num].attitude = 100;
            sceneTimer++;
        }
    }  // DUDE


    // FISHMAN
    if (Ludens[num].style == FISHMAN)
    {
        chero = LudensSee(num, HERO, FISHMAN_SIGHT, FISHMAN_SIGHT);

        if (chero > -1)
        {
            if (Ludens[num].attitude < 100) //start talk
            {
                Dialog.RestartDialog();
                Dialog.SetDialog("Only sorrow fills my heart now", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 70, sceneTimer);
                sceneTimer = 0;
            }
            else
            {
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
                    Dialog.SetDialog("Because sense has been lost somehow", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
                    Dialog.SetDialog("You have been caught right from the sky", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 3))
                    Dialog.SetDialog("Destiny, one cannot deny", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 4))
                    Dialog.SetDialog("You, the slippy pleasure maker", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 5))
                    Dialog.SetDialog("I, the two-legged life taker", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 6))
                    Dialog.SetDialog("If earlier would this cruel hint arrive", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 7))
                    Dialog.SetDialog("That angels only in water can survive", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 8))
                    Dialog.SetDialog("Today with me you would still be here alive", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 90, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 9))
                {
                    Dialog.SetDialog(".", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 30, sceneTimer);
                    choiceMenu = true;
                    choiceText[0] = "Wow that's a fat fish.";
                    choiceText[1] = "Who died?";
                    choiceText[2] = "Where's the nearest gas station?";
                }

                if (Dialog.count == 10)
                {
                    if (Engine.key_1)
                    {
                        Dialog.SetDialog(choiceText[0], DIALOG_HERO_X, DIALOG_HERO_Y, 20, sceneTimer);
                        Dialog.count = 12;
                        choiceMenu = false;
                    }
                    if (Engine.key_2)
                    {
                        Dialog.SetDialog(choiceText[1], DIALOG_HERO_X, DIALOG_HERO_Y, 20, sceneTimer);
                        Dialog.count = 12;
                        choiceMenu = false;
                    }
                    if (Engine.key_3)
                    {
                        Dialog.SetDialog(choiceText[2], DIALOG_HERO_X, DIALOG_HERO_Y, 20, sceneTimer);
                        Dialog.count = 15;
                        choiceMenu = false;
                    }
                }

                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 12))
                    Dialog.SetDialog("My sweet one, did we", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 13))
                    Dialog.SetDialog("Really live for a night?", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);

                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 15))
                    Dialog.SetDialog("I have forsaken you", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);
                if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 16))
                    Dialog.SetDialog("Will you ever forgive me!?", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 60, sceneTimer);
            }

            Ludens[num].attitude = 100;
            sceneTimer++;
        }
    }  // FISHMAN


    // OLDMAN
    if (Ludens[num].style == OLDMAN)
    {
        chero = LudensSee(num, HERO, OLDMAN_SIGHT, OLDMAN_SIGHT);
        czorth = LudensSee(num, ZORTH, OLDMAN_SIGHT, OLDMAN_SIGHT);

        if ((chero > -1)||(czorth > -1))
        {

			if (sceneTimer > 105)
			{
				Dialog.RestartDialog();
				int l = Engine.random(OLDMAN_LINES_NUM);
				Dialog.SetDialog(OldmanLines[l], DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 30 + strlen(OldmanLines[l])*2, sceneTimer);
				sceneTimer = 0;
			}

            sceneTimer++;
        }
    }  // OLDMAN


    /////////////////////////////////////////////////
}
