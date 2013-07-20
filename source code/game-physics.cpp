#include "preheader.h"
#include "game.h"


bool CGame::LudensPhysics(int num)
{
    int i;
    int cany = -1;
    int chero, clight, ctracker, ccrab, cbunny, cbunny2, cbunny3,
    cexit, chex, ckodama, chut, cstrangler, cball, cdoor, cswitch,
    celevator, czorth, cplazma, cswitch2, cgrenade, cspring, crazor,
    cswitch3, cblock, cplatform, chover, cline, cvspring, cbike, crabbit,
    cwater, cdestruct, cterminal, cbag;

    Ludens[num].moveSprite(0, Ludens[num].gravity);

    if (Map.tileSet == OUBLIETTE_SET)
        Ludens[num].moveSprite(0, -Ludens[num].gravity/2);

    chero = LudensCollide(num, HERO, cany);
    clight = LudensCollide(num, LIGHT, i);
    ctracker = LudensCollide(num, TRACKER, cany);
    ccrab = LudensCollide(num, CRAB, cany);
    cbunny = LudensCollide(num, BUNNY, cany);
    cbunny2 = LudensCollide(num, BUNNY2, cany);
    cbunny3 = LudensCollide(num, BUNNY3, cany);
    cexit = LudensCollide(num, EXIT, cany);
    chex = LudensCollide(num, HEX, cany);
    ckodama = LudensCollide(num, KODAMA, cany);
    chut = LudensCollide(num, HUT, cany);
    cstrangler = LudensCollide(num, STRANGLER, cany);
    cball = LudensCollide(num, BALL, cany);
    cdoor = LudensCollide(num, DOOR, cany);
    cswitch = LudensCollide(num, SWITCH, cany);
    cswitch2 = LudensCollide(num, SWITCH2, cany);
    cswitch3 = LudensCollide(num, SWITCH3, cany);
    celevator = LudensCollide(num, ELEVATOR, cany);
    czorth = LudensCollide(num, ZORTH, cany);
    cplazma = LudensCollide(num, PLAZMA, cany);
    cgrenade = LudensCollide(num, GRENADE, cany);
    cspring = LudensCollide(num, SPRING, cany);
    cvspring = LudensCollide(num, VSPRING, cany);
    crazor = LudensCollide(num, RAZOR, cany);
    cblock = LudensCollide(num, BLOCK, cany);
    cplatform = LudensCollide(num, PLATFORM, cany);
    chover = LudensCollide(num, HOVER, cany);
    cline = LudensCollide(num, LINE, cany);
    cbike = LudensCollide(num, BIKE, cany);
    crabbit = LudensCollide(num, RABBIT, cany);
    cwater = LudensCollide(num, WATER, cany);
    cdestruct = LudensCollide(num, DESTRUCT, cany);
    cterminal = LudensCollide(num, TERMINAL, cany);
	cbag = LudensCollide(num, BAG, cany);

    // HERO
    if (Ludens[num].style == HERO)
    {
        if (cplazma > -1)
        {
            MyLudensDie();
            Ludens[cplazma].interest = 0;
            Ludens[cplazma].setAnimation(ANIM_PLAZMA_BOOM, 1, Ludens[num].animDirection, true, false);
            Ludens[cplazma].velX = Ludens[cplazma].velY = 0;
        }

        if (cball > -1)
        {
            MyLudensDie();
        }

        if (cgrenade > -1)
        {
            if (Ludens[cgrenade].attitude == AI_NOTHING)
            {
                if ( (Ludens[num].animNum == ANIM_HERO_HIT) && (Ludens[num].animTick > 4) && (Ludens[num].animTick < 7))
                {
                    LudensPush(num, cgrenade, 0);
                    Ludens[cgrenade].velX = Ludens[num].animDirection*abs(Ludens[cgrenade].velX);
                    Ludens[cgrenade].velY = -abs(Ludens[cgrenade].velY);
                }
            }
            else
            {
                MyLudensDie();
                Ludens[cgrenade].interest = 0;
            }
        }

        if (crazor > -1)
        {
            if (Ludens[crazor].attitude == AI_NOTHING)
            {
                if ( (Ludens[num].animNum == ANIM_HERO_HIT) && (Ludens[num].animTick > 4) && (Ludens[num].animTick < 7))
                {
                    LudensPush(num, crazor, 0);
                    Ludens[crazor].velX = Ludens[num].animDirection*abs(Ludens[crazor].velX);
                    Ludens[crazor].velY = -abs(Ludens[crazor].velY);
                }
            }
            else
            {
                Engine.Sound.PlaySample(25);
                MyLudensDie();
                Ludens[crazor].interest = 0;
            }
        }

        if (chover > -1)
            if (Ludens[num].anchor == -1)
            {
                LudensAttach(num, chover);
                Ludens[num].anchorX = 0;//Ludens[num].radiusX/2;
                Ludens[num].anchorY = -2*Ludens[chover].radiusY + (3 << FIX);
                Ludens[chover].target = num;
                if (hintTimer < 120)
                    showHint = true;
            }

        if (cbunny3 > -1)
        {
            Ludens[cbunny3].setAnimation(ANIM_BUNNY_HIT, 2, Ludens[cbunny3].animDirection, false, false);

            if ( (Ludens[num].animNum == ANIM_HERO_HIT) && (Ludens[num].animTick > 4) && (Ludens[num].animTick < 7))
            {
                if (Ludens[num].animDirection == LEFT)
                    Ludens[cbunny3].velX = -BUNNY_MAXSPEED/2;
                else
                    Ludens[cbunny3].velX = BUNNY_MAXSPEED/2;

                Ludens[cbunny3].velY = -4 * BUNNY_GRAVITY;
            }
        }

        if (cline > -1)
        {
            if (Ludens[num].anchor > -1)
                if (Ludens[Ludens[num].anchor].style == HOVER)
                    return true;

            if (Ludens[cline].target > -1)
            {
                if (Ludens[num].anchor != cline)
                {
                    if (Ludens[num].anchor == -1)
                    {
                        Ludens[num].anchorX = 0;
                        Ludens[num].anchorY = 10 << FIX;
                    }
                    else
                    {
                        Ludens[num].anchorX = (Ludens[num].posX - Ludens[cline].posX);
                        Ludens[num].anchorY = (Ludens[num].posY - Ludens[cline].posY) + (10 << FIX);
                    }
                    Ludens[num].anchor = cline;
                }
            }
            else
                if (Ludens[num].anchor > -1)
                    if (Ludens[Ludens[num].anchor].style == LINE)
                    {
                        Ludens[num].anchor = -1;
                        Ludens[num].velX = (Ludens[num].posX - Ludens[num].oldX);
                        Ludens[num].velY = (Ludens[num].posY - Ludens[num].oldY);
                    }
        }

        if (cstrangler > -1)
        {
            LudensPush(num, cstrangler, 0);
        }

		//pick money
        if (cbag > -1)
			if (Ludens[cbag].animNum == ANIM_BAG_MONEY)
			{
				Ludens[cbag].kill();

				bagsPicked++;
				if (bagsPicked>6)
					dialogStep = 1;
			}

		usingTerminal = false;
        
		if (cterminal > -1)
		    if (Ludens[cterminal].animNum == ANIM_TERMINAL_DEFAULT)
			{
				usingTerminal = true;
				if (terminalNum != cterminal)
					terminalLayer =  terminalPos = 0;
				terminalNum = cterminal;
	        }

		if (!usingTerminal)
			if (myLudens > -1)
				if (Ludens[myLudens].style == MOLE)
					myLudens = num;
    }



    // LIGHT
    if (Ludens[num].style == LIGHT)
    {
        if (clight > -1)
            if (Ludens[num].attitude != AI_NOTHING)
            {
                Ludens[num].velX = Ludens[num].velX + -Ludens[clight].velX / 3;
                Ludens[num].velY = Ludens[num].velY + -Ludens[clight].velY / 3;
            }

        if (chex > -1)
            if ((Ludens[num].attitude != AI_NOTHING) && (Ludens[chex].attitude != AI_NOTHING))
            {
                Ludens[num].attitude = AI_NOTHING;
                Ludens[chex].attitude = AI_NOTHING;
                Ludens[chex].target = num;
                Ludens[num].target = chex;
                Engine.Sound.PlaySample(1);
            }

        if (chero > -1)
        {
            if (Ludens[num].attitude == AI_RUNAWAY)
            {
                Ludens[num].attitude = AI_FOLLOW;
                Ludens[num].target = chero;
                Engine.Sound.PlaySample(2);
            }

            if ( (Ludens[chero].animNum == ANIM_HERO_HIT) && (Ludens[chero].animTick > 4) && (Ludens[chero].animTick < 7))
            {
                if (Ludens[chero].animDirection == LEFT)
                    Ludens[num].velX = -LIGHT_MAXSPEED2;
                else
                    Ludens[num].velX = LIGHT_MAXSPEED2;

                Ludens[num].maxSpeed = LIGHT_MAXSPEED2;
            }
        }

        if (chover > -1)
        {
            if (Ludens[num].attitude == AI_RUNAWAY)
            {
                Ludens[num].attitude = AI_FOLLOW;
                Ludens[num].target = chover;
                Engine.Sound.PlaySample(2);
            }
        }

        if (cdoor > -1)
            if (Ludens[cdoor].animNum == ANIM_DOOR_CLOSE)
            {
                LudensPush(num, cdoor, 0);
            }
    } //LIGHT

    // TRACKER
    if (Ludens[num].style == TRACKER)
    {
        if (clight > -1)
            if ((Ludens[num].animNum != ANIM_TRACKER_DEAD) && (Ludens[clight].attitude != AI_NOTHING))
                if (Ludens[clight].attitude == AI_FOLLOW)
                {
                    Ludens[num].velX = (-Ludens[num].velX + 2 * Ludens[clight].velX) >> 1;
                    Ludens[num].velY = (-Ludens[num].velY + 2 * Ludens[clight].velY) >> 1;
                    //	Ludens[num].interest = TRACKER_DEADTIME;
                    //	Ludens[num].setAnimation(ANIM_TRACKER_DEAD, 1, Ludens[num].animDirection, false, false);
                }

        if ((cbunny > -1) || (cbunny2 > -1) || (cbunny3 > -1))
        {
            //		Ludens[num].velX = -Ludens[num].velX;
            //		Ludens[num].velY = -Ludens[num].velY;
        }

        if (ctracker > -1)
        {
            Ludens[num].velX = Ludens[num].velX + -Ludens[ctracker].velX / 3;
            Ludens[num].velY = Ludens[num].velY + -Ludens[ctracker].velY / 3;
        }

        if (ckodama > -1)
        {
            Ludens[ckodama].kill();
            Ludens[num].setAnimation(ANIM_TRACKER_KICK, 1, Ludens[num].animDirection, false, false);
            Ludens[num].interest = 0;
            Ludens[num].target = -1;
            if (Hearable(Ludens[num].posX, Ludens[num].posY))
                Engine.Sound.PlaySample(5);
        }

        if (ccrab > -1)
        {
            Ludens[num].setAnimation(ANIM_TRACKER_KICK, 1, Ludens[num].animDirection, false, false);
            if (Hearable(Ludens[num].posX, Ludens[num].posY))
                Engine.Sound.PlaySample(5);
        }

        if (cstrangler > -1)
        {
            Ludens[num].setAnimation(ANIM_TRACKER_KICK, 1, Ludens[num].animDirection, false, false);
            if (Hearable(Ludens[num].posX, Ludens[num].posY))
                Engine.Sound.PlaySample(5);
        }

        if (chero > -1)
        {
            {
                if ( (Ludens[chero].animNum == ANIM_HERO_HIT) && (Ludens[chero].animTick > 4) && (Ludens[chero].animTick < 7))
                {
                    if (Ludens[chero].animDirection == LEFT)
                        Ludens[num].velX = -TRACKER_MAXSPEED2;
                    else
                        Ludens[num].velX = TRACKER_MAXSPEED2;
                    Ludens[num].maxSpeed = TRACKER_MAXSPEED2;
                }
                else
                {
                    Ludens[chero].life--;
                    if (Ludens[chero].life>0)
                        Ludens[chero].setAnimation(ANIM_HERO_KNOCK, 1, Ludens[chero].animDirection, false, false);
                    else
                        MyLudensDie();
                    Ludens[num].setAnimation(ANIM_TRACKER_KICK, 1, Ludens[num].animDirection, true, false);
                    Engine.Sound.PlaySample(5);
                }
            }

        }

        if (cball > -1)
        {
            LudensAttach(num, cball, 1, 0);
        }

    } // TRACKER


    // BUNNY
    if ((Ludens[num].style == BUNNY) || (Ludens[num].style == BUNNY2) || (Ludens[num].style == BUNNY3))
    {
        if (cbunny > -1)
        {
            //   Ludens[num].setAnimation(ANIM_BUNNY_HIT, 2, Ludens[num].animDirection, false, false);
            LudensAttach(num, cbunny, 1, -5);
            if (Ludens[num].style == BUNNY3)
            {
                AddLudens(BALL, Ludens[num].posX, Ludens[num].posY);
                Ludens[num].kill();
                Ludens[cbunny].kill();
            }
        }

        if (cbunny2 > -1)
        {
            //    Ludens[num].setAnimation(ANIM_BUNNY_HIT, 2, Ludens[num].animDirection, false, false);
            LudensAttach(num, cbunny2, 1, -5);
            if (Ludens[num].style == BUNNY3)
            {
                AddLudens(BALL, Ludens[num].posX, Ludens[num].posY);
                Ludens[num].kill();
                Ludens[cbunny2].kill();
            }
        }

        if (cbunny3 > -1)
        {
            //    Ludens[num].setAnimation(ANIM_BUNNY_HIT, 2, Ludens[num].animDirection, false, false);
            LudensPush(num, cbunny3, 0, false);
        }

        if (ctracker > -1)
        {
            Ludens[num].setAnimation(ANIM_BUNNY_HIT, 2, Ludens[num].animDirection, false, false);
            LudensAttach(num, ctracker, 2, 0);
            Ludens[ctracker].velX = Ludens[ctracker].velX/2;
            Ludens[ctracker].velY = Ludens[ctracker].velY/2;
            Ludens[ctracker].maxSpeed = TRACKER_MAXSPEED/2;
        }

        if (ccrab > -1)
        {
            Ludens[num].setAnimation(ANIM_BUNNY_HIT, 2, Ludens[num].animDirection, false, false);
            LudensAttach(num, ccrab, 1, 0);
        }

        if (cstrangler > -1)
        {
            Ludens[num].setAnimation(ANIM_BUNNY_HIT, 2, Ludens[num].animDirection, false, false);
            LudensAttach(num, cstrangler, 3, 1);
            Ludens[cstrangler].maxSpeed = STRANGLER_MAXSPEED2;
            if (Ludens[cstrangler].animNum == ANIM_STRANGLER_WALK)
                Ludens[cstrangler].animSpeed = 2;
        }

        if (chero > -1)
        {
            Ludens[num].setAnimation(ANIM_BUNNY_HIT, 2, Ludens[num].animDirection, false, false);

            if (Ludens[num].posX > Ludens[chero].posX)
            {
                Ludens[num].posX = Ludens[num].posX + abs(Ludens[num].velX);
                Ludens[num].velX = abs(Ludens[chero].velX);
            }
            else
            {
                Ludens[num].posX = Ludens[num].posX - abs(Ludens[num].velX);
                Ludens[num].velX = -abs(Ludens[chero].velX);
            }
            /*
            Ludens[num].counter = 8;
            if (Ludens[chero].posX > Ludens[num].posX)
            Ludens[num].attitude = 1;
            else
            Ludens[num].attitude = 2;
            */
            if (Ludens[num].style != BUNNY3)
                MyLudensDie();
        }

        if (cball > -1)
        {
            Ludens[num].kill();
        }

        if (clight > -1)
        {
            Ludens[num].setAnimation(ANIM_BUNNY_HIT, 2, Ludens[num].animDirection, false, false);

            /*	if (Ludens[num].posX > Ludens[clight].posX)
            {
            Ludens[num].posX = Ludens[num].posX + abs(Ludens[num].velX);
            Ludens[num].velX = abs(Ludens[clight].velX);
            }
            else
            {
            Ludens[num].posX = Ludens[num].posX - abs(Ludens[num].velX);
            Ludens[num].velX = -abs(Ludens[clight].velX);
            }*/
        }

        if (czorth > -1)
        {
        //    Ludens[czorth].kill();
        }

        if (cstrangler > -1)
            if (Ludens[num].style == BUNNY2)
            {
                Ludens[cstrangler].kill();
            }

    } // BUNNY


    // CRAB
    if (Ludens[num].style == CRAB)
    {
        if ((clight > -1) || (ctracker > -1) || (cbunny > -1) || (cbunny2 > -1) || (cbunny3 > -1) || (ckodama > -1) || (cstrangler > -1) )
        {
            Ludens[num].attitude = 10;
            Ludens[num].counter = 8;
        }

        if (clight > -1)
            if (Ludens[num].target > -1)
            {
                if (Ludens[Ludens[num].target].posX > Ludens[num].posX)
                    Ludens[num].attitude = 1;
                else
                    Ludens[num].attitude = 2;

                Ludens[num].counter = 14;
                Ludens[clight].velY = Ludens[clight].velY - LIGHT_MOVE;
            }

        if (ctracker > -1)
        {
            Ludens[num].counter = 8;
            if (Ludens[ctracker].posX > Ludens[num].posX)
                Ludens[num].attitude = 1;
            else
                Ludens[num].attitude = 2;
        }

        if (chero > -1)
        {
            Ludens[num].attitude = 10;
            Ludens[num].counter = 8;

            if ( (Ludens[chero].animNum == ANIM_HERO_HIT) && (Ludens[chero].animTick > 4) && (Ludens[chero].animTick < 7))
            {
                if (Ludens[chero].animDirection == LEFT)
                    Ludens[num].velX = Ludens[num].velX - (CRAB_MAXSPEED >> 2);
                else
                    Ludens[num].velX = Ludens[num].velX + (CRAB_MAXSPEED >> 2);

                Ludens[num].velY = -2 * CRAB_GRAVITY;

                Ludens[num].counter = 9;
                if (Ludens[chero].posX > Ludens[num].posX)
                    Ludens[num].attitude = 1;
                else
                    Ludens[num].attitude = 2;
            }
            else
                if ( (Ludens[num].animNum == ANIM_CRAB_ATTACK) && ( (Ludens[num].animTick < 2) || (Ludens[num].animTick == 3)
                        || (Ludens[num].animTick == 5) || (Ludens[num].animTick == 6)))
                {
                    //Engine.Sound.PlaySample(8);
                    MyLudensDie();
                }
        }

        if (cball > -1)
        {
            //LudensAttach(num, cball, 1, 0);
            Ludens[num].kill();
        }

        if (ccrab > -1)
        {
            if (Ludens[ccrab].posX > Ludens[num].posX)
            {
                //Ludens[ccrab].posX = Ludens[ccrab].posX + abs(Ludens[ccrab].velX);
                Ludens[ccrab].velX = abs(Ludens[num].velX);
            }
            else
            {
                //Ludens[ccrab].posX = Ludens[ccrab].posX - abs(Ludens[ccrab].velX);
                Ludens[ccrab].velX = -abs(Ludens[num].velX);
            }

            Ludens[num].counter = 8;
            if (Ludens[ccrab].posX > Ludens[num].posX)
                Ludens[num].attitude = 1;
            else
                Ludens[num].attitude = 2;
        }

    } // CRAB

    // EXIT
    if (Ludens[num].style == EXIT)
        if (Ludens[num].attitude == AI_NOTHING)
        {
            if (crabbit > -1)
                Ludens[crabbit].kill();

            if (chero > -1)
            {
                NextMap();
            }

            if ((czorth > -1)&&(mapNum >= 24 ))
            {
                NextMap();
            }
        } // EXIT

    // KODAMA
    if (Ludens[num].style == KODAMA)
    {
        if (ccrab > -1)
        {
            Ludens[num].anchor = ccrab;
            Ludens[num].anchorX = (-6 << FIX) + (Engine.random(14) << FIX);
            Ludens[num].anchorY = (-9 << FIX) + (Engine.random(3) << FIX);
        }

        if (ckodama > -1)
            if ((Ludens[num].attitude != AI_HIDDEN)&&(Ludens[num].onGround))
            {
                if (Ludens[ckodama].posX > Ludens[num].posX)
                {
                    Ludens[ckodama].posX = Ludens[ckodama].posX + abs(Ludens[ckodama].velX);
                    Ludens[ckodama].velX = abs(Ludens[num].velX);
                }
                else
                {
                    Ludens[ckodama].posX = Ludens[ckodama].posX - abs(Ludens[ckodama].velX);
                    Ludens[ckodama].velX = -abs(Ludens[num].velX);
                }
            }

        if (chero > -1)
        {
            if ((Ludens[num].attitude == AI_FOLLOW)&&(Ludens[num].anchor == -1))
            {
                Ludens[num].anchor = chero;
                Ludens[num].anchorX = (-6 << FIX) + (Engine.random(13) << FIX);
                Ludens[num].anchorY = (-6 << FIX) + (Engine.random(22) << FIX);
            }

            if ( (Ludens[chero].animNum == ANIM_HERO_HIT) && (Ludens[chero].animTick > 4) && (Ludens[chero].animTick < 7))
            {
                Ludens[num].attitude = AI_RUNAWAY;
                Ludens[num].anchor = -1;

                if (Ludens[chero].animDirection == LEFT)
                    Ludens[num].velX = Ludens[num].velX - (KODAMA_MAXSPEED >> 2);
                else
                    Ludens[num].velX = Ludens[num].velX + (KODAMA_MAXSPEED >> 2);

                Ludens[num].velY = -4 * KODAMA_GRAVITY;
            }

        }

        if (chut > -1)
            if (Ludens[chut].attitude == 0)
            {
                Ludens[num].setAnimation(ANIM_KODAMA_GIVE, 12, Ludens[num].animDirection, true, false);
                Ludens[num].anchor = chut;
                Ludens[num].attitude = AI_GIVE;
                Ludens[num].anchorX = 0;
                Ludens[num].anchorY = (8 << FIX);
                Ludens[chut].attitude = 2;
            }

        if (cball > -1)
        {
            //LudensAttach(num, cball, 1, 0);
            Ludens[num].kill();
        }

    } // KODAMA


    // STRANGLER
    if (Ludens[num].style == STRANGLER)
    {
        if (ckodama > -1)
            //if (Ludens[ckodama].attitude != AI_HIDDEN)
        {
            Ludens[num].state = 0;
            Ludens[num].setAnimation(ANIM_STRANGLER_ATTACK, 1, Ludens[num].animDirection, true, false);

            if ( (Ludens[num].animNum == ANIM_STRANGLER_ATTACK) && ( (Ludens[num].animTick == 9) || (Ludens[num].animTick == 10)
                    || (Ludens[num].animTick == 11) || (Ludens[num].animTick == 12)))
            {
                Ludens[ckodama].kill();
            }
        }

        if (ccrab > -1)
        {
            Ludens[num].state = 0;
            Ludens[num].setAnimation(ANIM_STRANGLER_ATTACK, 1, Ludens[num].animDirection, true, false);

            if ( (Ludens[num].animNum == ANIM_STRANGLER_ATTACK) && ( (Ludens[num].animTick == 9) || (Ludens[num].animTick == 10)
                    || (Ludens[num].animTick == 11) || (Ludens[num].animTick == 12)))
            {}

            Ludens[ccrab].counter = 14;
            if (Ludens[num].posX > Ludens[ccrab].posX)
                Ludens[ccrab].attitude = 1;
            else
                Ludens[ccrab].attitude = 2;

            Ludens[ccrab].posY = Ludens[ccrab].posY - Ludens[ccrab].gravity;
        }

        if (chero > -1)
        {
            Ludens[num].state = 0;
            Ludens[num].setAnimation(ANIM_STRANGLER_ATTACK, 1, Ludens[num].animDirection, true, false);

            if ( (Ludens[num].animNum == ANIM_STRANGLER_ATTACK) && ( (Ludens[num].animTick == 9) || (Ludens[num].animTick == 10)
                    || (Ludens[num].animTick == 11) || (Ludens[num].animTick == 12)))
            {
                MyLudensDie();
            }

            //		LudensPush(chero, num, 0);
        }

        if (czorth > -1)
        {
            Ludens[num].state = 0;

			//Ludens[czorth].oldAttitude = Ludens[czorth].attitude;
//            Ludens[czorth].oldTarget = Ludens[czorth].target = num;
			Ludens[czorth].target = num;
            Ludens[czorth].interest = ZORTH_INTEREST;
        }

        if (cball > -1)
        {
            //LudensAttach(num, cball, 1, 0);
            Ludens[num].kill();
        }

        if (cstrangler > -1)
        {
            if (Ludens[cstrangler].posX > Ludens[num].posX)
            {
                Ludens[cstrangler].posX = Ludens[cstrangler].posX + abs(Ludens[cstrangler].velX);
                Ludens[cstrangler].velX = abs(Ludens[num].velX);
            }
            else
            {
                Ludens[cstrangler].posX = Ludens[cstrangler].posX - abs(Ludens[cstrangler].velX);
                Ludens[cstrangler].velX = -abs(Ludens[num].velX);
            }
        }

        if (cplazma > -1)
        {
            Ludens[num].kill();
            Ludens[cplazma].interest = 0;
            Ludens[cplazma].setAnimation(ANIM_PLAZMA_BOOM, 1, Ludens[num].animDirection, true, false);
            Ludens[cplazma].velX = Ludens[cplazma].velY = 0;
        }

        if (cgrenade > -1)
        {
            Ludens[num].kill();
            Ludens[cgrenade].interest = 0;
        }

    } // STRANGLER


    // DOOR
    if (Ludens[num].style == DOOR)
        if (Ludens[num].animNum == ANIM_DOOR_CLOSE)
        {
            if (clight > -1)
            {
                LudensPush(clight, num, 0);
            }

            if (chero > -1)
            {
                LudensPush(chero, num, 0);
            }

            if (ccrab > -1)
            {
                LudensPush(ccrab, num, 0);
            }

            if (cstrangler > -1)
            {
                LudensPush(cstrangler, num, 0);
            }

            if (ckodama > -1)
            {
                LudensPush(ckodama, num, 0);
            }

            if (cball > -1)
            {
                LudensPush(cball, num, 0);
            }

            if (cbunny > -1)
            {
                LudensPush(cbunny, num, 0);
            }

            if (cbunny2 > -1)
            {
                LudensPush(cbunny2, num, 0);
            }

            if (cbunny3 > -1)
            {
                LudensPush(cbunny3, num, 0);
            }

            if (ctracker > -1)
            {
                LudensPush(ctracker, num, 0);
            }

            if (czorth > -1)
            {
                LudensPush(czorth, num, 0);

				int oldT = Ludens[czorth].target;

                // search for door switch
                if (Ludens[czorth].target > -1)
                    if (Ludens[Ludens[czorth].target].style != SWITCH)
                        Ludens[czorth].oldTarget = Ludens[czorth].target;

                if (Ludens[czorth].posX > Ludens[num].posX)
                    Ludens[czorth].target = ClosestStyleLudens(czorth, SWITCH, SWITCH, RIGHT);
                else
                    Ludens[czorth].target = ClosestStyleLudens(czorth, SWITCH, SWITCH, LEFT);
                // search for door zorth switch
                if (Ludens[czorth].target > -1)
                    if (Ludens[Ludens[czorth].target].style != SWITCH3)
                        Ludens[czorth].oldTarget = Ludens[czorth].target;

                if (Ludens[czorth].posX > Ludens[num].posX)
                    Ludens[czorth].target = ClosestStyleLudens(czorth, SWITCH3, SWITCH3, RIGHT);
                else
                    Ludens[czorth].target = ClosestStyleLudens(czorth, SWITCH3, SWITCH3, LEFT);

				// go on patrol if can't open door
				if (Ludens[czorth].target > -1)
					if ( (Ludens[Ludens[czorth].target].style != SWITCH)&&(Ludens[Ludens[czorth].target].style != SWITCH3) )
					{
                       Ludens[czorth].target = -1;
					   Ludens[czorth].attitude = AI_PATROL;
					   Ludens[czorth].interest = 0;
					}
					else
					if ( ( (Ludens[czorth].animDirection == LEFT)&&(Ludens[czorth].posX > Ludens[num].posX) )||
						( (Ludens[czorth].animDirection == RIGHT)&&(Ludens[czorth].posX < Ludens[num].posX) ) )
					{
                       Ludens[czorth].target = -1;
					   Ludens[czorth].attitude = AI_PATROL;
					   Ludens[czorth].interest = 0;
					}
				if (Ludens[czorth].target == oldT)
				{
                   Ludens[czorth].target = -1;
				   Ludens[czorth].attitude = AI_PATROL;
				   Ludens[czorth].interest = 0;
				}

                Ludens[czorth].attitude = AI_FOLLOW;
                Ludens[czorth].interest = ZORTH_INTEREST2;
            }

            if (cplazma > -1)
            {
                //	LudensPush(cplazma, num, 0);
                Ludens[cplazma].velX = -Ludens[cplazma].velX;
                Ludens[cplazma].velY = -Ludens[cplazma].velY;
            }

            if (cgrenade > -1)
            {
                //	LudensPush(cplazma, num, 0);
                Ludens[cgrenade].velX = -Ludens[cgrenade].velX;
                Ludens[cgrenade].velY = -Ludens[cgrenade].velY;
                Ludens[cgrenade].interest--;
				LudensPush(cgrenade, num, 0);
            }

            if (crazor > -1)
            {
                Ludens[crazor].velX = -Ludens[crazor].velX;
                Ludens[crazor].velY = -Ludens[crazor].velY;
                //Ludens[crazor].interest--;
				LudensPush(crazor, num, 0);
            }

            if (chover > -1)
            {
                LudensPush(chover, num, 0);
            }

            if (cbike > -1)
            {
                AddLudens(GRENADE, Ludens[cbike].posX, Ludens[cbike].posY - (7 << FIX));
                if (Ludens[cbike].target > -1)
                    Ludens[Ludens[cbike].target].kill();
                Ludens[cbike].kill();
            }
        } //DOOR

    // SWITCH DOOR
    if (Ludens[num].style == SWITCH)
    {
        if ((chero > -1)||(czorth > -1))
        {
            if (czorth > -1)
            {
                if (Ludens[czorth].target == num)
                {
                    Ludens[czorth].target = Ludens[czorth].oldTarget;
                    if (Ludens[czorth].target == -1)
                    {
                        Ludens[czorth].interest = 0;
                    }
                    else
                    {
                        Ludens[czorth].attitude = AI_FOLLOW;
                        Ludens[czorth].interest = ZORTH_INTEREST;
                    }
                }

                //always open for chasing zorth
                if ((Ludens[czorth].attitude != AI_PATROL)&&(Ludens[czorth].attitude != AI_NOTHING))
                    Ludens[num].animNum = ANIM_SWITCH_ALL;
            }

            if (Ludens[num].animNum != ANIM_SWITCH_CHANGE)
            {
                if (Hearable(Ludens[num].posX, Ludens[num].posY))
                    Engine.Sound.PlaySample(23);
            }

            if (Ludens[num].animNum == ANIM_SWITCH_ALL)
            {
                Ludens[num].attitude = 100;
                Ludens[num].setAnimation(ANIM_SWITCH_CHANGE, 1, Ludens[num].animDirection, false, false);

                for (i=0; i<MAX_LUDENS; i++)
                    if ((Ludens[i].active)&&(Ludens[i].style == SWITCH))
                        if (Ludens[i].target == Ludens[num].target)
                        {
                            Ludens[i].attitude = 100;
                            Ludens[i].setAnimation(ANIM_SWITCH_CHANGE, 1, Ludens[i].animDirection, false, false);
                        }

                Ludens[Ludens[num].target].setAnimation(ANIM_DOOR_OPEN, 1, LEFT, false, false);
            }

            if (Ludens[num].animNum == ANIM_SWITCH_ON)
            {
                Ludens[num].attitude = 0;
                Ludens[num].setAnimation(ANIM_SWITCH_CHANGE, 1, Ludens[num].animDirection, false, false);

                for (i=0; i<MAX_LUDENS; i++)
                    if ((Ludens[i].active)&&(Ludens[i].style == SWITCH))
                        if (Ludens[i].target == Ludens[num].target)
                        {
                            Ludens[i].attitude = 0;
                            Ludens[i].setAnimation(ANIM_SWITCH_CHANGE, 1, Ludens[i].animDirection, false, false);
                        }

                Ludens[Ludens[num].target].setAnimation(ANIM_DOOR_CLOSE, 1, LEFT, false, true);
            }

            if (Ludens[num].animNum == ANIM_SWITCH_CHANGE)
            {
                Ludens[num].interest = 0;
            }

        }
        else
        {
            if (Ludens[num].attitude == 0)
            {
                Ludens[num].setAnimation(ANIM_SWITCH_ALL, 1, LEFT, false, false);
            }
            if (Ludens[num].attitude == 100)
            {
                Ludens[num].setAnimation(ANIM_SWITCH_ON, 1, LEFT, false, false);
            }
        }
    } //SWITCH

    //SWITCH3 ZORTHDOOR
    if (Ludens[num].style == SWITCH3)
    {
        if (czorth > -1)
        {

            if (Ludens[czorth].target == num)
            {
                Ludens[czorth].target = Ludens[czorth].oldTarget;
                if (Ludens[czorth].target == -1)
                {
                    Ludens[czorth].interest = 0;
                }
                else
                {
                    Ludens[czorth].attitude = AI_FOLLOW;
                    Ludens[czorth].interest = ZORTH_INTEREST;
                }
            }

            //always open for zorth
            if ((Ludens[czorth].attitude != AI_PATROL)&&(Ludens[czorth].attitude != AI_NOTHING))
                Ludens[num].animNum = ANIM_SWITCH_ALL;

            if (Ludens[num].animNum == ANIM_SWITCH_ALL)
            {
                Ludens[num].attitude = 100;
                Ludens[num].setAnimation(ANIM_SWITCH_CHANGE, 1, Ludens[num].animDirection, false, false);

                for (i=0; i<MAX_LUDENS; i++)
                    if ((Ludens[i].active)&&(Ludens[i].style == SWITCH3))
                        if (Ludens[i].target == Ludens[num].target)
                        {
                            Ludens[i].attitude = 100;
                            Ludens[i].setAnimation(ANIM_SWITCH_CHANGE, 1, Ludens[i].animDirection, false, false);
                        }

                Ludens[Ludens[num].target].setAnimation(ANIM_DOOR_OPEN, 1, LEFT, false, false);
            }

            if (Ludens[num].animNum == ANIM_SWITCH_ON)
            {
                Ludens[num].attitude = 0;
                Ludens[num].setAnimation(ANIM_SWITCH_CHANGE, 1, Ludens[num].animDirection, false, false);

                for (i=0; i<MAX_LUDENS; i++)
                    if ((Ludens[i].active)&&(Ludens[i].style == SWITCH3))
                        if (Ludens[i].target == Ludens[num].target)
                        {
                            Ludens[i].attitude = 0;
                            Ludens[i].setAnimation(ANIM_SWITCH_CHANGE, 1, Ludens[i].animDirection, false, false);
                        }

                Ludens[Ludens[num].target].setAnimation(ANIM_DOOR_CLOSE, 1, LEFT, false, true);
            }

            if (Ludens[num].animNum == ANIM_SWITCH_CHANGE)
            {
                Ludens[num].interest = 0;
            }

        }
        else
        {
            if (Ludens[num].attitude == 0)
            {
                Ludens[num].setAnimation(ANIM_SWITCH_ALL, 1, LEFT, false, false);
            }
            if (Ludens[num].attitude == 100)
            {
                Ludens[num].setAnimation(ANIM_SWITCH_ON, 1, LEFT, false, false);
            }
        }
    } //SWITCH3 ZORTHDOOR


    // SWITCH 2 ELEVATOR
    if (Ludens[num].style == SWITCH2)
    {
        bool upper = (Ludens[Ludens[num].target].posY - ((TILE_HEIGHT+16) << FIX) > Ludens[num].posY);
        bool lower = Ludens[Ludens[num].target].posY - ((TILE_HEIGHT+3) << FIX) < Ludens[num].posY;

        if ((chero > -1)||(czorth > -1))
        {
            if ((czorth > -1)&&(czorth != myLudens))
            {
                if ((Ludens[num].animNum != ANIM_SWITCH_WRONG)&&(Ludens[czorth].attitude != AI_WAIT))
                {
                    if (lower)
                    {
                        Ludens[czorth].oldAttitude = Ludens[czorth].attitude;
                        Ludens[czorth].attitude = AI_WAIT;
                    }
                    // throw a grenade down the well :)
                    if (Ludens[czorth].target > -1)
                        if (upper)
                            if (Ludens[czorth].posY < Ludens[Ludens[czorth].target].posY)
                            {
                                //Ludens[czorth].setAnimation(ANIM_ZORTH_SHOOT, 2, Ludens[czorth].animDirection, true, false);
                                Ludens[czorth].state = FIRE_PRESSED;
                                Ludens[czorth].ammoType = ZORTH_AMMOGRENADE;
                            }
                }

                if (Ludens[num].animNum == ANIM_SWITCH_WRONG)
                {
                    if (Ludens[czorth].attitude == AI_WAIT)
                        Ludens[czorth].attitude = Ludens[czorth].oldAttitude;

                    //HACK
					if (Ludens[czorth].target > - 1)
					{
						Ludens[czorth].posX = Ludens[czorth].posX + Ludens[czorth].animDirection*ZORTH_MOVE;
						Ludens[czorth].velX = Ludens[czorth].velX + Ludens[czorth].animDirection*ZORTH_MOVE;
						Ludens[czorth].counter = 5;
					}
                }

                Ludens[czorth].interest++;
            }

            if (Ludens[num].animNum == ANIM_SWITCH_ALL)
            {
                Ludens[num].attitude = 100;
                Ludens[num].setAnimation(ANIM_SWITCH_CHANGE, 1, Ludens[num].animDirection, false, false);

            }

            if (Ludens[num].animNum == ANIM_SWITCH_ON)
            {
                Ludens[num].attitude = 0;
                Ludens[num].setAnimation(ANIM_SWITCH_CHANGE, 1, Ludens[num].animDirection, false, false);
            }

            if (Ludens[num].animNum == ANIM_SWITCH_CHANGE)
			if (Ludens[num].target > -1)
            {
                Ludens[num].interest = 0;
				Ludens[Ludens[num].target].oldAttitude = Ludens[Ludens[num].target].attitude;

                if (lower)
                    Ludens[Ludens[num].target].attitude = 101;
                else
                    if (upper)
                        Ludens[Ludens[num].target].attitude = 100;
                    else
                        Ludens[num].setAnimation(ANIM_SWITCH_WRONG, 1, LEFT, false, false);

				// if zorth on elevator don't move
				if (Ludens[Ludens[num].target].oldTarget > -1)
					if ( Ludens[Ludens[Ludens[num].target].oldTarget].style == ZORTH )
					{
                        Ludens[Ludens[num].target].attitude = Ludens[Ludens[num].target].oldAttitude;
                        Ludens[num].setAnimation(ANIM_SWITCH_CHANGE, 1, LEFT, false, false);
					}

            }

        }
        else
        {
			Ludens[num].setAnimation(ANIM_SWITCH_ON, 1, LEFT, false, false);
        }
    } //SWITCH2

    // ELEVATOR
    if (Ludens[num].style == ELEVATOR)
    {
        Ludens[num].attitude = 0;

        bool elev = false;
		Ludens[num].oldTarget = -1;

        for (int j=0; j < MAX_LUDENS; j++)
            if ((Ludens[j].active)&&(j != num)&&(LudensCollideOne(num, j) > -1))
            {
                LudensPush(j, num, 1);
                elev = Ludens[j].onGround = true;

                if ((Ludens[j].style == HERO)||(Ludens[j].style == HOVER))
                {
                    if ((Ludens[j].velX != 0)&&(Ludens[num].interest > 0))
                        Ludens[num].interest = ELEVATOR_WAITTIME;
                }

                if ((Ludens[j].style == ZORTH)||(Ludens[j].style == BIKE))
                {
                    if ((Ludens[j].velX != 0)&&(Ludens[num].interest > 0))
                        if (j==myLudens)
                            Ludens[num].interest = ELEVATOR_WAITTIME;
                        else
                            Ludens[num].interest = ELEVATOR_WAITTIME;


                    Ludens[j].counter = 0;
					Ludens[num].oldTarget = j;

                    // elevator always go were zorth wants to
                    if (Ludens[j].target > -1)
                        if (Ludens[Ludens[j].target].posArchiveY[Ludens[j].trackIndex] < Ludens[j].posY)
                            Ludens[num].target = 100;
                        else
                            Ludens[num].target = 101;
                }
            }


        if (elev)
        {
            Ludens[num].attitude = Ludens[num].target;
            Ludens[num].counter = 1;
        }
        else
		{
            Ludens[num].interest = -1;
		}

        if ((Ludens[num].attitude == 0)&&(Ludens[num].counter == 1))
        {
            if (Ludens[num].target == 101)
                Ludens[num].target = 100;
            else
                if (Ludens[num].target == 100)
                    Ludens[num].target = 101;

            Ludens[num].counter = 0;
        }

    } //ELEVATOR

    // ZORTH
    if (Ludens[num].style == ZORTH)
    {
        if (chero > -1)
            if (Ludens[chero].animNum != ANIM_HERO_DUCK) // CHANGE THIS, ZORTH CAN WALK THROUGH
            {
                Ludens[num].state = 0;
                if (Ludens[num].posX > Ludens[chero].posX)
                {
                    //Ludens[num].setAnimation(ANIM_ZORTH_SHOOT, 2, LEFT, true, false);
                    Ludens[num].state = FIRE_PRESSED;
                    Ludens[num].animDirection = LEFT;
                }
                else
                {
                    //Ludens[num].setAnimation(ANIM_ZORTH_SHOOT, 2, RIGHT, true, false);
                    Ludens[num].state = FIRE_PRESSED;
                    Ludens[num].animDirection = RIGHT;
                }
                LudensPush(chero, num, 0);
                Ludens[num].oldTarget = Ludens[num].target = chero;
                Ludens[num].interest = ZORTH_INTEREST;
            }

		if (cblock > -1)
		{
			Ludens[num].state = 0;
			if (Ludens[num].posX > Ludens[cblock].posX)
			{
				Ludens[num].state = FIRE_PRESSED;
				Ludens[num].animDirection = LEFT;
			}
			else
			{
				Ludens[num].state = FIRE_PRESSED;
				Ludens[num].animDirection = RIGHT;
			}
			LudensPush(num, cblock, 0, true);
			Ludens[num].oldTarget = Ludens[num].target = cblock;
			Ludens[num].interest = 10;
		}

		if (Ludens[num].target == -1)
		{

			if (cbunny3 > -1)
			{
				Ludens[num].state = 0;
				if (Ludens[num].posX > Ludens[cbunny3].posX)
				{
					Ludens[num].state = FIRE_PRESSED;
					Ludens[num].animDirection = LEFT;
				}
				else
				{
					Ludens[num].state = FIRE_PRESSED;
					Ludens[num].animDirection = RIGHT;
				}
				LudensPush(cbunny3, num, 0);
				Ludens[num].oldTarget = Ludens[num].target = cbunny3;
				Ludens[num].interest = ZORTH_INTEREST_MOMENT;
			}
		}

        if (cball > -1)
        {
            Ludens[num].kill();
        }

        if (czorth > -1)
        {
            //	LudensPush(czorth, num, 0);
        }

        if ((cswitch == -1)&&(cswitch2 == -1)&&(cswitch3 == -1))
        {
            // if didn't hit the switch find it
            if (Ludens[num].attitude == AI_WAIT)
            {
                Ludens[num].attitude = AI_FOLLOW;
                //Ludens[num].oldTarget = Ludens[num].target;
                //Ludens[num].target = ClosestStyleLudens(num, SWITCH, ELEVATOR, 0);
                //Ludens[num].interest = ZORTH_INTEREST2;
            }
        }

        if (cgrenade > -1)
        {
            if (Ludens[cgrenade].attitude == AI_NOTHING)
            {
                LudensPush(num, cgrenade, 0);
                Ludens[cgrenade].velX = Ludens[num].animDirection*abs(Ludens[cgrenade].velX);
                Ludens[cgrenade].velY = -abs(Ludens[cgrenade].velY);
            }
        }

        // Bikey
        if (cbike > -1)
            if (Ludens[num].anchor == -1)
            {
                LudensAttach(num, cbike);
                Ludens[num].anchorX = 0;//Ludens[num].radiusX/2;
                Ludens[num].anchorY = -2*Ludens[chover].radiusY + (3 << FIX);
                Ludens[cbike].target = num;
                Ludens[num].counter = BIKE_SHOOTFREQ-1;
            }

        /*if (crazor > -1)
        if (Ludens[crazor].attitude == AI_NOTHING)
        {
        LudensPush(num, crazor, 0);
        Ludens[crazor].kill();
        Ludens[num].ammoCount++;
        }*/

        if (cplazma > -1)
            if ((Ludens[cplazma].posX > Ludens[num].posX)&&(Ludens[cplazma].velX < 0)||
                    (Ludens[cplazma].posX < Ludens[num].posX)&&(Ludens[cplazma].velX > 0))
                if (Ludens[num].anchor == -1)
                {
                    if (num == myLudens)
                    {
                        Ludens[num].setAnimation(ANIM_ZORTH_DIE, 1, Ludens[num].animDirection, true, false);
                    }
                    else
                    {
                        Ludens[num].counter = 72;
                        Ludens[num].oldAttitude = Ludens[num].attitude;
                        Ludens[num].attitude = AI_BARRIER;
                        if (Hearable(Ludens[num].posX, Ludens[num].posY))
                            Engine.Sound.PlaySample(30);
                    }
                    Ludens[cplazma].setAnimation(ANIM_PLAZMA_BOOM, 1, Ludens[num].animDirection, true, false);
                    Ludens[cplazma].interest = Ludens[cplazma].velX = Ludens[cplazma].velY = 0;
                }

        if (cterminal > -1)
        {
			if (Ludens[num].target == cterminal)
			if (Ludens[cterminal].target > -1)
				if (Ludens[Ludens[cterminal].target].style == DOOR)
				{
					if (Ludens[Ludens[cterminal].target].animNum == ANIM_DOOR_OPEN)
					{
//						Ludens[cterminal].setAnimation(ANIM_TERMINAL_DESTROYED, 2, LEFT, false, true);
					}

					if (Ludens[cterminal].animNum != ANIM_TERMINAL_DESTROYED)
						Ludens[Ludens[cterminal].target].setAnimation(ANIM_DOOR_CLOSE, 1, LEFT, false, true);

					// when closed the door seek for old target or any elevator or zorth
					if (Ludens[num].oldTarget > -1)
						Ludens[num].target = Ludens[num].oldTarget;
					else
						Ludens[num].target = ClosestStyleLudens(num, STEP, STEP, 0);

					Ludens[num].attitude = AI_FOLLOW;
                    Ludens[num].interest = ZORTH_INTEREST;
				}
        }

    } // ZORTH

    // PLAZMA
    if (Ludens[num].style == PLAZMA)
    {} //PLAZMA

    // GRENADE
    if (Ludens[num].style == GRENADE)
    {} //GRENADE

    // RAZOR
    if (Ludens[num].style == RAZOR)
    {} //RAZOR


    // SPRING
    if (Ludens[num].style == SPRING)
    {
        Ludens[num].attitude = 0;

        bool elev = false;

        if (Ludens[num].onGround)
            for (int j=0; j < MAX_LUDENS; j++)
                if ((Ludens[j].active)&&(j != num)&&(LudensCollideOne(num, j) > -1))
                {
                    Ludens[j].velY = -Ludens[j].maxSpeed;
                    elev = true;

                    if ((Ludens[j].style == HERO)||(Ludens[j].style == SPRING))
                    {
                        if (Ludens[j].onGround)
                        {
                            LudensPush(num, j, 0, true);
                            Ludens[j].velY = 0;
                        }
                    }
                }

        if (elev)
        {
            Ludens[num].setAnimation(ANIM_SPRING_JUMP, 2, RIGHT, false, false);
        }
        else
            Ludens[num].setAnimation(ANIM_SPRING_NORMAL, 2, RIGHT, false, false);

    } //SPRING

    // VSPRING
    if (Ludens[num].style == VSPRING)
    {
        bool elev = false;

        Ludens[num].attitude = 0;

        for (int j=0; j < MAX_LUDENS; j++)
            if ((Ludens[j].active)&&(j != num)&&(LudensCollideOne(num, j) > -1))
            {
                if (Ludens[j].oldX > Ludens[num].posX)
                    Ludens[j].velX = Ludens[j].maxSpeed;
                else
                    Ludens[j].velX = -Ludens[j].maxSpeed;
                Ludens[j].velY = -Ludens[j].maxSpeed;
                elev = true;
            }

        if (elev)
        {
            Ludens[num].setAnimation(ANIM_VSPRING_JUMP, 2, RIGHT, false, false);
        }
        else
            Ludens[num].setAnimation(ANIM_VSPRING_NORMAL, 2, RIGHT, false, false);

    } //VSPRING

    // BLOCK
    if (Ludens[num].style == BLOCK)
        if (Ludens[num].animNum == ANIM_BLOCK_NORMAL)
        {
            for (int j=0; j < MAX_LUDENS; j++)
                if ((Ludens[j].active)&&(j != num)&&(Ludens[j].gravity != 0)&&(LudensCollideOne(num, j) > -1))
                {
                    if (Ludens[j].posY < Ludens[num].posY)
                    {
                        LudensPush(j, num, 1);
                        Ludens[j].onGround = true;
                    }
                    else
                    {
                        if (Ludens[j].gravity > (1 << FIX))
                            LudensPush(num, j, 0, false);
                        else
                            LudensPush(j, num, 0, true);

                        if (Ludens[j].style == BUNNY2)
                        {
                            Engine.Sound.PlaySample(28);
                            Ludens[j].kill();
                        }

                        if (Ludens[j].style == BALL)
                        {
                            Ludens[cball].velX = -Ludens[cball].velX;
                        }

                        if (Ludens[j].style == ZORTH)
                        {
							Ludens[j].state = 0;
							if (Ludens[j].posX > Ludens[num].posX)
							{
								Ludens[j].state = FIRE_PRESSED;
								Ludens[j].animDirection = LEFT;
							}
							else
							{
								Ludens[j].state = FIRE_PRESSED;
								Ludens[j].animDirection = RIGHT;
							}
							Ludens[j].oldTarget = Ludens[j].target = num;
							Ludens[j].interest = 15;
							LudensPush(j, num, 0, true);
                        }
                    }
                }

            /*	  if (chero > -1)
            {
            if (Ludens[chero].posY < Ludens[num].posY)
            LudensPush(chero, num, 1);
            else
            LudensPush(num, chero, 0, false);

            elev = Ludens[chero].onGround = true;
            }*/

            if (cball > -1)
            {
                //	Ludens[cball].velX = -Ludens[cball].velX;
            }
            if (cplazma > -1)
            {
                Ludens[cgrenade].interest = 1;
                Ludens[num].setAnimation(ANIM_BLOCK_CRACK, 2, RIGHT, true, false);
            }
            if (cgrenade > -1)
            {
                Ludens[cgrenade].velX = -Ludens[cgrenade].velX;
                Ludens[cgrenade].velY = -Ludens[cgrenade].velY;
                Ludens[cgrenade].interest--;
            }
            if (crazor > -1)
            {
                Ludens[crazor].velX = -Ludens[crazor].velX;
                Ludens[crazor].velY = -Ludens[crazor].velY;
                Ludens[crazor].interest--;
            }
            if (cbike > -1)
            {
                Ludens[num].setAnimation(ANIM_BLOCK_CRACK, 2, RIGHT, true, false);
            }
            if (ccrab > -1)
            {
                if (Ludens[ccrab].posX > Ludens[num].posX)
                {
                    Ludens[ccrab].posX = Ludens[ccrab].posX + abs(Ludens[num].velX);
                    Ludens[ccrab].velX = abs(Ludens[num].velX);
                }
                else
                {
                    Ludens[ccrab].posX = Ludens[ccrab].posX - abs(Ludens[num].velX);
                    Ludens[ccrab].velX = -abs(Ludens[num].velX);
                }

                Ludens[num].counter = 8;
                if (Ludens[ccrab].posX > Ludens[num].posX)
                    Ludens[num].attitude = 1;
                else
                    Ludens[num].attitude = 2;
            }

        } //BLOCK

    // PLATFORM
    if (Ludens[num].style == PLATFORM)
        if (Ludens[num].animNum == ANIM_PLATFORM_NORMAL)
        {
            for (int j=0; j < MAX_LUDENS; j++)
                if ((Ludens[j].active)&&(j != num)&&(LudensCollideOne(num, j) > -1))
                    if (Ludens[j].style != PLAZMA)
                    {
                        LudensPush(j, num, 1);
                        Ludens[j].onGround = true;
                    }

            if (cplazma > -1)
            {
                //Ludens[cgrenade].interest = 1;
                //Ludens[cplazma].onGround = false;
                Ludens[num].setAnimation(ANIM_BLOCK_CRACK, 2, RIGHT, true, false);
            }
            if (cgrenade > -1)
            {
                Ludens[cgrenade].velY = -Ludens[cgrenade].velY;
                Ludens[cgrenade].interest--;
            }
            if (crazor > -1)
            {
                Ludens[crazor].velY = -Ludens[crazor].velY;
                Ludens[crazor].interest--;
            }

        } //PLATFORM

    // HIDE
    if (Ludens[num].style == HIDE)
    {
        if (chero > -1)
        {
            if (Ludens[chero].animNum == ANIM_HERO_DUCK)
                Ludens[chero].attitude = AI_HIDDEN;
        }

    } //HIDE

    // BIKE
    if (Ludens[num].style == BIKE)
    {
        if (cbike > -1)
        {
            if (Ludens[cbike].posY < Ludens[num].posY)
                LudensPush(cbike, num, 1);
            else
                LudensPush(num, cbike, 0, true);
        }

    } //BIKE

    // DESTRUCT
    if (Ludens[num].style == DESTRUCT)
    {
        if ((chero > -1)||(czorth > -1)||(chover > -1)||(cbike > -1)||(cplazma > -1)||(cwater > -1))
        {
            Ludens[num].setAnimation(ANIM_DESTRUCT_DESTROY, 1, Ludens[num].animDirection, true, false);
            if (Ludens[num].target > -1)
                Ludens[Ludens[num].target].setAnimation(ANIM_DESTRUCT_DESTROY, 1, Ludens[Ludens[num].target].animDirection, true, false);
        }
    } //DESTRUCT


    // SECRET
    if (Ludens[num].style == SECRET)
    {
        // BEGIN SECRET
        if (chero > -1)
            if (Ludens[num].target > -1)
            {
                oldSecretX = Ludens[chero].posX;
                oldSecretY = Ludens[chero].posY;
                Ludens[chero].posX = Ludens[Ludens[num].target].posX;
                Ludens[chero].posY = Ludens[Ludens[num].target].posY;
                startSecret = true;
                ProcessCutScene(mapNum);
                if (cutScene)
                    StartCutScene();
                Ludens[num].kill();
            }

    } //SECRET


    // LINE
    if (Ludens[num].style == LINE)
        if (Ludens[num].target > -1)
        {
            Ludens[num].velX = Ludens[Ludens[num].target].posX - Ludens[num].posX;
            Ludens[num].velY = Ludens[Ludens[num].target].posY - Ludens[num].posY;

            int start;
            if (Ludens[myLudens].anchor > -1)
            {
                if (Ludens[Ludens[myLudens].anchor].style == HOVER)
                    return true;

                start = 5;
            }
            else
                start = 1;

            /*	for (int k = start; k < 10; k++)
            if ( (abs(Ludens[num].posX + (k-1)*Ludens[num].velX/k - Ludens[myLudens].posX) < Ludens[num].radiusX)
            && (abs(Ludens[num].posY + (k-1)*Ludens[num].velY/k - Ludens[myLudens].posY) < Ludens[num].radiusY))
            {
            if (Ludens[myLudens].anchor != num)
            {
            if (Ludens[myLudens].anchor == -1)
            {
            Ludens[myLudens].counter = 30;
            Ludens[myLudens].anchorX = (Ludens[myLudens].posX - Ludens[num].posX);
            Ludens[myLudens].anchorY = (Ludens[myLudens].posY - Ludens[num].posY);
            }
            else
            {
            Ludens[myLudens].anchorX = (Ludens[myLudens].posX - Ludens[num].posX);
            Ludens[myLudens].anchorY = (Ludens[myLudens].posY - Ludens[num].posY);
            }
            Ludens[myLudens].anchor = num;
            }
            break;
            }*/

            Ludens[num].velX = 0;
            Ludens[num].velY = 0;
        } //LINE


    // GUSTAV
    if (Ludens[num].style == GUSTAV)
    {
        if (chero > -1)
        {
            Ludens[chero].anchor = num;
            Ludens[chero].anchorX = -15 << FIX;
            Ludens[chero].anchorY = -5 << FIX;
            Ludens[chero].state = 0;
        }

    } //GUSTAV

    // WATER
    if (Ludens[num].style == WATER)
    {
        if (cwater > -1)
        {
            LudensPush(cwater, num, 1);
            Ludens[num].velX = -Ludens[num].velX;
        }

        if (chover > -1)
        {
            LudensPush(chover, num, 0);
            Ludens[chover].velX = Ludens[chover].velX + Ludens[num].velX;
        }

        if (chero > -1)
        {
            if (Ludens[chero].anchor > -1)
            {
                LudensPush(Ludens[chero].anchor, num, 0);
                Ludens[Ludens[chero].anchor].velY = Ludens[Ludens[chero].anchor].velY - 2*Ludens[Ludens[chero].anchor].gravity;
                Ludens[Ludens[chero].anchor].velX = Ludens[Ludens[chero].anchor].velX + Ludens[num].velX;
            }
        }
    } //WATER

    // HOVER
    if (Ludens[num].style == HOVER)
    {
        if (cline > -1)
        {
            if (Ludens[cline].target > -1)
            {
                if (Ludens[num].anchor != cline)
                {
                    if (Ludens[num].anchor == -1)
                    {
                        Ludens[num].anchorX = 0;
                        Ludens[num].anchorY = 0;
                    }
                    else
                    {
                        Ludens[num].anchorX = (Ludens[num].posX - Ludens[cline].posX);
                        Ludens[num].anchorY = (Ludens[num].posY - Ludens[cline].posY);
                    }
                    Ludens[num].anchor = cline;
                }
            }
            else
                if (Ludens[num].anchor > -1)
                    if (Ludens[Ludens[num].anchor].style == LINE)
                    {
                        Ludens[num].anchor = -1;
                        Ludens[num].velX = (Ludens[num].posX - Ludens[num].oldX);
                        Ludens[num].velY = (Ludens[num].posY - Ludens[num].oldY);
                    }
        }
    }  // HOVER

    // DUDE
    if (Ludens[num].style == DUDE)
    {
        if (chero > -1)
        {
            Dialog.SetDialog("Watch it!", DIALOG_RIDDLER_X, DIALOG_RIDDLER_Y, 30, sceneTimer);
            Dialog.count = 5;
        }
    }  // DUDE

    // STEP
    if (Ludens[num].style == STEP)
    {
        if ((chero > -1))
        {
            dialogStep++;
            sceneTimer = Dialog.lastTime + Dialog.duration;
            Ludens[num].kill();
        }
    } //STEP


    // DOOR
    if (Ludens[num].style == DOOR)
        if (Ludens[num].animNum == ANIM_DOOR_CLOSE)
        {
            if (clight > -1)
            {
                LudensPush(clight, num, 0);
            }

            if (chero > -1)
            {
                LudensPush(chero, num, 0);
            }

            if (ccrab > -1)
            {
                LudensPush(ccrab, num, 0);
            }

            if (cstrangler > -1)
            {
                LudensPush(cstrangler, num, 0);
            }

            if (ckodama > -1)
            {
                LudensPush(ckodama, num, 0);
            }

            if (cball > -1)
            {
                LudensPush(cball, num, 0);
            }

            if (cbunny > -1)
            {
                LudensPush(cbunny, num, 0);
            }

            if (cbunny2 > -1)
            {
                LudensPush(cbunny2, num, 0);
            }

            if (cbunny3 > -1)
            {
                LudensPush(cbunny3, num, 0);
            }

            if (ctracker > -1)
            {
                LudensPush(ctracker, num, 0);
            }

            if (czorth > -1)
            {
                LudensPush(czorth, num, 0);

                // search for door switch
                if (Ludens[czorth].target > -1)
                    if (Ludens[Ludens[czorth].target].style != SWITCH)
                        Ludens[czorth].oldTarget = Ludens[czorth].target;

                if (Ludens[czorth].posX > Ludens[num].posX)
                    Ludens[czorth].target = ClosestStyleLudens(czorth, SWITCH, SWITCH, RIGHT);
                else
                    Ludens[czorth].target = ClosestStyleLudens(czorth, SWITCH, SWITCH, LEFT);
                // search for door zorth switch
                if (Ludens[czorth].target > -1)
                    if (Ludens[Ludens[czorth].target].style != SWITCH3)
                        Ludens[czorth].oldTarget = Ludens[czorth].target;

                if (Ludens[czorth].posX > Ludens[num].posX)
                    Ludens[czorth].target = ClosestStyleLudens(czorth, SWITCH3, SWITCH3, RIGHT);
                else
                    Ludens[czorth].target = ClosestStyleLudens(czorth, SWITCH3, SWITCH3, LEFT);

                Ludens[czorth].attitude = AI_FOLLOW;
                Ludens[czorth].interest = ZORTH_INTEREST2;
            }

            if (cplazma > -1)
            {
                //	LudensPush(cplazma, num, 0);
                Ludens[cplazma].velX = -Ludens[cplazma].velX;
                Ludens[cplazma].velY = -Ludens[cplazma].velY;
            }

            if (cgrenade > -1)
            {
                //	LudensPush(cplazma, num, 0);
                Ludens[cgrenade].velX = -Ludens[cgrenade].velX;
                Ludens[cgrenade].velY = -Ludens[cgrenade].velY;
                Ludens[cgrenade].interest--;
            }

            if (crazor > -1)
            {
                Ludens[crazor].velX = -Ludens[crazor].velX;
                Ludens[crazor].velY = -Ludens[crazor].velY;
                Ludens[crazor].interest--;
            }

            if (chover > -1)
            {
                LudensPush(chover, num, 0);
            }

            if (cbike > -1)
            {
                AddLudens(GRENADE, Ludens[cbike].posX, Ludens[cbike].posY - (7 << FIX));
                if (Ludens[cbike].target > -1)
                    Ludens[Ludens[cbike].target].kill();
                Ludens[cbike].kill();
            }
        } //DOOR

    // MOLE
    if (Ludens[num].style == MOLE)
    {
        if ((czorth > -1))
        {
			AddPart(P_BLOOD, Ludens[czorth].posX, Ludens[czorth].posY);
			AddPart(P_BLOOD, Ludens[czorth].posX-(12 << FIX), Ludens[czorth].posY-(9 << FIX));
			AddPart(P_BLOOD, Ludens[czorth].posX-(5 << FIX), Ludens[czorth].posY-(11 << FIX));
			AddPart(P_BLOOD, Ludens[czorth].posX+(13 << FIX), Ludens[czorth].posY+(5 << FIX));
            Ludens[czorth].kill();			
        }
    } //MOLE

    // CHANGER
    if (Ludens[num].style == CHANGER)
    {
		//STRANGLER
		//	CRAB
		//	KODAMA
		//	LIGHT

        if (chero > -1)
        {
			Ludens[chero].kill();
			AddLudens(STRANGLER, Ludens[chero].posX + (3*TILE_WIDTH << FIX), Ludens[chero].posY, myLudens);
        }

        if (cstrangler > -1)
        {
			Ludens[cstrangler].kill();
			AddLudens(CRAB, Ludens[cstrangler].posX + (3*TILE_WIDTH << FIX), Ludens[cstrangler].posY, myLudens);
        }

        if (ccrab > -1)
        {
			Ludens[ccrab].kill();
			AddLudens(KODAMA, Ludens[ccrab].posX + (3*TILE_WIDTH << FIX), Ludens[ccrab].posY, myLudens);
        }

        if (ckodama > -1)
        {
			Ludens[ckodama].kill();
			AddLudens(LIGHT, Ludens[ckodama].posX + (3*TILE_WIDTH << FIX), Ludens[ckodama].posY, myLudens);
        }

        if (clight > -1)
        {
			Ludens[clight].kill();
			AddLudens(ZORTH, Ludens[clight].posX + (3*TILE_WIDTH << FIX), Ludens[clight].posY, myLudens);
        }

        if (czorth > -1)
        {
			Ludens[czorth].kill();
			AddLudens(HERO, Ludens[czorth].posX + (3*TILE_WIDTH << FIX), Ludens[czorth].posY, myLudens);
        }
    } //CHANGER


    // TERMINAL
  /*  if (Ludens[num].style == TERMINAL)
        if (Ludens[num].animNum == ANIM_TERMINAL_DEFAULT)
        {
            if (chero > -1)
            {
				usingTerminal = true;
				terminalNum = num;
			} else
			usingTerminal = false;

        }*/ //TERMINAL


    ////////////////// //  // /

    // collisions
    int collision[3];
    Ludens[num].onGround = false;
    Ludens[num].onWall = false;
    Ludens[num].onCeiling = false;
    int vw = 22;
    int vh = 22;

    // collision tiles HERO
    if (Ludens[num].style == HERO)
    {

        // feet
        if (Ludens[num].velY >= 0)
            for (i = 1; i < vh + 1; i++)
            {
                TestMapCollision(Ludens[num].posX, Ludens[num].posY + Ludens[num].radiusY + (Ludens[num].velY / vh) * i, collision);
                if (collision[0] == 1)
                {
                    Ludens[num].posY = collision[2] - Ludens[num].radiusY;
                    Ludens[num].velY = 0;
                    Ludens[num].onGround = true;
                    break;
                }

                if (collision[0] == 2)
                {
                    MyLudensDie();
                    if (Ludens[num].animTick == 0)
                    {
                        if ((Map.tileSet == VOLCANO_SET)||(Map.tileSet == BLACK_SET))
                            Engine.Sound.PlaySample(0);
                        else
                            Engine.Sound.PlaySample(32);
                    }
                    break;
                }
            }



        // head
        if (Ludens[num].velY < 0)
            for (i = 1; i < vh + 1; i++)
            {
                TestMapCollision(Ludens[num].posX, Ludens[num].posY - Ludens[num].radiusY + (Ludens[num].velY / vh) * i, collision);
                if (collision[0] == 1)
                {
                    Ludens[num].posY = collision[2] + (TILE_HEIGHT << FIX) + Ludens[num].radiusY;
                    Ludens[num].velY = 0;
                    break;
                }

                if (collision[0] == 2)
                {
                    MyLudensDie();
                    if (Ludens[num].animTick == 0)
                        if ((Map.tileSet == VOLCANO_SET)||(Map.tileSet == BLACK_SET))
                            Engine.Sound.PlaySample(0);
                        else
                            Engine.Sound.PlaySample(32);
                    break;
                }
            }

        // right
        for (i = 1; i < vw + 1; i++)
        {
            TestMapCollision(Ludens[num].posX + Ludens[num].radiusX + (Ludens[num].velX / vw) * i, Ludens[num].posY, collision);
            if (collision[0] == 1)
            {
                Ludens[num].posX = collision[1] - Ludens[num].radiusX;

                Ludens[num].velX = 0;

                //if (Engine.key_right)
                //if ((!Ludens[num].onGround)&&(Ludens[num].animNum != ANIM_HERO_JUMP))
                if (!Ludens[num].onGround)
                    Ludens[num].onWall = true;
                break;
            }
        }

        // left
        for (i = 1; i < vw + 1; i++)
        {
            TestMapCollision(Ludens[num].posX - Ludens[num].radiusX + (Ludens[num].velX / vw) * i, Ludens[num].posY, collision);
            if (collision[0] == 1)
            {
                Ludens[num].posX = collision[1] + (TILE_WIDTH << FIX) + Ludens[num].radiusX;

                Ludens[num].velX = 0;

                //	if (Engine.key_left)
                ///		if ((!Ludens[num].onGround)&&(Ludens[num].animNum != ANIM_HERO_JUMP))
                if (!Ludens[num].onGround)
                    Ludens[num].onWall = true;
                break;
            }
        }
    }
    else
        // collision tiles REST
        if ((Ludens[num].style != HEX)&&(Ludens[num].style != EXIT)&&(Ludens[num].style != LINE)&&(Ludens[num].style != HIDE)
                &&(Ludens[num].style != PLATFORM))
        {
            int resolveX;
            int resolveY;

            if (Ludens[num].style == WATER)
            {
                resolveX = 1;
                resolveY = 0;
            }
            else
                if (Ludens[num].style == BALL)
                {
                    resolveX = 1;
                    resolveY = 0;
                }
                else
                    if (Ludens[num].style == PLAZMA)
                    {
                        resolveX = 0;
                        resolveY = 0;
                        //	Ludens[num].interest = 0;
                        //if (Ludens[num].animNum == ANIM_PLAZMA_BOOM)
                        //	return false;
                    }
                    else
                        if (Ludens[num].style == GRENADE)
                        {
                            resolveX = 1;
                            resolveY = 1;
                        }
                        else
                            if (Ludens[num].style == RAZOR)
                            {
                                resolveX = 1;
                                resolveY = 1;
                            }
                            else
                                if (Ludens[num].style == BIKE)
                                {
                                    if (abs(Ludens[num].velX) > BIKE_CRASHSPEED )
                                    {
                                        resolveX = 3;
                                    }
                                    else
                                    {
                                        resolveX = 1;
                                    }
                                    resolveY = 0;
                                }
                                else
                                {
                                    resolveX = 0;
                                    resolveY = 0;
                                }

            // feet
            for (i = 1; i < vh + 1; i++)
            {
                TestMapCollision(Ludens[num].posX, Ludens[num].posY + Ludens[num].radiusY + (Ludens[num].velY / vh) * i, collision);
                if (collision[0] == 1)
                {
                    Ludens[num].posY = collision[2] - Ludens[num].radiusY;

                    if (resolveY == 2)
                    {
                        DeleteTile((collision[1] >> FIX) / TILE_WIDTH, (collision[2] >> FIX) / TILE_HEIGHT);
                        Ludens[num].velY = 3*Ludens[num].velY/4;
                    }
                    if (resolveY == 1)
                        Ludens[num].velY = -Ludens[num].velY;
                    if (resolveY == 0)
                        Ludens[num].velY = 0;

                    Ludens[num].onGround = true;
                    break;
                }
            }
            // head
            for (i = 1; i < vh + 1; i++)
            {
                TestMapCollision(Ludens[num].posX, Ludens[num].posY - Ludens[num].radiusY + (Ludens[num].velY / vh) * i, collision);
                if (collision[0] == 1)
                {
                    Ludens[num].posY = collision[2] + (TILE_HEIGHT << FIX) + Ludens[num].radiusY;

                    if (resolveY == 2)
                    {
                        DeleteTile((collision[1] >> FIX) / TILE_WIDTH, (collision[2] >> FIX) / TILE_HEIGHT);
                        Ludens[num].velY = 3*Ludens[num].velY/4;
                    }
                    if (resolveY == 1)
                        Ludens[num].velY = -Ludens[num].velY;
                    if (resolveY == 0)
                        Ludens[num].velY = 0;

                    Ludens[num].onCeiling = true;
                    break;
                }
                if ((Ludens[num].style != LIGHT)&&(Ludens[num].style != WATER)&&(Ludens[num].style != DESTRUCT)&&(Ludens[num].style != MOLE))
                    if (collision[0] == 2)
                    {
                        Ludens[num].active = false;

                        if ((Ludens[num].style == KODAMA)&&(Ludens[num].anchor == -1))
                            break;

                        if (Hearable(Ludens[num].posX, Ludens[num].posY))
                            if ((Map.tileSet == VOLCANO_SET)||(Map.tileSet == BLACK_SET))
                                Engine.Sound.PlaySample(0);
                            else
                                Engine.Sound.PlaySample(32);
                        break;
                    }
            }
            // right
            for (i = 1; i < vw + 1; i++)
            {
                TestMapCollision(Ludens[num].posX + Ludens[num].radiusX + (Ludens[num].velX / vw) * i, Ludens[num].posY, collision);
                if (collision[0] == 1)
                {
                    Ludens[num].posX = collision[1] - Ludens[num].radiusX;

                    if (resolveX == 3)
                    {
                        AddLudens(GRENADE, Ludens[num].posX, Ludens[num].posY - (7 << FIX));
                        if (Ludens[num].target > -1)
                            Ludens[Ludens[num].target].kill();
                        Ludens[num].kill();
                    }
                    if (resolveX == 2)
                    {
                        DeleteTile((collision[1] >> FIX) / TILE_WIDTH, (collision[2] >> FIX) / TILE_HEIGHT);
                        Ludens[num].velX = 3*Ludens[num].velX/4;
                    }
                    if (resolveX == 1)
                        Ludens[num].velX = -Ludens[num].velX;
                    if (resolveX == 0)
                        Ludens[num].velX = 0;

                    Ludens[num].onWall = true;
                    break;
                }
            }
            // left
            for (i = 1; i < vw + 1; i++)
            {
                TestMapCollision(Ludens[num].posX - Ludens[num].radiusX + (Ludens[num].velX / vw) * i, Ludens[num].posY, collision);
                if (collision[0] == 1)
                {
                    Ludens[num].posX = collision[1] + (TILE_WIDTH << FIX) + Ludens[num].radiusX;

                    if (resolveX == 3)
                    {
                        AddLudens(GRENADE, Ludens[num].posX, Ludens[num].posY - (7 << FIX));
                        if (Ludens[num].target > -1)
                            Ludens[Ludens[num].target].kill();
                        Ludens[num].kill();
                    }
                    if (resolveX == 2)
                    {
                        DeleteTile((collision[1] >> FIX) / TILE_WIDTH, (collision[2] >> FIX) / TILE_HEIGHT);
                        Ludens[num].velX = 3*Ludens[num].velX/4;
                    }
                    if (resolveX == 1)
                        Ludens[num].velX = -Ludens[num].velX;
                    if (resolveX == 0)
                        Ludens[num].velX = 0;

                    Ludens[num].onWall = true;
                }
            }
        }

    return false;
}
