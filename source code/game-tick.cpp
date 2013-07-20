#include "preheader.h"
#include "game.h"


void CGame::LudensTick(int num)
{
    int distX, distY;

    // edit mode only //
    if (editMode)
    {
        // hero (cursor)
        if (num == myLudens)
            EditTick(num);
        return;
    }
    // // // // // // //

    if (num == myLudens)
    {
        if (!miniMap)
        {
            if ((!showMenu)&&(!cutScene))
            {
                if (Engine.key_left)
                    Ludens[num].state = Ludens[num].state | LEFT_PRESSED;
                if (Engine.key_right)
                    Ludens[num].state = Ludens[num].state | RIGHT_PRESSED;
                if ((Engine.key_jump)||(Engine.key_up))
                    Ludens[num].state = Ludens[num].state | UP_PRESSED;
                if ((Engine.key_duck)||(Engine.key_down))
                    Ludens[num].state = Ludens[num].state | DOWN_PRESSED;
                if (Engine.key_fire)
                    Ludens[num].state = Ludens[num].state | GAME_A_PRESSED;
            }
            if (shakeCounter<0)
                viewX = viewY = 0;

        }
        else
        {
            if (Engine.key_left)
                viewX = -VIEW_MAX << FIX;
            else
                if (Engine.key_right)
                    viewX = VIEW_MAX << FIX;
                else
                    viewX = 0;

            if (Engine.key_up||Engine.key_jump)
                viewY = -VIEW_MAX << FIX;
            else
                if (Engine.key_down)
                    viewY = VIEW_MAX << FIX;
                else
                    viewY = 0;
        }
    }
    else
        //if (!cutScene)
        if ((((Ludens[num].style != HERO)&&(Ludens[num].style != GUSTAV))||(!cutScene))&&(myLudens != num))
            LudensAI(num);

    // pos archive control
    int k = 32;
    distX = abs(Ludens[num].posArchiveX[Ludens[num].posArchiveIndex] - Ludens[num].posX);
    distY = abs(Ludens[num].posArchiveY[Ludens[num].posArchiveIndex] - Ludens[num].posY);
    if ((distX > (k << FIX))||(distY > (k << FIX)))
    {
        Ludens[num].posArchiveIndex++;
        if (Ludens[num].posArchiveIndex > MAX_POSARCHIVE-1)
            Ludens[num].posArchiveIndex = 0;
        //Ludens[num].posArchiveX[Ludens[num].posArchiveIndex] = ((((Ludens[num].posX >> FIX) + k/2)/k)*k) << FIX;
        //Ludens[num].posArchiveY[Ludens[num].posArchiveIndex] = ((((Ludens[num].posY >> FIX) - k/2)/k)*k) << FIX;
        Ludens[num].posArchiveX[Ludens[num].posArchiveIndex] = Ludens[num].posX;
        Ludens[num].posArchiveY[Ludens[num].posArchiveIndex] = Ludens[num].posY;
    }

    Ludens[num].oldX = Ludens[num].posX;
    Ludens[num].oldY = Ludens[num].posY;
	if (Ludens[num].onGround)
		Ludens[num].beenOnGround = Ludens[num].onGround;

    // control //
    switch (Ludens[num].style)
    {
    case HERO:
        if ((Ludens[num].onGround)||(Ludens[num].animNum == ANIM_HERO_UMB)||(Ludens[num].animNum == ANIM_HERO_UMBBACK))
            Ludens[num].velX = 0;
        else
        {
            Ludens[num].velX = (1)*Ludens[num].velX/(2);
            if (( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)||( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED))
            {
                if (Ludens[num].velX > HERO_MAXAIRMOVE)
                    Ludens[num].velX = HERO_MAXAIRMOVE;
                if (Ludens[num].velX < -HERO_MAXAIRMOVE)
                    Ludens[num].velX = -HERO_MAXAIRMOVE;
            }
        }

        // dead
        if (Ludens[num].animNum == ANIM_HERO_DIE)
        {
            //if (Ludens[num].animTick == 5)
            //  Engine.Sound.PlaySample(3);


            if (Ludens[num].animTick > 3)
                if ((Ludens[num].state != 0)||(mainTickCounter % 48 == 0))
                {
                    if ((Map.tileSet == OUBLIETTE_SET)||(Map.tileSet == END_SET))
                        NextMap();
                    else
                        LoadTileMap(filePlusDir(mapFileName));
                    return;
                }
            break;

        }

		if (usingTerminal)
		{
			if ( ((Ludens[num].state & DOWN_PRESSED) == DOWN_PRESSED)||( (Ludens[num].state & UP_PRESSED) == UP_PRESSED) )
				Ludens[num].state = 0;
		} else
		{
		}

        // RIDING on...
        if (Ludens[num].anchor > -1)
        {
            Ludens[num].transferState = Ludens[num].state;

            // back to the future 2
            if (Ludens[Ludens[num].anchor].style == HOVER)
            {

                /*   if ( (Ludens[num].state & GAME_A_PRESSED) == GAME_A_PRESSED)
                {
                Ludens[num].anchor = -1;
                Ludens[num].velX = 0;
                }
                else*/
                if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
                {
                    if ( (Ludens[num].state & DOWN_PRESSED) == DOWN_PRESSED)
                        Ludens[num].setAnimation(ANIM_HERO_DUCK, 1, RIGHT, false, false);
                    else
                        if (Ludens[Ludens[num].anchor].onGround)
                            Ludens[num].setAnimation(ANIM_HERO_HOVER, 1, RIGHT, false, false);
                        else
                            Ludens[num].setAnimation(ANIM_HERO_FALL, 1, RIGHT, false, false);
                    Ludens[num].animDirection = RIGHT;
                }
                else
                    if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
                    {
                        if ( (Ludens[num].state & DOWN_PRESSED) == DOWN_PRESSED)
                            Ludens[num].setAnimation(ANIM_HERO_DUCK, 1, LEFT, false, false);
                        else
                            if (Ludens[Ludens[num].anchor].onGround)
                                Ludens[num].setAnimation(ANIM_HERO_HOVER, 1, LEFT, false, false);
                            else
                                Ludens[num].setAnimation(ANIM_HERO_FALL, 1, LEFT, false, false);
                        Ludens[num].animDirection = LEFT;
                    }
                    else
                        if ( (Ludens[num].state & DOWN_PRESSED) == DOWN_PRESSED)
                        {
                            Ludens[num].setAnimation(ANIM_HERO_DUCK, 1, Ludens[num].animDirection, false, false);
                        }
                        else
                            if (Ludens[Ludens[num].anchor].onGround)
                                Ludens[num].setAnimation(ANIM_HERO_HOVER, 1, Ludens[num].animDirection, false, false);
                            else
                                Ludens[num].setAnimation(ANIM_HERO_FALL, 1, Ludens[num].animDirection, false, false);

            }

            // Ride the linetning
            if (Ludens[Ludens[num].anchor].style == LINE)
            {
                Ludens[num].setAnimation(ANIM_HERO_RIDE, 1, Ludens[num].animDirection, false, true);

                int x1, x2, y1, y2, m, k;
                x1 = Ludens[Ludens[num].anchor].posX;
                x2 = Ludens[Ludens[Ludens[num].anchor].target].posX;
                y1 = Ludens[Ludens[num].anchor].posY;
                y2 = Ludens[Ludens[Ludens[num].anchor].target].posY;


                //m = 64;
                m = 45;

                Ludens[num].velX = -(x1 - x2) / m;
                Ludens[num].velY = -(y1 - y2) / m;

                Ludens[num].anchorX = Ludens[num].anchorX + Ludens[num].velX;
                Ludens[num].anchorY = Ludens[num].anchorY + Ludens[num].velY;

                if ((Ludens[num].state & UP_PRESSED) != UP_PRESSED)
                {
                    Ludens[num].attitude = 0;
                }

                if (Ludens[num].attitude == 0)
                    if ((Ludens[num].state & UP_PRESSED) == UP_PRESSED)
                    {
                        Ludens[num].anchor = -1;
                        Ludens[num].attitude = 100;
                        Ludens[num].moveSprite(0, -HERO_MAXSPEED);
                    }

            }

            break;
        } // end ride :(

        // for hiding
        if (((Ludens[num].state & DOWN_PRESSED) != DOWN_PRESSED) )
            Ludens[num].attitude = 0;


        if (Ludens[num].animNum == ANIM_HERO_HIT)
            Ludens[num].radiusX = HERO_RADIUSHITX;
        else
            Ludens[num].radiusX = HERO_RADIUSX;

        if (Ludens[num].animNum == ANIM_HERO_DUCK)
            Ludens[num].radiusY = HERO_RADIUSDUCKY;
        else
            Ludens[num].radiusY = HERO_RADIUSY;


        if ( ( (Ludens[num].state & GAME_A_PRESSED) == GAME_A_PRESSED) && (Ludens[num].onGround))
        {
            if (Ludens[num].animNum != ANIM_HERO_CLOSE_UMB)
            {
                Ludens[num].setAnimation(ANIM_HERO_HIT, 1, Ludens[num].animDirection, true, false);
                if (Ludens[num].animTick == 0)
                    Engine.Sound.PlaySample(9);
            }
        }
        else
            if ( ( (Ludens[num].state & GAME_A_PRESSED) == GAME_A_PRESSED) && (!Ludens[num].onGround))
            {
                if ( (Ludens[num].animNum == ANIM_HERO_FALL) || (Ludens[num].animNum == ANIM_HERO_AIR_JUMP) || (Ludens[num].animNum == ANIM_HERO_JUMP))
                {
                    Ludens[num].setAnimation(ANIM_HERO_OPEN_UMB, 1, Ludens[num].animDirection, false, false);
                    if (Ludens[num].animTick == 0)
                        Engine.Sound.PlaySample(10);
                }

                if ((Ludens[num].animNum == ANIM_HERO_UMB)||(Ludens[num].animNum == ANIM_HERO_UMBBACK))
                    Ludens[num].setAnimation(ANIM_HERO_CLOSE_UMB, 1, Ludens[num].animDirection, false, false);
            }
            else
                if (((Ludens[num].animNum == ANIM_HERO_OPEN_UMB)||(Ludens[num].animNum == ANIM_HERO_UMB)||(Ludens[num].animNum == ANIM_HERO_UMBBACK)) && (!Ludens[num].onGround))
                {
                    //if (Ludens[num].animTick > 3)
                    //	Ludens[num].setAnimation(ANIM_HERO_UMB, 1, Ludens[num].animDirection, false, true);

                    if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
                    {
                        //						Ludens[num].animDirection = RIGHT;
                        Ludens[num].moveSprite(HERO_FLOATMOVE, 0);
                        if (Ludens[num].animTick > 3)
                            if (Ludens[num].animDirection == RIGHT)
                                Ludens[num].setAnimation(ANIM_HERO_UMB, 1, Ludens[num].animDirection, false, true);
                            else
                                Ludens[num].setAnimation(ANIM_HERO_UMBBACK, 1, Ludens[num].animDirection, false, true);
                    }
                    else
                        if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
                        {

                            //							Ludens[num].animDirection = LEFT;
                            Ludens[num].moveSprite( -HERO_FLOATMOVE, 0);
                            if (Ludens[num].animTick > 3)
                                if (Ludens[num].animDirection == LEFT)
                                    Ludens[num].setAnimation(ANIM_HERO_UMB, 1, Ludens[num].animDirection, false, true);
                                else
                                    Ludens[num].setAnimation(ANIM_HERO_UMBBACK, 1, Ludens[num].animDirection, false, true);
                        }
                        else
                            if ((Ludens[num].animNum == ANIM_HERO_UMB)||(Ludens[num].animNum == ANIM_HERO_UMBBACK))
                                Ludens[num].animTick = 7;

                }
                else
                    if ( ( (Ludens[num].state & UP_PRESSED) == UP_PRESSED)  && (Ludens[num].onGround))
                    {
                        if ( (Ludens[num].animNum == ANIM_HERO_STAND) || (Ludens[num].animNum == ANIM_HERO_RUN)|| (Ludens[num].animNum == ANIM_HERO_IDLE))
                            Ludens[num].setAnimation(ANIM_HERO_JUMP, 1, Ludens[num].animDirection, false, false);

                        if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
                        {
                            Ludens[num].animDirection = RIGHT;
                            Ludens[num].moveSprite(HERO_MOVE, 0);
                        }
                        else
                            if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
                            {
                                Ludens[num].animDirection = LEFT;
                                Ludens[num].moveSprite( -HERO_MOVE, 0);
                            }
                    }
                    else
                        if (((Ludens[num].state & DOWN_PRESSED) == DOWN_PRESSED) )
                        {
                            Ludens[num].setAnimation(ANIM_HERO_DUCK, 1, Ludens[num].animDirection, false, false);
                        }
                        else
                            if ( ( (Ludens[num].state & UP_PRESSED) == UP_PRESSED) && (!Ludens[num].onGround) && (!Ludens[num].onWall)
                                    && (Ludens[num].animNum != ANIM_HERO_WALL_CLIMB) && (Ludens[num].animNum != ANIM_HERO_WALL_JUMP) && (Ludens[num].animNum != ANIM_HERO_STAND) )
                            {
                                if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
                                {
                                    Ludens[num].animDirection = RIGHT;
                                    Ludens[num].moveSprite(HERO_MOVE, 0);
                                }
                                else
                                    if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
                                    {
                                        Ludens[num].animDirection = LEFT;
                                        Ludens[num].moveSprite( -HERO_MOVE, 0);
                                    }
                            }
                            else
                                if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
                                {
                                    if ( (Ludens[num].onWall) && (!Ludens[num].onGround))
                                    {
                                        if (Ludens[num].animDirection == LEFT)
                                            Ludens[num].setAnimation(ANIM_HERO_WALL_JUMP, 1, LEFT, true, false);

                                        Ludens[num].setAnimation(ANIM_HERO_WALL_CLIMB, 1, RIGHT, false, false);
                                        Ludens[num].moveSprite(HERO_MOVE, -HERO_WALL);

                                        if (Ludens[num].animTick > 0)
                                            Ludens[num].velY = Ludens[num].velY / 2;
                                    }
                                    else
                                    {
                                        if (Ludens[num].onGround)
                                            Ludens[num].setAnimation(ANIM_HERO_RUN, 1, RIGHT, false, true);
                                        else
                                            Ludens[num].setAnimation(ANIM_HERO_AIR_JUMP, 1, RIGHT, false, false);

                                        if (Ludens[num].animNum == ANIM_HERO_RUN)
                                            Ludens[num].moveSprite(HERO_MOVE, 0);

                                        if ( (Ludens[num].animNum == ANIM_HERO_JUMP) || (Ludens[num].animNum == ANIM_HERO_AIR_JUMP))
                                        {
                                            Ludens[num].moveSprite(HERO_AIRMOVE, 0);
                                        }

                                        Ludens[num].animDirection = RIGHT;
                                    }

                                }
                                else
                                    if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
                                    {
                                        if ( (Ludens[num].onWall) && (!Ludens[num].onGround))
                                        {
                                            if (Ludens[num].animDirection == RIGHT)
                                                Ludens[num].setAnimation(ANIM_HERO_WALL_JUMP, 1, RIGHT, true, false);

                                            Ludens[num].setAnimation(ANIM_HERO_WALL_CLIMB, 1, LEFT, false, false);
                                            Ludens[num].moveSprite( -HERO_MOVE, -HERO_WALL);

                                            if (Ludens[num].animTick > 0)
                                                Ludens[num].velY = Ludens[num].velY / 2;
                                        }
                                        else
                                        {
                                            if (Ludens[num].onGround)
                                                Ludens[num].setAnimation(ANIM_HERO_RUN, 1, LEFT, false, true);
                                            else
                                                Ludens[num].setAnimation(ANIM_HERO_AIR_JUMP, 1, LEFT, false, false);

                                            if (Ludens[num].animNum == ANIM_HERO_RUN)
                                                Ludens[num].moveSprite( -HERO_MOVE, 0);

                                            if ( (Ludens[num].animNum == ANIM_HERO_JUMP) || (Ludens[num].animNum == ANIM_HERO_AIR_JUMP))
                                                Ludens[num].moveSprite( -HERO_AIRMOVE, 0);

                                            Ludens[num].animDirection = LEFT;
                                        }

                                    }
                                    else
                                    {
                                        if (((Ludens[num].animNum == ANIM_HERO_OPEN_UMB)||(Ludens[num].animNum == ANIM_HERO_UMB)||(Ludens[num].animNum == ANIM_HERO_UMBBACK)||(Ludens[num].animNum == ANIM_HERO_CLOSE_UMB))&&(Ludens[num].onGround)&&(Ludens[num].animTick<2))
                                        {
                                            Ludens[num].setAnimation(ANIM_HERO_CLOSE_UMB, 1, Ludens[num].animDirection, false, false);
                                        }
                                        else
                                        {
                                            if (Ludens[num].onGround)
                                            {
                                                if (Ludens[num].animNum == ANIM_HERO_FALL)
                                                {
                                                    AddPart(P_DUST, Ludens[num].posX + (-1 << FIX), Ludens[num].posY + Ludens[num].radiusY + (-2 << FIX));
                                                    AddPart(P_DUST, Ludens[num].posX + (-8 << FIX), Ludens[num].posY + Ludens[num].radiusY + (-2 << FIX));
                                                }

                                                if ((Ludens[num].animNum != ANIM_HERO_IDLE)||((Ludens[num].animNum == ANIM_HERO_IDLE)&&(Ludens[num].animTick > 8)))
                                                    Ludens[num].setAnimation(ANIM_HERO_STAND, ANIM_HERO_STAND_SPEED, Ludens[num].animDirection, false, true);
                                            }
                                            else
                                                if ((Ludens[num].animNum != ANIM_HERO_OPEN_UMB)&&(Ludens[num].animNum != ANIM_HERO_UMB)&&(Ludens[num].animNum != ANIM_HERO_UMBBACK)&&(Ludens[num].animNum != ANIM_HERO_WALL_CLIMB))
                                                    Ludens[num].setAnimation(ANIM_HERO_FALL, 1, Ludens[num].animDirection, false, false);
                                        }
                                    }

        if ( (Ludens[num].onGround) && ( ( ( (Ludens[num].animNum == ANIM_HERO_JUMP) | (Ludens[num].animNum == ANIM_HERO_AIR_JUMP)) && (Ludens[num].animTick > 1)) || ((Ludens[num].animNum == ANIM_HERO_HIT) && (!Ludens[num].onGround)) || ( (Ludens[num].animNum == ANIM_HERO_FALL) | (Ludens[num].animNum == ANIM_HERO_WALL_CLIMB))))
        {
            Ludens[num].setAnimation(ANIM_HERO_STAND, ANIM_HERO_STAND_SPEED, Ludens[num].animDirection, false, true);
        }

        if (Ludens[num].animNum == ANIM_HERO_WALL_CLIMB)
        {
            if (((Ludens[num].state & LEFT_PRESSED) != LEFT_PRESSED)&&((Ludens[num].state & RIGHT_PRESSED) != RIGHT_PRESSED))
                Ludens[num].moveSprite(Ludens[num].animDirection*HERO_MOVE, 0);
            if (!Ludens[num].onWall)
                Ludens[num].setAnimation(ANIM_HERO_FALL, 1, Ludens[num].animDirection, false, false);
        }

        if ( (Ludens[num].animNum == ANIM_HERO_JUMP) && (Ludens[num].animTick > 0) && (Ludens[num].animTick < 3))
            Ludens[num].moveSprite(0, -HERO_JUMP);

        if ( (Ludens[num].animNum == ANIM_HERO_WALL_JUMP))
            if (Ludens[num].animDirection == LEFT)
                Ludens[num].moveSprite( -HERO_WALLBACK, -HERO_WALLJUMP);
            else
                Ludens[num].moveSprite(HERO_WALLBACK, -HERO_WALLJUMP);

        if ((Ludens[num].animNum == ANIM_HERO_UMB)||(Ludens[num].animNum == ANIM_HERO_OPEN_UMB)||(Ludens[num].animNum == ANIM_HERO_UMBBACK)||((Ludens[num].animNum == ANIM_HERO_CLOSE_UMB)&&(Ludens[num].animTick < 3)))
        {
            Ludens[num].velY = Ludens[num].velY/2;
            Ludens[num].moveSprite(0, -HERO_FLOAT);
        }

        if (Ludens[num].animNum == ANIM_HERO_RAIN)
        {
            if ((Ludens[num].animTick == 5)&&(Ludens[num].animSpeedTick == Ludens[num].animSpeed-1))
            {
                Ludens[num].animTick = 4;
                Ludens[num].animSpeedTick = 0;
            }
        }


        if (Ludens[num].animNum == ANIM_HERO_STAND)
        {
            Ludens[num].idleCounter--;
            if (Ludens[num].idleCounter < 1)
            {
                Ludens[num].idleCounter = LUDENS_IDLE_TIME2 + Engine.random(48);
                Ludens[num].setAnimation(ANIM_HERO_IDLE, ANIM_HERO_IDLE_SPEED, Ludens[num].animDirection, false, false);
            }
        }
        else
            if (Ludens[num].animNum != ANIM_HERO_IDLE)
                Ludens[num].idleCounter = LUDENS_IDLE_TIME;

        break;

    case LIGHT: //LIGHT

        if (Ludens[num].attitude == AI_NOTHING)
        {
            Ludens[num].velX = Ludens[num].velX >> 1;
            Ludens[num].velY = Ludens[num].velY >> 1;

            if (Ludens[num].posX < Ludens[Ludens[num].target].posX - (2 << FIX))
                Ludens[num].velX = Ludens[num].velX + LIGHT_MOVE;
            else
                Ludens[num].velX = Ludens[num].velX - LIGHT_MOVE;

            if (Ludens[num].posY < Ludens[Ludens[num].target].posY + (2 << FIX))
                Ludens[num].velY = Ludens[num].velY + LIGHT_MOVE;
            else
                Ludens[num].velY = Ludens[num].velY - LIGHT_MOVE;

            Ludens[num].state = 0;

            Ludens[num].setAnimation(ANIM_LIGHT_FRIEND, 2, RIGHT, false, true);
            break;
        }

        if (Ludens[num].state == 0)
        {
            Ludens[num].velX = Ludens[num].velX / 2;
            Ludens[num].velY = Ludens[num].velY / 2;
            Ludens[num].setAnimation(ANIM_LIGHT_STEADY, 1, RIGHT, false, true);
        }
        else
        {
            if (Ludens[num].attitude == AI_RUNAWAY)
                Ludens[num].setAnimation(ANIM_LIGHT_GLOW, 1, RIGHT, false, true);

            if (Ludens[num].attitude == AI_FOLLOW)
            { //friendly
                Ludens[num].setAnimation(ANIM_LIGHT_FRIEND, 1, RIGHT, false, true);

                distX = abs(Ludens[num].posX - Ludens[Ludens[num].target].posX);
                distY = abs(Ludens[num].posY - Ludens[Ludens[num].target].posY);

                if ((distX < (TILE_WIDTH*10 << FIX))&&(distY < (TILE_HEIGHT*10 << FIX)))
                    Ludens[num].maxSpeed = (abs(Ludens[num].posX - Ludens[Ludens[num].target].posX) + abs(Ludens[num].posY - Ludens[Ludens[num].target].posY)) / 2;
                else
                    Ludens[num].maxSpeed = LIGHT_MAXSPEED;

                //if ( (Ludens[num].velX != LIGHT_MAXSPEED) && (Ludens[num].velX != -LIGHT_MAXSPEED))

                if (Ludens[num].maxSpeed < LIGHT_MAXSPEED)
                    Ludens[num].maxSpeed = LIGHT_MAXSPEED;
            }
        }

        if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
        {
            Ludens[num].moveSprite(LIGHT_MOVE, 0);
        }
        if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
        {
            Ludens[num].moveSprite( -LIGHT_MOVE, 0);
        }
        if ( (Ludens[num].state & UP_PRESSED) == UP_PRESSED)
        {
            Ludens[num].moveSprite(0, -LIGHT_MOVE);
        }
        if ( (Ludens[num].state & DOWN_PRESSED) == DOWN_PRESSED)
        {
            Ludens[num].moveSprite(0, LIGHT_MOVE);
        }

        break;

    case TRACKER: //TRACKER
        if (Ludens[num].animNum == ANIM_TRACKER_DEAD)
        {
            Ludens[num].setAnimation(ANIM_TRACKER_DEAD, 2, Ludens[num].animDirection, false, true);
            Ludens[num].velX = Ludens[num].velX/2;
            Ludens[num].velY = Ludens[num].velY/2;
            break;
        }

        if (Ludens[num].state == 0)
        {
            Ludens[num].setAnimation(ANIM_TRACKER_STEADY, 1, Ludens[num].animDirection, false, true);
            Ludens[num].velX = Ludens[num].velY = 0;
        }

        if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_TRACKER_TRACK, 1, RIGHT, false, true);
            Ludens[num].moveSprite(TRACKER_MOVE, 0);
            Ludens[num].animDirection = RIGHT;
        }
        if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_TRACKER_TRACK, 1, LEFT, false, true);
            Ludens[num].moveSprite( -TRACKER_MOVE, 0);
            Ludens[num].animDirection = LEFT;
        }
        if ( (Ludens[num].state & UP_PRESSED) == UP_PRESSED)
        {
            Ludens[num].moveSprite(0, -TRACKER_MOVE);
        }
        if ( (Ludens[num].state & DOWN_PRESSED) == DOWN_PRESSED)
        {
            Ludens[num].moveSprite(0, TRACKER_MOVE);
        }

        //	  Ludens[num].maxSpeed = (abs(Ludens[num].posX - Ludens[Ludens[num].target].posArchiveX[Ludens[num].trackIndex]) + abs(Ludens[num].posY - Ludens[Ludens[num].target].posArchiveY[Ludens[num].trackIndex])) / 12;
        if (Ludens[num].target > -1)
        {
            if (Ludens[num].maxSpeed != TRACKER_MAXSPEED/2)
            {
                distX = abs(Ludens[num].posX - Ludens[Ludens[num].target].posX);
                distY = abs(Ludens[num].posY - Ludens[Ludens[num].target].posY);
                if ((distX < (TILE_WIDTH*10 << FIX))&&(distY < (TILE_HEIGHT*10 << FIX)))
                    Ludens[num].maxSpeed = (distX + distY) / 12;
                else
                    Ludens[num].maxSpeed = TRACKER_MAXSPEED;

                if (Ludens[num].maxSpeed < TRACKER_MAXSPEED)
                    Ludens[num].maxSpeed = TRACKER_MAXSPEED;
            }

            if (Ludens[Ludens[num].target].anchor > -1)
                Ludens[num].maxSpeed = TRACKER_MAXSPEED;

        }

        break;

    case CRAB: //CRAB
        if (Ludens[num].onGround)
            Ludens[num].velX = 0;
        else
            Ludens[num].state = 0;

        int speed;
        if (Ludens[num].target > -1)
            speed = CRAB_MOVECHASE;
        else
            speed = CRAB_MOVE;

        if ( (Ludens[num].animNum == ANIM_CRAB_ATTACK) && ( (Ludens[num].animTick == 3)
                || (Ludens[num].animTick == 6)))
        {
            if (Hearable(Ludens[num].posX, Ludens[num].posY))
                Engine.Sound.PlaySample(8);
        }

        Ludens[num].animDirection = RIGHT;

        if (Ludens[num].state == 0)
        {
            Ludens[num].setAnimation(ANIM_CRAB_STAND, 1, Ludens[num].animDirection, false, true);
        }

        if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_CRAB_WALK, 1, Ludens[num].animDirection, false, true);
            Ludens[num].moveSprite(speed, 0);
        }
        if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_CRAB_WALK, 1, Ludens[num].animDirection, false, true);
            Ludens[num].moveSprite( -speed, 0);
        }
        if ( (Ludens[num].state & UP_PRESSED) == UP_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_CRAB_DANCE, 1, Ludens[num].animDirection, false, true);
        }
        if ( (Ludens[num].state & DOWN_PRESSED) == DOWN_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_CRAB_ATTACK, 1, Ludens[num].animDirection, true, false);
        }

        break;

    case BUNNY: //BUNNY
        Ludens[num].animDirection = RIGHT;
        Ludens[num].velX = 0;

        if (Ludens[num].velY > 0)
            Ludens[num].setAnimation(ANIM_BUNNY_FALL, 1, Ludens[num].animDirection, false, false);
        else
            if (Ludens[num].velY < 0)
                Ludens[num].setAnimation(ANIM_BUNNY_JUMP, 1, Ludens[num].animDirection, false, false);
            else
                Ludens[num].setAnimation(ANIM_BUNNY_STAND, 1, Ludens[num].animDirection, false, false);

        if (Ludens[num].counter>0)
        {
            Ludens[num].moveSprite(0, -BUNNY_JUMP);
            Ludens[num].counter--;
        }

        if (((Ludens[num].state & UP_PRESSED) == UP_PRESSED)  && (Ludens[num].onGround))
            Ludens[num].counter = 4;

        Ludens[num].state = 0;
        break;

    case BUNNY2: //STATIC BUNNY
        Ludens[num].animDirection = RIGHT;
        Ludens[num].velX = 0;

        if (Ludens[num].velY > 0)
            Ludens[num].setAnimation(ANIM_BUNNY_FALL, 1, Ludens[num].animDirection, false, false);
        else
            if (Ludens[num].velY < 0)
                Ludens[num].setAnimation(ANIM_BUNNY_JUMP, 1, Ludens[num].animDirection, false, false);
            else
                Ludens[num].setAnimation(ANIM_BUNNY_STAND, 1, Ludens[num].animDirection, false, false);

        if (Ludens[num].counter>0)
        {
            Ludens[num].moveSprite(0, -BUNNY_JUMP);
            Ludens[num].counter--;
        }

        if (((Ludens[num].state & UP_PRESSED) == UP_PRESSED)  && (Ludens[num].onGround))
            Ludens[num].counter = 3;

        Ludens[num].state = 0;
        break;

    case BUNNY3: //SIDEWAYS BUNNY
        if (Ludens[num].onGround)
            Ludens[num].velX = 0;

        if (Ludens[num].velY > 0)
            Ludens[num].setAnimation(ANIM_BUNNY_FALL, 1, Ludens[num].animDirection, false, false);
        else
            if (Ludens[num].velY < 0)
                Ludens[num].setAnimation(ANIM_BUNNY_JUMP, 1, Ludens[num].animDirection, false, false);
            else
                Ludens[num].setAnimation(ANIM_BUNNY_STAND, 1, Ludens[num].animDirection, false, false);

        /*      if (Ludens[num].counter>0)
        {
        Ludens[num].moveSprite(0, -BUNNY_JUMP);

        if (Ludens[num].animDirection == LEFT)
        Ludens[num].moveSprite(-BUNNY_MOVE, 0);
        else
        Ludens[num].moveSprite(BUNNY_MOVE, 0);

        Ludens[num].counter--;
        }

        if (Ludens[num].onWall)
        {
        //  Ludens[num].animDirection = -Ludens[num].animDirection;
        if (Ludens[Ludens[num].target].posX < Ludens[num].posX)
        Ludens[num].animDirection = LEFT;
        else
        Ludens[num].animDirection = RIGHT;

        Ludens[num].counter = 2;
        }


        if (((Ludens[num].state & UP_PRESSED) == UP_PRESSED)  && (Ludens[num].onGround))
        Ludens[num].counter = 4;*/

        Ludens[num].state = 0;
        break;

    case EXIT: //EXIT
        int hc, lc;
        hc = lc = 0;

        if (Ludens[num].attitude == 1)
        {
            Ludens[num].setAnimation(ANIM_EXIT_OPEN, 1, RIGHT, false, false);
            break;
        }


        for (int i=0; i < MAX_LUDENS; i++)
            if ((Ludens[i].active)&&(Ludens[i].style == HEX))
            {
                lc++;
                if (Ludens[i].attitude == AI_NOTHING)
                    hc++;
            }

        if (lc == hc)
        {
            Ludens[num].setAnimation(ANIM_EXIT_OPEN, 1, RIGHT, false, false);
            Ludens[num].attitude = AI_NOTHING;
        }

        break;

    case KODAMA: //KODAMA
        if (Ludens[num].onGround)
        {
            Ludens[num].velX = 0;
        }
        else
            Ludens[num].state = 0;

        // kodama gives
        if (Ludens[num].animNum == ANIM_KODAMA_GIVE)
        {
            Ludens[num].attitude = AI_GIVE;
            if (Ludens[num].animTick > 3)
            {
                AddLudens(LIGHT, Ludens[num].posX, Ludens[num].posY);
                Ludens[Ludens[num].anchor].attitude = 1;
                Ludens[num].kill();
            }
            break;
        }

        if (Ludens[num].anchor > -1)
        {
            Ludens[num].setAnimation(ANIM_KODAMA_GRAB, 1, Ludens[num].animDirection, false, false);
            break;
        }

        if (Ludens[num].state == 0)
        {
            if (Ludens[num].attitude == AI_HIDDEN)
            {
                Ludens[num].setAnimation(ANIM_KODAMA_FADE, 1, Ludens[num].animDirection, false, false);
                if (Engine.random(30) == 0)
                {
                    Ludens[num].setAnimation(ANIM_KODAMA_FADEBLINK, 1, Ludens[num].animDirection, false, false);
                }
            }
            else
            {
                if (Ludens[num].animNum != ANIM_KODAMA_LOOK)
                    Ludens[num].setAnimation(ANIM_KODAMA_STAND, 1, Ludens[num].animDirection, false, false);

                if (Engine.random(40) == 0)
                {
                    Ludens[num].setAnimation(ANIM_KODAMA_BLINK, 1, Ludens[num].animDirection, false, false);
                }
                if (Engine.random(50) == 0)
                    if (Ludens[num].animNum != ANIM_KODAMA_BLINK)
                    {
                        Ludens[num].setAnimation(ANIM_KODAMA_LOOK, 1, Ludens[num].animDirection, false, false);
                    }
            }

        }

        if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_KODAMA_RUN, 1, RIGHT, false, true);
            Ludens[num].moveSprite(KODAMA_MOVE, 0);
            Ludens[num].animDirection = RIGHT;
        }
        if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_KODAMA_RUN, 1, LEFT, false, true);
            Ludens[num].moveSprite( -KODAMA_MOVE, 0);
            Ludens[num].animDirection = LEFT;
        }

        if (!Ludens[num].onGround)
            Ludens[num].setAnimation(ANIM_KODAMA_FALL, 1, Ludens[num].animDirection, false, false);

        break;

    case HUT: //HUT
        if (Ludens[num].attitude == 1)
            Ludens[num].setAnimation(ANIM_HUT_OCCUPIED, 2, RIGHT, false, true);
        break;

    case STRANGLER: //STRANGLER
        if (Ludens[num].onGround)
            Ludens[num].velX = 0;
        else
            Ludens[num].state = 0;

        if (Ludens[num].animNum == ANIM_STRANGLER_ATTACK)
        {
            Ludens[num].state = 0;

            if (Ludens[num].animTick == 1)
            {
                if (Hearable(Ludens[num].posX, Ludens[num].posY))
                    Engine.Sound.PlaySample(20);
            }

            if (Ludens[num].animTick == 8)
                ShakeCamera(2, 3);
        }

        if (Ludens[num].state == 0)
        {
            if (((Ludens[num].animNum != ANIM_STRANGLER_BLINK)||(Ludens[num].animTick > 10))&&(Ludens[num].animNum != ANIM_STRANGLER_ATTACK))
                Ludens[num].setAnimation(ANIM_STRANGLER_STAND, 2, Ludens[num].animDirection, false, true);

            if (Ludens[num].animNum == ANIM_STRANGLER_STAND)
            {
                if (Ludens[num].animTick > 13)
                    if (Engine.random(6) == 0)
                    {
                        Ludens[num].setAnimation(ANIM_STRANGLER_BLINK, 2, Ludens[num].animDirection, false, false);
                    }
            }
        }

        if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_STRANGLER_WALK, 1, RIGHT, false, true);
            Ludens[num].moveSprite(STRANGLER_MOVE, 0);
            Ludens[num].animDirection = RIGHT;
        }
        if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_STRANGLER_WALK, 1, LEFT, false, true);
            Ludens[num].moveSprite( -STRANGLER_MOVE, 0);
            Ludens[num].animDirection = LEFT;
        }

        break;

    case BALL: //BALL
        if (!Ludens[num].onGround)
            Ludens[num].state = 0;

        if ((Ludens[num].state == 0)&&(Ludens[num].velX == 0)&&(!Ludens[num].onGround))
            Ludens[num].setAnimation(ANIM_BALL_STOP, 1, Ludens[num].animDirection, false, true);

        if ( (abs(Ludens[num].velX) > (BALL_MAXSPEED2)) || ((!Ludens[num].onGround)) )
            Ludens[num].velX = Ludens[num].velX/2;

        if (Ludens[num].velX == 0)
        {
            Ludens[num].velX = BALL_MOVE;
        }

        if (( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED) || (Ludens[num].velX > 0))
        {
            Ludens[num].setAnimation(ANIM_BALL_ROLL, 1, RIGHT, false, true);
            Ludens[num].moveSprite(BALL_MOVE, 0);
            Ludens[num].animDirection = RIGHT;
        }
        if (( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED) || (Ludens[num].velX < 0))
        {
            Ludens[num].setAnimation(ANIM_BALL_ROLL, 1, LEFT, false, true);
            Ludens[num].moveSprite( -BALL_MOVE, 0);
            Ludens[num].animDirection = LEFT;
        }
        break;

    case ELEVATOR: //ELEVATOR
        if (Ludens[num].interest > -1)
            Ludens[num].interest--;

        if ((Ludens[num].state == 0)||(Ludens[num].interest > 0))
        {
            Ludens[num].setAnimation(ANIM_ELEVATOR_STOP, 1, Ludens[num].animDirection, false, true);
            Ludens[num].velX = Ludens[num].velY = 0;
            Ludens[num].state = 0;
        }

        if ((Ludens[num].state & UP_PRESSED) == UP_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_ELEVATOR_GO, 1, RIGHT, false, true);
            Ludens[num].moveSprite(0, -ELEVATOR_MOVE);
        }

        if ((Ludens[num].state & DOWN_PRESSED) == DOWN_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_ELEVATOR_GO, 1, RIGHT, false, true);
            Ludens[num].moveSprite(0, ELEVATOR_MOVE);
        }
        break;

    case ZORTH: //ZORTH
        if (Ludens[num].counter > -1) // for flying counter // for shooting
            Ludens[num].counter--;

        // player zorth
        if (num == myLudens)
        {
            Ludens[num].target = -1;
            Ludens[num].attitude = AI_PATROL;
        }

        // barrier - hit
        if ((Ludens[num].attitude == AI_BARRIER))
        {
            Ludens[num].animBlock = false;
            Ludens[num].setAnimation(ANIM_ZORTH_BARRIER, 1, Ludens[num].animDirection, false, true);
            if (Ludens[num].counter == 1)
            {
                if (Ludens[num].oldAttitude != AI_BARRIER)
                    Ludens[num].attitude = Ludens[num].oldAttitude;
                else
                    Ludens[num].attitude = AI_PATROL;

                if (Hearable(Ludens[num].posX, Ludens[num].posY))
                    //	if (Ludens[num].target > -1)
                    //		Engine.Sound.PlaySample(17);
                    //	else
                    Engine.Sound.PlaySample(17);
            }

            Ludens[num].velX = Ludens[num].velY = 0;
            break;
        }

        // dead
        if (Ludens[num].animNum == ANIM_ZORTH_DIE)
        {
            if (Ludens[num].animTick > 4)
            {
                if (num == myLudens)
                {
                    if (Ludens[num].state != 0)
                    {
                        LoadTileMap(filePlusDir(mapFileName));
                        return;
                    }
                }
                else
                    Ludens[num].kill();

                return;
            }
            break;
        }

        // RIDING on...
        if (Ludens[num].anchor > -1)
        {
            // star wars bike
            if (Ludens[Ludens[num].anchor].style == BIKE)
            {
                Ludens[num].animNum = ANIM_ZORTH_ONBIKE;
                Ludens[num].animTick = 0;

                if (Ludens[num].target == -1)
                    Ludens[num].state = 0;
                else
                    if (mainTickCounter % 5 == 0)
                    {
                        if (Hearable(Ludens[num].posX, Ludens[num].posY))
                            Engine.Sound.PlaySample(22);
                    }

                Ludens[num].animDirection = Ludens[Ludens[num].anchor].animDirection;

                distY = abs(Ludens[num].posY - Ludens[Ludens[num].target].posY);

                //if (distY < (2*TILE_HEIGHT))
                if (Ludens[num].counter < 1)
                    //if (Ludens[Ludens[num].target].posY > Ludens[num].posY)
                    if (Ludens[num].onGround)
                        Ludens[num].counter = BIKE_SHOOTFREQ;

                if ((Ludens[num].target > -1)&&(Ludens[num].counter == BIKE_SHOOTFREQ))
                {
                    k = AddLudens(PLAZMA, Ludens[num].posX, Ludens[num].posY - (12 << FIX));
                    if (k > -1)
                    {
                        Ludens[k].animDirection = Ludens[Ludens[num].anchor].animDirection;
                        Ludens[k].velX = Ludens[num].animDirection*PLAZMA_MOVE + Ludens[Ludens[num].anchor].velX;
                        Ludens[k].interest = 33;
                        Ludens[k].maxSpeed = PLAZMA_MAXSPEED2;
                        Ludens[num].counter--;
                        Ludens[Ludens[num].anchor].setAnimation(ANIM_BIKE_ZORTHFIRE, 1, Ludens[Ludens[num].anchor].animDirection, false, false);
                    }
                }

            }

            Ludens[num].transferState = Ludens[num].state;

            break;
        }
        // end ride :(


        if ((Ludens[num].attitude == AI_WAIT)||(Ludens[num].attitude == AI_BACKUP))
        {
            Ludens[num].state = 0;
            Ludens[num].setAnimation(ANIM_ZORTH_STAND, 2, Ludens[num].animDirection, false, false);
        }

        if ((Ludens[num].oldAttitude == AI_WAIT)||(Ludens[num].oldAttitude == AI_BACKUP))
            Ludens[num].oldAttitude = AI_FOLLOW;

        if (Ludens[num].animBlock)
        {
            Ludens[num].counter = Ludens[num].state = Ludens[num].velX = Ludens[num].velY = 0;
            //break;
        }

        if (( (Ludens[num].state & FIRE_PRESSED) == FIRE_PRESSED)||( (Ludens[num].state & GAME_A_PRESSED) == GAME_A_PRESSED))
            if (((Ludens[num].animNum == ANIM_ZORTH_SHOOT)&&(Ludens[num].animTick < 9))
                    ||(Ludens[num].animNum == ANIM_ZORTH_AIM))
            {
                Ludens[num].state = 0;
                Ludens[num].velX = Ludens[num].velX/3;

                // SHHOOOT HAHA!
                if ((Ludens[num].animTick == 5)&&(Ludens[num].animSpeedTick == 0))
                {
                    int k;

                    if (Ludens[num].ammoType == ZORTH_AMMOPLAZMA)
                    {
                        k = AddLudens(PLAZMA, Ludens[num].posX, Ludens[num].posY - (7 << FIX));
                        if (k > -1)
                        {
                            Ludens[k].animDirection = Ludens[num].animDirection;
                            Ludens[k].velX = Ludens[num].animDirection*PLAZMA_MOVE;
                            Ludens[k].interest = 33;
                            Ludens[k].velY = Ludens[num].aimY;
                            Ludens[num].setAnimation(ANIM_ZORTH_AIM, 2, Ludens[num].animDirection, false, true);
							if (Hearable(Ludens[num].posX, Ludens[num].posY))
								Engine.Sound.PlaySample(15);
                        }
                    }
                    if ((Ludens[num].ammoType == ZORTH_AMMOSLOWGRENADE)||(Ludens[num].ammoType == ZORTH_AMMOGRENADE))
                    {
                        k = AddLudens(GRENADE, Ludens[num].posX, Ludens[num].posY - (7 << FIX));
                        if (k > -1)
                        {
                            Ludens[k].animDirection = Ludens[num].animDirection;
                            Ludens[k].velX = Ludens[num].animDirection*GRENADE_MOVE;
                            if (Ludens[num].ammoType == ZORTH_AMMOSLOWGRENADE)
                                Ludens[k].velX = Ludens[k].velX/2;
                            Ludens[k].interest = GRENADE_LIFE;
                        }
                        Ludens[num].setAnimation(ANIM_ZORTH_RELOAD, 2, Ludens[num].animDirection, true, false);
						if (Hearable(Ludens[num].posX, Ludens[num].posY))
							Engine.Sound.PlaySample(13);
                    }
                    if (Ludens[num].ammoType == ZORTH_AMMORAZOR)
                        if (Ludens[num].ammoCount > 0)
                        {
                            k = AddLudens(RAZOR, Ludens[num].posX, Ludens[num].posY - (7 << FIX));
                            if (k > -1)
                            {
                                Ludens[k].animDirection = Ludens[num].animDirection;
                                Ludens[k].velX = Ludens[num].animDirection*RAZOR_MOVE;
                                Ludens[k].interest = RAZOR_LIFE;
                                Ludens[k].owner = num;
                                Ludens[num].ammoCount--;
                            }
                            Ludens[num].setAnimation(ANIM_ZORTH_RELOAD, 2, Ludens[num].animDirection, true, false);
							if (Hearable(Ludens[num].posX, Ludens[num].posY))
								Engine.Sound.PlaySample(14);
                        }

                    if (Engine.random(3) > 0)
                        Ludens[num].ammoType = ZORTH_AMMOPLAZMA;
                    else
                    {
                        if (Ludens[num].target > -1)
                            if (abs(Ludens[num].posX - Ludens[Ludens[num].target].posX) > ZORTH_GRENADESIGHTX*19)
                                Ludens[num].ammoType = ZORTH_AMMOGRENADE;
                    }

                    /*if (Ludens[num].ammoType == ZORTH_AMMOPLAZMA)
                    Ludens[num].ammoType = ZORTH_AMMOGRENADE;
                    else
                    Ludens[num].ammoType = ZORTH_AMMOPLAZMA;*/

					if (Hearable(Ludens[num].posX, Ludens[num].posY))
						ShakeCamera(1, 3);
                }
                break;
            }

        if (Ludens[num].onGround) // GROUND
        {
            Ludens[num].velX = Ludens[num].velX/3;

            if (Ludens[num].attitude == AI_PATROL)
                Ludens[num].velX = Ludens[num].velX/2;

            if (Ludens[num].state == 0)
            {
                if (((Ludens[num].animNum != ANIM_ZORTH_BREATH)||(Ludens[num].animTick > 13))&&
                        (Ludens[num].animNum != ANIM_ZORTH_SHOOT)&&(Ludens[num].animNum != ANIM_ZORTH_AIM)
                        &&(Ludens[num].animNum != ANIM_ZORTH_RELOAD))
                    Ludens[num].setAnimation(ANIM_ZORTH_STAND, 3, Ludens[num].animDirection, false, true);

                if (Ludens[num].animNum == ANIM_ZORTH_STAND)
                {
                    if (Ludens[num].animTick > 8)
                        if (Engine.random(7) == 0)
                        {
                            Ludens[num].setAnimation(ANIM_ZORTH_BREATH, 2, Ludens[num].animDirection, false, false);
                        }
                }
            }

            if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
            {
                if (Ludens[num].animNum == ANIM_ZORTH_WALK)
                {
                    Ludens[num].moveSprite(ZORTH_MOVE, 0);
                    if ( (Ludens[num].animTick == 4)||(Ludens[num].animTick == 5)||(Ludens[num].animTick == 9)||(Ludens[num].animTick == 10)  )
                        Ludens[num].moveSprite(1*ZORTH_MOVE, 0);
                }
                Ludens[num].setAnimation(ANIM_ZORTH_WALK, 2, RIGHT, false, true);
                Ludens[num].animDirection = RIGHT;
            }
            if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
            {
                if (Ludens[num].animNum == ANIM_ZORTH_WALK)
                {
                    Ludens[num].moveSprite( -ZORTH_MOVE, 0);
                    if ( (Ludens[num].animTick == 4)||(Ludens[num].animTick == 5)||(Ludens[num].animTick == 9)||(Ludens[num].animTick == 10)  )
                        Ludens[num].moveSprite( -1*ZORTH_MOVE, 0);
                }
                Ludens[num].setAnimation(ANIM_ZORTH_WALK, 2, LEFT, false, true);
                Ludens[num].animDirection = LEFT;
            }
            //		if (( (Ludens[num].state & FIRE_PRESSED) == FIRE_PRESSED)||( (Ludens[num].state & GAME_A_PRESSED) == GAME_A_PRESSED))

            if (( (Ludens[num].state & FIRE_PRESSED) == FIRE_PRESSED)||( (Ludens[num].state & GAME_A_PRESSED) == GAME_A_PRESSED))
            {
                if ((Ludens[num].animNum != ANIM_ZORTH_AIM)&&(Ludens[num].animNum != ANIM_ZORTH_RELOAD))
                    Ludens[num].setAnimation(ANIM_ZORTH_SHOOT, 2, Ludens[num].animDirection, false, false);
            }
            else
            {
                if ((Ludens[num].animNum == ANIM_ZORTH_SHOOT)||(Ludens[num].animNum == ANIM_ZORTH_AIM)||(Ludens[num].animNum == ANIM_ZORTH_RELOAD))
                    Ludens[num].setAnimation(ANIM_ZORTH_STAND, 2, Ludens[num].animDirection, false, false);
            }


            if ( (Ludens[num].state & UP_PRESSED) == UP_PRESSED)
            {
                Ludens[num].counter = 3;
            }
        }
        else // FLY
        {
            Ludens[num].velX = 4*Ludens[num].velX/5;

            if (Ludens[num].state == 0)
            {
                Ludens[num].setAnimation(ANIM_ZORTH_FLY, 3, Ludens[num].animDirection, false, true);
            }

            if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
            {
                Ludens[num].setAnimation(ANIM_ZORTH_FLY, 2, RIGHT, false, true);
                Ludens[num].moveSprite(ZORTH_MOVE, 0);
                Ludens[num].animDirection = RIGHT;
            }
            if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
            {
                Ludens[num].setAnimation(ANIM_ZORTH_FLY, 2, LEFT, false, true);
                Ludens[num].moveSprite( -ZORTH_MOVE, 0);
                Ludens[num].animDirection = LEFT;
            }
            if ( (Ludens[num].state & UP_PRESSED) == UP_PRESSED)
            {
                Ludens[num].counter = 3;
            }

            // float
            if (Ludens[num].velY > ZORTH_MAXFALLSPEED)
            {
                Ludens[num].counter = 6;
            }
        } // end FLY

        // bump head stupid!
        if (Ludens[num].onCeiling)
        {
            Ludens[num].counter = 0;
            Ludens[num].moveSprite( 0, ZORTH_FLYMOVE);
            Ludens[num].interest = Ludens[num].interest/2;
            Ludens[num].trackIndex--;
            if (Ludens[num].trackIndex < 0)
                Ludens[num].trackIndex = MAX_POSARCHIVE - 1;
        }

        // fly away
        if (Ludens[num].counter > 0)
        {
            if ((Ludens[num].onGround)&&(Ludens[num].velX < 0))
                Ludens[num].moveSprite( 0, -ZORTH_FLYMOVE);

            AddPart(P_JETS, Ludens[num].posX - Ludens[num].animDirection*Ludens[num].radiusX/2, Ludens[num].posY + Ludens[num].radiusY);
            Ludens[num].moveSprite( 0, -ZORTH_FLYMOVE);

			if (Hearable(Ludens[num].posX, Ludens[num].posY))
            if (mainTickCounter % 5 == 0)
            {
                Engine.Sound.PlaySample(21);
            }
        }

        break;

    case PLAZMA: //PLAZMA
        if ((Ludens[num].onGround)||(Ludens[num].onWall))//||(Ludens[num].interest == 0))
        {
            Ludens[num].setAnimation(ANIM_PLAZMA_BOOM, 1, Ludens[num].animDirection, true, false);
        }
        if (Ludens[num].interest > 0)
            Ludens[num].interest--;

        if (Ludens[num].animNum == ANIM_PLAZMA_BOOM)
        {
            if (Ludens[num].animTick == 1)
                Engine.Sound.PlaySample(19);

            if (Ludens[num].animTick > 5)
            {
                int tx = (Ludens[num].posX  >> FIX) / TILE_WIDTH;
                int ty = (Ludens[num].posY >> FIX) / TILE_HEIGHT;

                //if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH-1) && (ty < MAP_HEIGHT-1))
                //	DeleteTile(tx, ty);
                Ludens[num].kill();
            }
            break;
        }

        if (Ludens[num].velX > 0)
        {
            Ludens[num].animDirection = RIGHT;
        }
        else
        {
            Ludens[num].animDirection = LEFT;
        }

        if (Ludens[num].animDirection == RIGHT)
        {
            Ludens[num].moveSprite(PLAZMA_MOVE, 0);
        }
        if (Ludens[num].animDirection == LEFT)
        {
            Ludens[num].moveSprite(-PLAZMA_MOVE, 0);
        }

        break;

    case GRENADE: //GRENADE
        if ((Ludens[num].onGround)||(Ludens[num].onWall)||(Ludens[num].onCeiling))
        {
            Ludens[num].interest--;
            Ludens[num].velX = 5*Ludens[num].velX/6;
            Ludens[num].velY = 2*Ludens[num].velY/3;
			if (Hearable(Ludens[num].posX, Ludens[num].posY))
				Engine.Sound.PlaySample(24);
        }

        if ((Ludens[num].interest > GRENADE_ARMEDTIME-1)&&(Ludens[num].interest < GRENADE_LIFE-1))
            Ludens[num].attitude = AI_NOTHING;
        else
            Ludens[num].attitude = AI_ARMED;

        if (Ludens[num].interest < GRENADE_ARMEDTIME)
        {
            Ludens[num].setAnimation(ANIM_GRENADE_READY, 1, Ludens[num].animDirection, false, false);
        }
        else
        {
            Ludens[num].setAnimation(ANIM_GRENADE_UNARMED, 1, Ludens[num].animDirection, false, false);
        }

        if (Ludens[num].interest < 1)
        {
            Ludens[num].setAnimation(ANIM_GRENADE_BOOM, 1, Ludens[num].animDirection, true, false);
			if (Hearable(Ludens[num].posX, Ludens[num].posY))
	            Engine.Sound.PlaySample(12);
        }

        if (Ludens[num].animNum == ANIM_GRENADE_BOOM)
        {
            if (Ludens[num].animTick > 0)
            {
                int tx = (Ludens[num].posX  >> FIX) / TILE_WIDTH;
                int ty = (Ludens[num].posY >> FIX) / TILE_HEIGHT;

                if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH-1) && (ty < MAP_HEIGHT-1))
                    DeleteTile(tx, ty);

                AddPart(P_EXPLOSION, Ludens[num].posX, Ludens[num].posY);

                // kill all nearby
                for (int i = 0; i < MAX_LUDENS; i++)
                    if ((Ludens[i].active)&&(i != num))
                        if ( (abs(Ludens[num].posX - Ludens[i].posX) < GRENADE_EXPLODERADIUS)
                                && (abs(Ludens[num].posY - Ludens[i].posY) < GRENADE_EXPLODERADIUS))
                        {
                            if (Ludens[i].style == HERO)
                                MyLudensDie();
                            if (Ludens[i].style == ZORTH)
                                Ludens[i].setAnimation(ANIM_ZORTH_DIE, 1, Ludens[i].animDirection, true, false);
                        }


                Ludens[num].kill();
            }
            break;
        }
        break;

    case SPRING: //SPRING
        Ludens[num].velX = Ludens[num].velX/2;
        break;

    case VSPRING: //VSPRING
        Ludens[num].velX = 0;
        Ludens[num].velY = 0;
        Ludens[num].posX = Ludens[num].oldX;
        Ludens[num].posY = Ludens[num].oldY;
        break;

    case RAZOR: //RAZOR
        if ((Ludens[num].onGround)||(Ludens[num].onWall)||(Ludens[num].onCeiling))
        {
            Ludens[num].interest--;
            if (Hearable(Ludens[num].posX, Ludens[num].posY))
                Engine.Sound.PlaySample(24);
            //Ludens[num].velX = Ludens[num].velX;
        }

        if (Ludens[num].interest == RAZOR_ARMEDTIME)
        {
            if (Hearable(Ludens[num].posX, Ludens[num].posY))
                Engine.Sound.PlaySample(11);
            Ludens[num].interest--;
        }

        if ((Ludens[num].interest > RAZOR_ARMEDTIME-1)&&(Ludens[num].interest < RAZOR_LIFE-1))
            Ludens[num].attitude = AI_NOTHING;
        else
            Ludens[num].attitude = AI_ARMED;

        if (abs(Ludens[num].velX) > RAZOR_MAXSPEEDX)
            Ludens[num].velX = Ludens[num].velX/2;

        if (Ludens[num].interest < 1)
        {
            Ludens[num].kill();
            Ludens[Ludens[num].owner].ammoCount++;
        }

        if ((Ludens[num].interest > RAZOR_ARMEDTIME-1)||(Ludens[num].interest < 1))
        {
            Ludens[num].setAnimation(ANIM_RAZOR_UNARMED, 1, Ludens[num].animDirection, false, false);
        }
        else
        {
            Ludens[num].setAnimation(ANIM_RAZOR_ARMED, 1, Ludens[num].animDirection, false, false);
            Ludens[num].moveSprite(0, -RAZOR_MOVE);
            if ((Ludens[num].onGround)||(Ludens[num].onWall)||(Ludens[num].onCeiling))
                if (Engine.random(2) == 0)
                    Ludens[num].velY = -abs(Ludens[num].velY);
        }

        if (Ludens[num].velX > 0)
        {
            Ludens[num].animDirection = RIGHT;
        }
        else
        {
            Ludens[num].animDirection = LEFT;
        }

        if (Ludens[num].animDirection == RIGHT)
        {
            Ludens[num].moveSprite(RAZOR_MOVE, 0);
        }
        if (Ludens[num].animDirection == LEFT)
        {
            Ludens[num].moveSprite(-RAZOR_MOVE, 0);
        }

        break;

    case BLOCK: //BLOCK
        Ludens[num].velX = 0;
        // Ludens[num].velY = 0;
        //  Ludens[num].posX = Ludens[num].oldX;
        //  Ludens[num].posY = Ludens[num].oldY;

        if ((Ludens[num].animNum == ANIM_BLOCK_CRACK)&&(Ludens[num].animTick == 4))
        {
            Ludens[num].kill();
        }
        break;

    case RABBIT: // RABBIT
        if (Ludens[num].onGround)
            Ludens[num].velX = 0;

        if (Ludens[num].velY < 0)
            Ludens[num].setAnimation(ANIM_RABBIT_JUMP, 1, Ludens[num].animDirection, false, false);
        else
            Ludens[num].setAnimation(ANIM_RABBIT_STAND, 1, Ludens[num].animDirection, false, false);

        if (Ludens[num].counter>0)
        {
            Ludens[num].moveSprite(0, -RABBIT_JUMP);

            if (Ludens[num].animDirection == LEFT)
                Ludens[num].moveSprite(-RABBIT_MOVE, 0);
            else
                Ludens[num].moveSprite(RABBIT_MOVE, 0);

            Ludens[num].counter--;
        }

        if (Ludens[num].onWall)
        {
            //  Ludens[num].animDirection = -Ludens[num].animDirection;
            if (Ludens[Ludens[num].target].posX < Ludens[num].posX)
                Ludens[num].animDirection = LEFT;
            else
                Ludens[num].animDirection = RIGHT;

            Ludens[num].counter = 2;
        }


        if (((Ludens[num].state & UP_PRESSED) == UP_PRESSED)  && (Ludens[num].onGround))
            Ludens[num].counter = 4;

        if (((Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)  && (Ludens[num].onGround))
            Ludens[num].animDirection = LEFT;

        if (((Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)  && (Ludens[num].onGround))
            Ludens[num].animDirection = RIGHT;

        Ludens[num].state = 0;
        break;

    case PLATFORM: //PLATFORM
        Ludens[num].velX = 0;
        Ludens[num].velY = 0;
        Ludens[num].posX = Ludens[num].oldX;
        Ludens[num].posY = Ludens[num].oldY;

        if ((Ludens[num].animNum == ANIM_PLATFORM_CRACK)&&(Ludens[num].animTick == 5))
        {
            Ludens[num].kill();
        }
        break;

    case HOVER: //HOVER
        if (Ludens[num].target > -1)
            Ludens[num].state = Ludens[Ludens[num].target].transferState;

        Ludens[num].setAnimation(ANIM_HOVER_HOVER, 1, Ludens[num].animDirection, false, true);

        // RIDING on...
        if (Ludens[num].anchor > -1)
        {
            // Ride the linetning
            if (Ludens[Ludens[num].anchor].style == LINE)
            {

                int x1, x2, y1, y2, m, k;
                x1 = Ludens[Ludens[num].anchor].posX;
                x2 = Ludens[Ludens[Ludens[num].anchor].target].posX;
                y1 = Ludens[Ludens[num].anchor].posY;
                y2 = Ludens[Ludens[Ludens[num].anchor].target].posY;

                m = 36;

                Ludens[num].velX = -(x1 - x2) / m;
                Ludens[num].velY = -(y1 - y2) / m;

                Ludens[num].anchorX = Ludens[num].anchorX + Ludens[num].velX;
                Ludens[num].anchorY = Ludens[num].anchorY + Ludens[num].velY;

                if ((Ludens[num].state & UP_PRESSED) != UP_PRESSED)
                {
                    Ludens[num].attitude = 0;
                }

                if (Ludens[num].attitude == 0)
                    if ((Ludens[num].state & UP_PRESSED) == UP_PRESSED)
                    {
                        Ludens[num].anchor = -1;
                        Ludens[num].attitude = 100;
                        Ludens[num].moveSprite(0, -HOVER_MAXSPEED);
                    }
            }

            break;
        } // end ride

        //if (abs(Ludens[num].velX) > HOVER_MAXSPEED2)
        //	Ludens[num].velX = Ludens[num].velX /2;

        if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
        {
            Ludens[num].moveSprite(HOVER_MOVE, 0);
            Ludens[num].setAnimation(ANIM_HOVER_HOVER, 1, RIGHT, false, true);
            Ludens[num].animDirection = RIGHT;
        }
        if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
        {
            Ludens[num].moveSprite(-HOVER_MOVE, 0);
            Ludens[num].setAnimation(ANIM_HOVER_HOVER, 1, LEFT, false, true);
            Ludens[num].animDirection = LEFT;
        }

        if (((Ludens[num].state & UP_PRESSED) == UP_PRESSED)&&(Ludens[num].onGround))
        {
            Ludens[num].moveSprite(0, -HOVER_JUMP);
            Ludens[num].setAnimation(ANIM_HOVER_KICKFLIP, 1, Ludens[num].animDirection, true, false);
        }

        if (((Ludens[num].state & DOWN_PRESSED) == DOWN_PRESSED)&&(Ludens[num].onGround))
            Ludens[num].maxSpeed = HOVER_MAXSPEED2;
        else
            Ludens[num].maxSpeed = HOVER_MAXSPEED;

        break;

    case LINE: //LINE
        Ludens[num].velX = 0;
        Ludens[num].velY = 0;
        Ludens[num].posX = Ludens[num].oldX;
        Ludens[num].posY = Ludens[num].oldY;
        break;

    case HIDE: //HIDE
        Ludens[num].velX = 0;
        Ludens[num].velY = 0;
        Ludens[num].posX = Ludens[num].oldX;
        Ludens[num].posY = Ludens[num].oldY;

        //Ludens[num].animTick = Ludens[num].target;
        break;

    case BIKE: //BIKE
        if (Ludens[num].target > -1)
        {
            Ludens[num].state = Ludens[Ludens[num].target].transferState;
            Ludens[num].setAnimation(ANIM_BIKE_ZORTH, 1, Ludens[num].animDirection, false, false);

            if (Ludens[Ludens[num].target].target > -1)
            {
                distX = abs(Ludens[num].posX - Ludens[Ludens[Ludens[num].target].target].posX);
                distY = abs(Ludens[num].posY - Ludens[Ludens[Ludens[num].target].target].posY);
            }
            else
            {
                distX = 9999999;
                distY = 9999999;
            }
            if (((distX + distY) < (TILE_WIDTH*15 << FIX)))
                Ludens[num].maxSpeed = (distX + distY) / 12;
            else
                Ludens[num].maxSpeed = BIKE_MAXSPEED;

            if (((distX) < (TILE_WIDTH*2 << FIX)))
                Ludens[num].velX = Ludens[num].velX / 2;

            if (Ludens[num].maxSpeed < BIKE_MAXSPEED)
                Ludens[num].maxSpeed = BIKE_MAXSPEED;
        }
        else
        {
            Ludens[num].setAnimation(ANIM_BIKE_HOVER, 1, Ludens[num].animDirection, false, true);
        }

        if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
        {
            Ludens[num].moveSprite(BIKE_MOVE, 0);
            if ((Ludens[num].animNum != ANIM_BIKE_ZORTHFIRE)&&(Ludens[num].animTick < 3))
                Ludens[num].setAnimation(ANIM_BIKE_ZORTHGO, 1, RIGHT, false, true);
            Ludens[num].animDirection = RIGHT;
        }
        if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
        {
            Ludens[num].moveSprite(-BIKE_MOVE, 0);
            if ((Ludens[num].animNum != ANIM_BIKE_ZORTHFIRE)&&(Ludens[num].animTick < 3))
                Ludens[num].setAnimation(ANIM_BIKE_ZORTHGO, 1, LEFT, false, true);
            Ludens[num].animDirection = LEFT;
        }

        //		if (((Ludens[num].state & UP_PRESSED) == UP_PRESSED)&&(Ludens[num].onGround))
        if ((Ludens[num].state & UP_PRESSED) == UP_PRESSED)
        {
            Ludens[num].moveSprite(0, -BIKE_JUMP);
            //Ludens[num].setAnimation(ANIM_BIKE_ZORTH, 1, Ludens[num].animDirection, true, false);
        }

        break;

    case DESTRUCT: //DESTRUCT
        Ludens[num].velX = 0;
        Ludens[num].velY = 0;
        Ludens[num].posX = Ludens[num].oldX;
        Ludens[num].posY = Ludens[num].oldY;

        if (Ludens[num].animNum == ANIM_DESTRUCT_DESTROY)
        {
            int tx = (Ludens[num].posX  >> FIX) / TILE_WIDTH;
            int ty = ((Ludens[num].posY >> FIX) + TILE_HEIGHT) / TILE_HEIGHT;

            if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH-1) && (ty < MAP_HEIGHT-1))
                if (Map.getCell(tx, ty) == 0)
                {
                    DeleteTile(tx, ty);
                    AddPart(P_PUFF, (tx*TILE_WIDTH << FIX), (ty*TILE_HEIGHT << FIX));
                }

            tx = ((Ludens[num].posX  >> FIX)) / TILE_WIDTH;
            ty = ((Ludens[num].posY >> FIX) - TILE_HEIGHT) / TILE_HEIGHT;

            if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH-1) && (ty < MAP_HEIGHT-1))
                if (Map.getCell(tx, ty) == 0)
                {
                    DeleteTile(tx, ty);
                    AddPart(P_PUFF, (tx*TILE_WIDTH << FIX), (ty*TILE_HEIGHT << FIX));
                }

            tx = ((Ludens[num].posX  >> FIX) + TILE_WIDTH) / TILE_WIDTH;
            ty = ((Ludens[num].posY >> FIX)) / TILE_HEIGHT;

            if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH-1) && (ty < MAP_HEIGHT-1))
                if (Map.getCell(tx, ty) == 0)
                {
                    DeleteTile(tx, ty);
                    AddPart(P_PUFF, (tx*TILE_WIDTH << FIX), (ty*TILE_HEIGHT << FIX));
                }

            tx = ((Ludens[num].posX  >> FIX) - TILE_WIDTH) / TILE_WIDTH;
            ty = ((Ludens[num].posY >> FIX)) / TILE_HEIGHT;

            if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH-1) && (ty < MAP_HEIGHT-1))
                if (Map.getCell(tx, ty) == 0)
                {
                    DeleteTile(tx, ty);
                    AddPart(P_PUFF, (tx*TILE_WIDTH << FIX), (ty*TILE_HEIGHT << FIX));
                }


            if (Hearable(Ludens[num].posX, Ludens[num].posY))
                Engine.Sound.PlaySample(27);
            Ludens[num].kill();
        }

        Ludens[num].setAnimation(ANIM_DESTRUCT_HIDDEN, 1, LEFT, false, true);
        break;

    case SECRET: //SECRET
        Ludens[num].velX = 0;
        Ludens[num].velY = 0;
        Ludens[num].posX = Ludens[num].oldX;
        Ludens[num].posY = Ludens[num].oldY;
        break;

    case GUSTAV: //GUSTAV
        // Ludens[num].velX = 0;
        //  Ludens[num].velY = 0;
        //if (mainTickCounter % 2 == 0)
        {
            if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
            {
                Ludens[num].moveSprite( GUSTAV_MAXSPEED, 0);
                Ludens[num].setAnimation(ANIM_GUSTAV_PLAY, 2, RIGHT, false, true);
                Ludens[num].animDirection = RIGHT;
            }
            else
                if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
                {
                    //Ludens[num].moveSprite( -GUSTAV_MAXSPEED, 0);
                    Ludens[num].velX = 0;
                    Ludens[num].setAnimation(ANIM_GUSTAV_PLAY, 2, RIGHT, false, true);
                    Ludens[num].animDirection = RIGHT;
                }
                else
                    Ludens[num].setAnimation(ANIM_GUSTAV_DEFAULT, 5, RIGHT, false, true);
        }
        break;

    case WATER: //WATER
        // if ( (abs(Ludens[num].velX) > (WATER_MAXSPEED2)) || ((!Ludens[num].onGround)) )
        //	  Ludens[num].velX = Ludens[num].velX/2;

        if (Ludens[num].velX == 0)
        {
            Ludens[num].velX = WATER_MOVE;
        }

        if (!Ludens[num].onGround)
        {
            Ludens[num].state = 0;
            Ludens[num].velX = 0;
        }

		//if ((Ludens[num].onWall)&&(Ludens[num].onGround))
		//{
		//	Ludens[num].moveSprite(0, -(32 << FIX));
		//}

        if (( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED) || (Ludens[num].velX > 0))
        {
            Ludens[num].setAnimation(ANIM_WATER_ROLL, 1, RIGHT, false, true);
            Ludens[num].moveSprite(WATER_MOVE, 0);
            Ludens[num].animDirection = RIGHT;
        }
        if (( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED) || (Ludens[num].velX < 0))
        {
            Ludens[num].setAnimation(ANIM_WATER_ROLL, 1, LEFT, false, true);
            Ludens[num].moveSprite( -WATER_MOVE, 0);
            Ludens[num].animDirection = LEFT;
        }

        int tx, ty;
        int k, i, j, x1, x2;
        tx = (Ludens[num].posX >> FIX) / TILE_WIDTH;
        ty = (Ludens[num].posY >> FIX) / TILE_HEIGHT;

        if (Ludens[num].velX > 0)
        {
            x1 = -2;
            x2 = 1;
        }
        else
        {
            x1 = -1;
            x2 = 2;
        }

        for (j=-1; j<1; j++)
        {
            for (i=x1; i<x2; i++)
            {
                k = Map.getCell(tx + i, ty + j);
                if (k == -1)
                    Map.setCell(tx + i, ty + j, 46);
                else
                    if ((k != 0)&&(k < 46))
                        Map.setCell(tx + i, ty + j, 48 + k);
            }
        }

        k = Map.getCell(tx, ty - 2);
        if ((k != 0)&&(k < 46)&&(Map.getCell(tx, ty - 1) > 45))
            Map.setCell(tx, ty - 2, 48);

        break;

    case STEP: //STEP
        Ludens[num].velX = 0;
        Ludens[num].velY = 0;
        Ludens[num].posX = Ludens[num].oldX;
        Ludens[num].posY = Ludens[num].oldY;

        Ludens[num].setAnimation(ANIM_STEP_HIDDEN, 1, LEFT, false, true);
        break;

    case MOLE: //MOLE
		// moving
		if (mainTickCounter % 2 == 0)
		if (Ludens[num].state == 0)
		{
			Ludens[num].velX = Ludens[num].velX/2;
			Ludens[num].velY = Ludens[num].velY/2;
		}

        if ( (Ludens[num].state & RIGHT_PRESSED) == RIGHT_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_MOLE_DRILL_WEST, 1, RIGHT, false, true);
            Ludens[num].moveSprite(MOLE_MOVE, 0);
            Ludens[num].animDirection = RIGHT;
			tx = ((Ludens[num].posX  >> FIX)+TILE_WIDTH) / TILE_WIDTH;
			ty = ((Ludens[num].posY >> FIX)) / TILE_HEIGHT;
        }
        if ( (Ludens[num].state & LEFT_PRESSED) == LEFT_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_MOLE_DRILL_EAST, 1, LEFT, false, true);
            Ludens[num].moveSprite( -MOLE_MOVE, 0);
            Ludens[num].animDirection = LEFT;
			tx = ((Ludens[num].posX  >> FIX)-TILE_WIDTH) / TILE_WIDTH;
			ty = ((Ludens[num].posY >> FIX)) / TILE_HEIGHT;
        }
        if ( (Ludens[num].state & DOWN_PRESSED) == DOWN_PRESSED)
        {
            Ludens[num].setAnimation(ANIM_MOLE_DRILL_SOUTH, 1, DOWN, false, true);
            Ludens[num].moveSprite( 0, MOLE_MOVE);
            Ludens[num].animDirection = DOWN;
			tx = (Ludens[num].posX  >> FIX) / TILE_WIDTH;
			ty = ((Ludens[num].posY >> FIX)+TILE_HEIGHT) / TILE_HEIGHT;
        }
        if ( (Ludens[num].state & UP_PRESSED) == UP_PRESSED)
        {			
            Ludens[num].setAnimation(ANIM_MOLE_DRILL_NORTH, 1, UP, false, true);
            Ludens[num].moveSprite( 0, -MOLE_MOVE-MOLE_GRAVITY);
            Ludens[num].animDirection = UP;
			tx = (Ludens[num].posX  >> FIX) / TILE_WIDTH;
			ty = ((Ludens[num].posY >> FIX)-TILE_HEIGHT) / TILE_HEIGHT;
        }

		// drill!
		//if ( (Ludens[num].velX != 0)&&(Ludens[num].velY != 0) )
        if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH-1) && (ty < MAP_HEIGHT-1))
            if (Map.getCell(tx, ty) == 0)
            {
                DeleteTile(tx, ty);
                AddPart(P_PUFF, (tx*TILE_WIDTH << FIX), (ty*TILE_HEIGHT << FIX));
            }
        break;

    case BAG: //BAG
        int tx2, ty2;
		int kk;
        tx2 = (Ludens[num].posX >> FIX) / TILE_WIDTH;
        ty2 = (Ludens[num].posY >> FIX) / TILE_HEIGHT;

        kk = Map.getCell(tx2, ty2+1);
        if (kk != 0)
		{
			Ludens[num].gravity = BAG_GRAVITY2;
		}

		if (Ludens[num].onGround)
			Ludens[num].setAnimation(ANIM_BAG_MONEY, 1, LEFT, false, true);

        break;

	}


    // All

    if (Ludens[num].anchor > -1)
    {
        Ludens[num].oldX = Ludens[num].posX;
        Ludens[num].oldY = Ludens[num].posY;
        Ludens[num].posX = Ludens[num].posX - (Ludens[num].posX - (Ludens[Ludens[num].anchor].posX + Ludens[num].anchorX));
        Ludens[num].posY = Ludens[num].posY - (Ludens[num].posY - (Ludens[Ludens[num].anchor].posY + Ludens[num].anchorY));

        //	Ludens[num].posY = Ludens[Ludens[num].anchor].posY + Ludens[num].anchorY;
        Ludens[num].velX = Ludens[num].velY = 0;
    }

    Ludens[num].state = 0;

    // effects
    // dust
    if (Ludens[num].style == HERO)
        if (Ludens[num].onGround || Ludens[num].onWall)
            if ((mainTickCounter % 8 == 0)||(Engine.random(9) == 0))
                if ( (Ludens[num].animNum == ANIM_HERO_RUN) || (Ludens[num].animNum == ANIM_HERO_WALL_CLIMB))
                {
                    int offset, offsety;
                    offset = 0;
                    offsety = (1 << FIX);

                    if (Ludens[num].animDirection == LEFT)
                    {
                        if (Ludens[num].onWall)
                            offset = -Ludens[num].radiusX;
                        else
                            offset = Ludens[num].radiusX;
                    }
                    else
                    {
                        if (!Ludens[num].onWall)
                        {
                            offset = -Ludens[num].radiusX;
                            offsety = (-4 << FIX);
                        }
                    }

                    AddPart(P_DUST, Ludens[num].posX + offset, Ludens[num].posY + Ludens[num].radiusY + offsety);
                }


    //  //  //

    LudensPhysics(num);

    Ludens[num].advanceAnimations();

    Ludens[num].convertPosition();
}
