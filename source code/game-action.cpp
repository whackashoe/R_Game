#include "preheader.h"
#include "game.h"


void CGame::LudensResolveDependencies()
{
    for (int c=0; c<MAX_LUDENS; c++)
        if (Ludens[c].active)
            switch(Ludens[c].style)
            {
            case SWITCH:
                Ludens[c].target = ClosestStyleLudens(c, DOOR, DOOR, 0);
                break;
            case SWITCH2:
                Ludens[c].target = ClosestStyleLudens(c, ELEVATOR, ELEVATOR, 0);
                break;
            case SWITCH3:
                Ludens[c].target = ClosestStyleLudens(c, DOOR, DOOR, 0);
                break;
            };

    hint[0] = "Default controls:";
    hint[1] = "";
    hint[2] = "Left Arrow - move left";
    hint[3] = " stick to left wall";
    hint[4] = "Right Arrow - move right";
    hint[5] = " stick to right wall";
    hint[6] = "Down Arrow - duck";
    hint[7] = "Space Bar - jump";
    hint[8] = "Ctrl - hit with umbrella on ground";
    hint[9] = " in air open/close umbrella to float";
    hint[10] = "key Z - mini map";
    hint[11] = " combined with arrows - look around ";
    hint[12] = "";
    hint[13] = "Esc - options menu";
    hint[14] = "F1 - show/hide this help";

    // map specific ACTIONs on load map
    if (mapNum == 0)
    {
        Ludens[myLudens].kill();
        myLudens = -1;
        hintTimer = 0;
    }
    if (mapNum == 8)
    {
        hintTimer = 0;
    }
    if ((mapNum == 9)||(mapNum == 16))
    {
        hint[0] = "Hoverboard:";
        hint[1] = "";
        hint[2] = "Press duck button to gain speed";
        hint[3] = "";
        hint[4] = "";
        hint[5] = "";
        hint[6] = "";
        hint[7] = "";
        hint[8] = "";
        hint[9] = "";
        hint[10] = "";
        hint[11] = "";
        hint[12] = "";
        hint[13] = "";
        hint[14] = "";
    }
    //if (Map.tileSet == BLACK_SET)
    if ((mapNum >= ZORTHPLAY_MAP)&&(mapNum <= ZORTHEND_MAP))
    {
        Ludens[myLudens].kill();
        myLudens = AddLudens(ZORTH, cameraVX, cameraVY);
    }
}

///////// CUT SCENES STUFF
void CGame::StartCutScene()
{
    sceneTimer = 0;
}
void CGame::ProcessCutScene(int mapNum)
{
    sceneTimer++;

    cutScene = true;
    switch (mapNum)
    {
    case 0:
        CutScene_Intro();
        break;
    case 2:
        if (startSecret)
            CutScene_Travolta();
        else
            cutScene = false;
        break;
    case 5:
        CutScene_BaloonMan();
        break;
    case 10:
        CutScene_Boat();
        break;
    default:
        cutScene = false;
        break;
    }

    // fade out music
    if ((cutScene)&&(sceneTimer < 2))
        MusicFadeOut = Engine.Sound.DefaultVolume;
}

void CGame::RenderCutScene(int mapNum)
{
    switch (mapNum)
    {
    case 0:
        RenderCutScene_Intro();
        break;
    case 2:
        if (startSecret)
            RenderCutScene_Travolta();
        break;
    case 5:
        RenderCutScene_BaloonMan();
        break;
    case 10:
        RenderCutScene_Boat();
        break;
    default:
        break;
    }
}

void CGame::RenderAfterCutScene(int mapNum)
{
    Engine.DrawRectangle(0, 0, Engine.Screen->w, Engine.Screen->h/4, 0, 0, 0);
    Engine.DrawRectangle(0, 3*Engine.Screen->h/4, Engine.Screen->w, Engine.Screen->h/4, 0, 0, 0);

    switch (mapNum)
    {
    case 0:
        break;
    case 2:
        if (startSecret)
            RenderCutScene_Travolta();
        break;
    case 5:
        break;
    case 10:
        break;
    default:
        break;
    }
}

void CGame::ResetMusicCheck()
{
    useMusicCheck = true;
    musicStepCount = musicCheck = 0;
}

void CGame::CutScene_Intro()
{
    if (sceneTimer == 5)
    {
        Map.backgroundRed = 167;
        Map.backgroundGreen = 205;
        Map.backgroundBlue = 218;

        Engine.Sound.SpecialChannel = Engine.Sound.PlaySample(31);
        ResetMusicCheck();

        /*	sceneTimer = INTRO_STARTRUN-33;
        cameraX = 192;
        cameraY = 302 + sceneTimer;*/
    }

    if (sceneTimer < INTRO_ENDSCROLL)
    {
        cameraX = 192;
        cameraY = 302 + sceneTimer;
    }

    //I - 555
    if (sceneTimer == INTRO_STARTCREDITS)
    {
        Dialog.RestartDialog();
        Dialog.SetDialog("a game by", INTRO_CREDITSX , INTRO_CREDITSY, 93, sceneTimer);
    }

    if ((sceneTimer > INTRO_STARTCREDITS)&&(sceneTimer < INTRO_ENDSCROLL))
    {
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
            Dialog.SetDialog("Michal Marcinkowski", INTRO_CREDITSX, INTRO_CREDITSY, 98, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
            Dialog.SetDialog("", INTRO_CREDITSX, INTRO_CREDITSY, 195, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 3))
            Dialog.SetDialog("R", INTRO_CREDITSX, INTRO_CREDITSY, 98, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 4))
            Dialog.SetDialog("part I", INTRO_CREDITSX, INTRO_CREDITSY, 98, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 5))
            Dialog.SetDialog("'Weary dreams of melon rust'", INTRO_CREDITSX, INTRO_CREDITSY, 98, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 6))
            Dialog.SetDialog("", INTRO_CREDITSX, INTRO_CREDITSY, 98, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 7))
            Dialog.SetDialog("", INTRO_CREDITSX, INTRO_CREDITSY, 98, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 6))
            Dialog.SetDialog("", INTRO_CREDITSX, INTRO_CREDITSY, 98, sceneTimer);

        Dialog.y = INTRO_CREDITSY;
    }

    if (sceneTimer == INTRO_STARTNARRATE)
    {
        //Map.backgroundRed = 191;
        //Map.backgroundGreen = 230;
        //Map.backgroundBlue = 230;

        Dialog.RestartDialog();
        Dialog.SetDialog("Goodday...", INTRO_NARRATEX+20 , INTRO_NARRATEY, 90, sceneTimer);
    }

    if (sceneTimer > INTRO_ENDSCROLL)
    {
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
            Dialog.SetDialog("", INTRO_NARRATEX, INTRO_NARRATEY, 40, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
            Dialog.SetDialog("We see here", INTRO_NARRATEX, INTRO_NARRATEY, 50, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 3))
            Dialog.SetDialog("a nice little factory", INTRO_NARRATEX, INTRO_NARRATEY, 70, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 4))
            Dialog.SetDialog("run by good, noble chaps from GoodCo.", INTRO_NARRATEX, INTRO_NARRATEY, 70, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 5))
            Dialog.SetDialog("One day a rather unpleasant accident occured to them...", INTRO_NARRATEX, INTRO_NARRATEY, 90, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 6))
            Dialog.SetDialog("", INTRO_NARRATEX, INTRO_NARRATEY, 5, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 7))
            Dialog.SetDialog("", INTRO_NARRATEX, INTRO_NARRATEY, 5, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 8))
            Dialog.SetDialog("", INTRO_NARRATEX, INTRO_NARRATEY, 5, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 9))
            Dialog.SetDialog("Meet Joseph, the cleaner.", INTRO_NARRATEX, INTRO_NARRATEY, 70, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 10))
            Dialog.SetDialog("This, rather odd little fellow, was working there at the time.", INTRO_NARRATEX, INTRO_NARRATEY, 90, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 10))
            Dialog.SetDialog("As usual Joseph was trying to do his job as best as he could.", INTRO_NARRATEX, INTRO_NARRATEY, 90, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 11))
            Dialog.SetDialog("Sometimes dreaming of finding treasure...", INTRO_NARRATEX, INTRO_NARRATEY, 80, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 12))
            Dialog.SetDialog("While he was dozing a bit, his rest was disturbed.", INTRO_NARRATEX, INTRO_NARRATEY, 90, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 13))
            Dialog.SetDialog("'Help!, Help us!!'", INTRO_NARRATEX, INTRO_NARRATEY, 70, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 14))
            Dialog.SetDialog("shouted a merry man to Joseph.", INTRO_NARRATEX, INTRO_NARRATEY, 80, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 15))
            Dialog.SetDialog("'Where the fuck is that shithead when he is needed!'", INTRO_SHOUTX, INTRO_SHOUTY, 60, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 16))
            Dialog.SetDialog("and asked Joseph for a favour.", INTRO_NARRATEX, INTRO_NARRATEY, 80, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 17))
            Dialog.SetDialog("", INTRO_NARRATEX, INTRO_NARRATEY, 1, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 18))
            Dialog.SetDialog("", INTRO_NARRATEX, INTRO_NARRATEY, 1, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 19))
            Dialog.SetDialog("", INTRO_NARRATEX, INTRO_NARRATEY, 1, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 20))
            Dialog.SetDialog("Move your stupid ass and catch that monster!!!", INTRO_SHOUTX, INTRO_SHOUTY, 70, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 21))
            Dialog.SetDialog("'Oh how I've dreamt of helping you Sir.'", INTRO_NARRATEX, INTRO_NARRATEY, 80, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 22))
            Dialog.SetDialog("'Of course! I shall catch it right away!'", INTRO_NARRATEX, INTRO_NARRATEY, 80, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 23))
            Dialog.SetDialog("replied our obliging hero and rushed to catch the runaway creature.", INTRO_NARRATEX, INTRO_NARRATEY, 120, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 24))
            Dialog.SetDialog("'What?'", INTRO_SHOUT2X, INTRO_SHOUT2Y, 50, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 25))
            Dialog.SetDialog("", INTRO_NARRATEX, INTRO_NARRATEY, 20, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 26))
            Dialog.SetDialog("Bunny!", INTRO_SHOUT2X, INTRO_SHOUT2Y-59, 20, sceneTimer);
    }


    if (sceneTimer == INTRO_STARTRUN)
    {
        myLudens = AddLudens(HERO, INTRO_JOSEPHX << FIX, INTRO_JOSEPHY << FIX);
        Ludens[myLudens].setAnimation(ANIM_HERO_STAND, 1, RIGHT, false, false);
        Ludens[myLudens].animDirection = RIGHT;
        Ludens[myLudens].idleCounter = 3;

        cameraVX = cameraX << FIX;
        cameraVY = cameraY << FIX;
    }

    if (sceneTimer == INTRO_BUNNYAPPEAR)
    {
        sceneLudens[0] = AddLudens(RABBIT, INTRO_RABBITX << FIX, INTRO_RABBITY << FIX);
        //	Ludens[sceneLudens[0]].target = myLudens;
    }

    if (sceneTimer == INTRO_BUNNYAPPEAR+18)
    {
        Engine.Sound.SpecialChannel = Engine.Sound.PlaySample(33);
        ResetMusicCheck();
    }

    if ((sceneTimer > INTRO_BUNNYRUN)&&(sceneTimer < INTRO_FALL))
    {
        Ludens[myLudens].state = RIGHT_PRESSED;
    }

    if (sceneTimer == INTRO_FALL)
    {
        Ludens[myLudens].state = 0;
        Ludens[sceneLudens[0]].kill();
    }

    if (sceneTimer == INTRO_FALL + 10)
    {
        Ludens[myLudens].state = LEFT_PRESSED;
    }
    if (sceneTimer == INTRO_FALL + 16)
    {
        Ludens[myLudens].state = RIGHT_PRESSED;
    }

    if (sceneTimer == INTRO_FALL + 30)
    {
        Ludens[myLudens].state = LEFT_PRESSED;
    }
    if (sceneTimer == INTRO_FALL + 58)
    {
        Ludens[myLudens].state = RIGHT_PRESSED;
    }

    //return;

    // start intro music
    if (sceneTimer == INTRO_FALL + 2)
    {
        Engine.Sound.SpecialChannel = Engine.Sound.PlaySample(34);
        ResetMusicCheck();
    }

    // flash
    if ((sceneTimer == INTRO_STARTRAIN - 50)||(sceneTimer == INTRO_STARTRAIN + 50)||(sceneTimer == INTRO_STARTRAIN + 90)
            ||(sceneTimer == INTRO_STARTRAIN + 150)||(sceneTimer == INTRO_STARTRAIN + 220)||(sceneTimer == INTRO_STARTRAIN + 230)
            ||(sceneTimer == INTRO_STARTRAIN + 234)||(sceneTimer == INTRO_STARTRAIN + 370)
            ||(sceneTimer == INTRO_THUNDER-5)||(sceneTimer == INTRO_THUNDER)
            ||(sceneTimer == INTRO_THUNDER+25)||(sceneTimer == INTRO_THUNDER+40)||(sceneTimer == INTRO_THUNDER+100)
            ||(sceneTimer == INTRO_THUNDER+35)||(sceneTimer == INTRO_THUNDER+60)||(sceneTimer == INTRO_THUNDER+90)
            ||(sceneTimer == INTRO_THUNDER+105)||(sceneTimer == INTRO_THUNDER+110)||(sceneTimer == INTRO_THUNDER+120)
            ||(sceneTimer == INTRO_THUNDER+145)||(sceneTimer == INTRO_THUNDER+180)||(sceneTimer == INTRO_THUNDER+213)
            ||(sceneTimer == INTRO_THUNDER+135)||(sceneTimer == INTRO_THUNDER+140)||(sceneTimer == INTRO_THUNDER+160)
            ||(sceneTimer == INTRO_THUNDER+155)||(sceneTimer == INTRO_THUNDER+190)||(sceneTimer == INTRO_THUNDER+240)
            ||(sceneTimer == INTRO_THUNDER+215)||(sceneTimer == INTRO_THUNDER+245)||(sceneTimer == INTRO_THUNDER+282)
            ||(sceneTimer == INTRO_THUNDER+255)||(sceneTimer == INTRO_THUNDER+310)||(sceneTimer == INTRO_THUNDER+312)
            ||(sceneTimer == INTRO_THUNDER+202)||(sceneTimer == INTRO_THUNDER+266)||(sceneTimer == INTRO_THUNDER+301)
            ||(sceneTimer == INTRO_THUNDER+295)||(sceneTimer == INTRO_THUNDER+303)||(sceneTimer == INTRO_THUNDER+272)
            ||(sceneTimer == INTRO_THUNDER+218)||(sceneTimer == INTRO_THUNDER+224)||(sceneTimer == INTRO_THUNDER+297)
       )
    {
        Map.backgroundRed = 242;
        Map.backgroundGreen = 255;
        Map.backgroundBlue = 255;
    }
    else
    {
        //Map.backgroundRed = 192;
        //Map.backgroundGreen = 230;
        //Map.backgroundBlue = 230;
        Map.backgroundRed = 172;
        Map.backgroundGreen = 210;
        Map.backgroundBlue = 220;

        if (sceneTimer > INTRO_THUNDER)
        {
            Map.backgroundRed = 210 - (sceneTimer/15) - 10 + Engine.random(40);
            Map.backgroundGreen = 225 - (sceneTimer/15);
            Map.backgroundBlue = 235 - (sceneTimer/15) - 20 + Engine.random(40);
        }
    }

    // open umbrella
    if (sceneTimer == INTRO_STARTRAIN + 50)
    {
        Ludens[myLudens].setAnimation(ANIM_HERO_RAIN, 2, Ludens[myLudens].animDirection, true, false);
    }
    if (sceneTimer > INTRO_STARTRAIN + 55)
    {
        Ludens[myLudens].setAnimation(ANIM_HERO_RAIN, 2, Ludens[myLudens].animDirection, true, false);
		Ludens[myLudens].animTick = 4;
		Ludens[myLudens].animSpeedTick = 0;
    }

    // thunderstrike!
    if (sceneTimer == INTRO_THUNDER+2)
    {
        AddPart(P_DUST, Ludens[myLudens].posX + (-1 << FIX), Ludens[myLudens].posY + Ludens[myLudens].radiusY + (-4 << FIX));
        AddPart(P_DUST, Ludens[myLudens].posX + (-8 << FIX), Ludens[myLudens].posY + Ludens[myLudens].radiusY + (-4 << FIX));
        //Ludens[myLudens].posX = 0;
        Ludens[myLudens].kill();
    }

    // the end!
    if (sceneTimer == INTRO_END)
    {
        NextMap();
    }
}

void CGame::RenderCutScene_Intro()
{//247, 905 - 2100
    Engine.Blit(CloudsImage[2], 517  - cameraX, 302  - cameraY);
    Engine.Blit(CloudsImage[0], 317  - cameraX, 402  - cameraY);
    Engine.Blit(CloudsImage[1], 517  - cameraX, 702  - cameraY);
    Engine.Blit(CloudsImage[0], 467  - cameraX, 672  - cameraY);
    Engine.Blit(CloudsImage[2], 417  - cameraX, 802  - cameraY);
    Engine.Blit(CloudsImage[0], 297  - cameraX, 1102  - cameraY);
    Engine.Blit(CloudsImage[1], 376  - cameraX, 1002  - cameraY);
    Engine.Blit(CloudsImage[0], 397  - cameraX, 1302  - cameraY);
    Engine.Blit(CloudsImage[1], 357  - cameraX, 1282  - cameraY);
    Engine.Blit(CloudsImage[2], 537  - cameraX, 1402  - cameraY);
    Engine.Blit(CloudsImage[1], 737  - cameraX, 1452  - cameraY);
    Engine.Blit(CloudsImage[2], 797  - cameraX, 1602  - cameraY);
    Engine.Blit(CloudsImage[0], 297  - cameraX, 1702  - cameraY);
    Engine.Blit(CloudsImage[1], 697  - cameraX, 1802  - cameraY);
    Engine.Blit(CloudsImage[0], 357  - cameraX, 1872  - cameraY);
    Engine.Blit(CloudsImage[0], 597  - cameraX, 1902  - cameraY);
    Engine.Blit(CloudsImage[2], 897  - cameraX, 2002  - cameraY);
    Engine.Blit(GoodCoImage[0], 191  - cameraX, 2088  - cameraY);

    if (sceneTimer < INTRO_STARTRUN)
        Engine.Blit(HeroImage[38], 380, 400);

    //Engine.DrawRectangle(340, 283, 120, 15, 0, 0, 0);

    // intro - thunder
    if ((sceneTimer > INTRO_THUNDER)&&(sceneTimer < INTRO_THUNDER + 2))
        Engine.Blit(ThunderImage[0], (Ludens[myLudens].posX >> FIX) - 17  - cameraX, (Ludens[myLudens].posY >> FIX) - 151  - cameraY);
}

void CGame::CutScene_Travolta()
{
    if (sceneTimer == TV_BANANADIALOGSTART)
    {
        Dialog.RestartDialog();
        Dialog.SetDialog("Bananas!", TV_BANANAX , TV_BANANAY, 55, sceneTimer);
    }
    if (sceneTimer > TV_BANANADIALOGSTART)
    {
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
            Dialog.SetDialog("Fresh bananas!", TV_BANANAX, TV_BANANAY, 55, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
            Dialog.SetDialog("Who wants some tasty bananas?", TV_BANANAX, TV_BANANAY, 55, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 3))
            Dialog.SetDialog("John?", TV_TRAVOLTAX, TV_TRAVOLTAY, 55, sceneTimer);
    }
    if (sceneTimer == TV_DIALOGSTART)
    {
        Dialog.RestartDialog();
        Dialog.SetDialog("Oh no, not you again.", TV_TRAVOLTAX, TV_TRAVOLTAY, 85, sceneTimer);
    }
    if ((sceneTimer > TV_DIALOGSTART)&&(sceneTimer < TV_BANANADIALOGSTART))
    {
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
            Dialog.SetDialog("Me? I've never been here before!", DIALOG_HERO_X, DIALOG_HERO_Y, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
            Dialog.SetDialog("No?", TV_TRAVOLTAX, TV_TRAVOLTAY, 35, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 3))
            Dialog.SetDialog("No.", DIALOG_HERO_X, DIALOG_HERO_Y, 35, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 4))
            Dialog.SetDialog("...", TV_TRAVOLTAX, TV_TRAVOLTAY, 35, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 5))
            Dialog.SetDialog("...", DIALOG_HERO_X, DIALOG_HERO_Y, 35, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 6))
            Dialog.SetDialog("I say, some rather nasty trip you've had?", TV_TRAVOLTAX, TV_TRAVOLTAY, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 7))
            Dialog.SetDialog("Yes, I don't know what I'm doing here to be honest.", DIALOG_HERO_X, DIALOG_HERO_Y, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 8))
            Dialog.SetDialog("So what are you waiting for", TV_TRAVOLTAX, TV_TRAVOLTAY, 55, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 9))
            Dialog.SetDialog("give me that umbrella.", TV_TRAVOLTAX, TV_TRAVOLTAY+3, 55, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 10))
            Dialog.SetDialog("What!? It's my umbrella!", DIALOG_HERO_X, DIALOG_HERO_Y, 55, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 11))
            Dialog.SetDialog("I won't ask you twice.", TV_TRAVOLTAX, TV_TRAVOLTAY, 55, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 12))
            Dialog.SetDialog("Piss off.", DIALOG_HERO_X, DIALOG_HERO_Y, 45, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 13))
            Dialog.SetDialog("I see, then I must rip your spine off.", TV_TRAVOLTAX, TV_TRAVOLTAY, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 14))
            Dialog.SetDialog("No you won't. Where's the exit?", DIALOG_HERO_X, DIALOG_HERO_Y,65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 15))
            Dialog.SetDialog("Very well then, I shall eat your adrenal cortex.", TV_TRAVOLTAX, TV_TRAVOLTAY, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 16))
            Dialog.SetDialog("That's not edible!", DIALOG_HERO_X, DIALOG_HERO_Y, 55, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 17))
            Dialog.SetDialog("I shall listen to a Bee Gees record", TV_TRAVOLTAX, TV_TRAVOLTAY, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 18))
            Dialog.SetDialog("and eat it with ketchup.", TV_TRAVOLTAX, TV_TRAVOLTAY, 55, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 19))
            Dialog.SetDialog("You freak! Hey...", DIALOG_HERO_X, DIALOG_HERO_Y, 55, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 20))
            Dialog.SetDialog("You seem familiar...", DIALOG_HERO_X, DIALOG_HERO_Y, 45, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 21))
            Dialog.SetDialog("Yes [embarrassed]", TV_TRAVOLTAX, TV_TRAVOLTAY, 45, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 22))
            Dialog.SetDialog("I am often mistaken with John Travolta.", TV_TRAVOLTAX, TV_TRAVOLTAY, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 23))
            Dialog.SetDialog("But I am not him, I am me.", TV_TRAVOLTAX, TV_TRAVOLTAY, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 24))
            Dialog.SetDialog("He is dead.", TV_TRAVOLTAX, TV_TRAVOLTAY, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 25))
            Dialog.SetDialog("?", DIALOG_HERO_X, DIALOG_HERO_Y, 35, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 26))
            Dialog.SetDialog("Oh, that explains everything.", DIALOG_HERO_X, DIALOG_HERO_Y, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 27))
            Dialog.SetDialog("It's sad because it's true. But now", TV_TRAVOLTAX, TV_TRAVOLTAY, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 28))
            Dialog.SetDialog("I will dance like a little piggy", TV_TRAVOLTAX, TV_TRAVOLTAY + 5, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration + 24)&&(Dialog.count == 29))
        {
            Dialog.SetDialog("Maestro!", TV_TRAVOLTAX, TV_TRAVOLTAY, 25, sceneTimer);
            Engine.Sound.SpecialChannel = Engine.Sound.PlaySample(26);
            ResetMusicCheck();
        }
    }

    if (sceneTimer == OPENCURTAIN + 12)
        Ludens[myLudens].state = RIGHT_PRESSED;
    if (sceneTimer == OPENCURTAIN + 24)
        Ludens[myLudens].state = LEFT_PRESSED;
    if (sceneTimer == OPENCURTAIN + 48)
        Ludens[myLudens].state = RIGHT_PRESSED;
    if (sceneTimer == TV_END)
    {
        Map.backgroundRed = 98;
        Map.backgroundGreen = 52;
        Map.backgroundBlue = 18;
        startSecret = false;
        cutScene = false;
        Ludens[myLudens].posX = oldSecretX;
        Ludens[myLudens].posY = oldSecretY;
        if (Engine.Config.music == 1)
        {
            Engine.Sound.PauseMusic(false);
        }
        Engine.Sound.SetMusicVolume(Engine.Sound.DefaultVolume);
        Dialog.SetDialog("Oh... I must have dozed off a bit...", DIALOG_HERO_X, DIALOG_HERO_Y, 105, sceneTimer);
    }

}

void CGame::RenderCutScene_Travolta()
{

    if ((sceneTimer > TV_STARTDANCE)&&(sceneTimer < TV_DANCEEND))
    {
        Engine.Blit(BananaImage[0], Engine.Screen->w/3  + 26 - 300 + (sceneTimer % TV_STARTDANCE), Engine.Screen->h/3 + 48 + 20 + 35);
        Engine.Blit(TravoltaBackImage[(sceneTimer/4) % 2], Engine.Screen->w/3 + 26, Engine.Screen->h/3 + 22 + 30);
        Map.backgroundRed = Engine.random(255);
        Map.backgroundGreen = Engine.random(255);
        Map.backgroundBlue = Engine.random(255);
    }
    else
        if (sceneTimer > TV_DANCEEND)
        {
            Engine.Blit(BananaImage[0], Engine.Screen->w/3 - 300 + 26 + (sceneTimer % TV_STARTDANCE), Engine.Screen->h/3 + 48 + 20 + 35);
            Engine.Blit(TravoltaBackImage[0], Engine.Screen->w/3 + 26, Engine.Screen->h/3 + 20 + 35);
        }
        else
        {
            Engine.Blit(TravoltaBackImage[2], Engine.Screen->w/3 + 26, Engine.Screen->h/3 + 20 + 35);
            Map.backgroundRed = 111;
            Map.backgroundGreen = 99;
            Map.backgroundBlue = 99;
        }

    Engine.DrawRectangle(0, 0, Engine.Screen->w, Engine.Screen->h/3 + 55, 0, 0, 0);
    Engine.DrawRectangle(0, 2*Engine.Screen->h/3 - 40, Engine.Screen->w, Engine.Screen->h/3 + 20, 0, 0, 0);
    Engine.DrawRectangle(0, 0, Engine.Screen->w/3 + 26, Engine.Screen->h, 0, 0, 0);
    Engine.DrawRectangle(2*Engine.Screen->w/3 - 100, 0, Engine.Screen->w + 26, Engine.Screen->h, 0, 0, 0);
    if (sceneTimer < OPENCURTAIN)
        Engine.DrawRectangle(0, 0, Engine.Screen->w, Engine.Screen->h, 0, 0, 0);
}


/*
jozef goni krolika a ten wpada do lawy.
Jozef stoi i nie wiem co robic. Nagle slychac glos i pojawia sie
koles ktory nadmuchuje zwierzeta z balonow (ma ich kilka przy sobie):
"Well there goes your plot"
Jozef: " What? What? Who are you?"
Gosc: "I am a person that makes balloon animals."
Jozef: "Well... I can see that but WHO are you?"
Gosc: "You want me to tell something about myself?"
Jozef: "Yes"
Gosc: "I like bread with mayonaise"
Jozef: "Oh ok. What about the plot? What is my quest?"
Gosc: "You will know when the time comes"
Jozef: "When will the time come?"
Gosc: "When you are ready"
Jozef: "When will I be ready?"
Gosc: "When the time comes..."
Jozef: "Oh this is pointless. Will I find treasure?"
Gosc: "Yes. There are 6 secrets in this world. In one of them you will find your treasure. Now I must leave but we shall meet again."
 
Gosc znika i zostawia jozefowi balonowa zyrafe (rozowa).
*/

void CGame::CutScene_BaloonMan()
{
    if (sceneTimer == 1)
		Engine.Sound.SpecialChannel = Engine.Sound.PlaySample(35);

    if (sceneTimer < BM_HEROSTOP)
        Ludens[myLudens].state = LEFT_PRESSED;

    if (sceneTimer == BM_DIALOGSTART)
    {
        Dialog.RestartDialog();
        Dialog.SetDialog("Well there goes your plot.", BM_BALOONMANX, BM_BALOONMANY, 85, sceneTimer);
    }
    if (sceneTimer > BM_DIALOGSTART)
    {
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
            Dialog.SetDialog("What, what!? Who are you?", DIALOG_HERO_X, DIALOG_HERO_Y, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
            Dialog.SetDialog("I am a person that makes baloon animals.", BM_BALOONMANX, BM_BALOONMANY, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 3))
            Dialog.SetDialog("Well... I can see that but WHO are you?", DIALOG_HERO_X, DIALOG_HERO_Y, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 4))
            Dialog.SetDialog("You want me to tell something about myself?", BM_BALOONMANX, BM_BALOONMANY, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 5))
            Dialog.SetDialog("Yes.", DIALOG_HERO_X, DIALOG_HERO_Y, 40, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 6))
            Dialog.SetDialog("I like bread with mayonaise.", BM_BALOONMANX, BM_BALOONMANY, 70, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 7))
            Dialog.SetDialog("Oh ok. What about the plot? What is my quest?", DIALOG_HERO_X, DIALOG_HERO_Y, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 8))
            Dialog.SetDialog("You will know when the time comes.", BM_BALOONMANX, BM_BALOONMANY, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 9))
            Dialog.SetDialog("When will the time come?", DIALOG_HERO_X, DIALOG_HERO_Y, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 10))
            Dialog.SetDialog("When you are ready.", BM_BALOONMANX, BM_BALOONMANY, 55, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 11))
            Dialog.SetDialog("When will I be ready?", DIALOG_HERO_X, DIALOG_HERO_Y, 55, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 12))
            Dialog.SetDialog("When the time comes...", BM_BALOONMANX, BM_BALOONMANY, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 13))
            Dialog.SetDialog("When will the time come?", DIALOG_HERO_X, DIALOG_HERO_Y, 45, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 14))
            Dialog.SetDialog("Oh this is pointless.", DIALOG_HERO_X, DIALOG_HERO_Y, 55, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 15))
            Dialog.SetDialog("Will I find treasure?", DIALOG_HERO_X, DIALOG_HERO_Y, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 16))
            Dialog.SetDialog("Yes", BM_BALOONMANX, BM_BALOONMANY, 40, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 17))
            Dialog.SetDialog("...", BM_BALOONMANX, BM_BALOONMANY, 35, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 18))
            Dialog.SetDialog("There are 6 secrets in this world.", BM_BALOONMANX, BM_BALOONMANY, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 19))
            Dialog.SetDialog("In one of them you will find your treasure.", BM_BALOONMANX, BM_BALOONMANY, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 20))
            Dialog.SetDialog("Now I must leave but we shall meet again...", BM_BALOONMANX, BM_BALOONMANY, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 21))
            Dialog.SetDialog("Here have this pink giraffe.", BM_BALOONMANX, BM_BALOONMANY, 65, sceneTimer);

        if (sceneTimer == (BM_END - 1))
            Dialog.SetDialog("You suck.", BM_BALOONMANX, BM_BALOONMANY + 40, 2, sceneTimer);
    }

    if (sceneTimer == BM_END)
        NextMap();
}

void CGame::RenderCutScene_BaloonMan()
{
    if ((sceneTimer > BM_MANAPPEAR)&&(sceneTimer < BM_DISAPPEAR + 1))
        Engine.Blit(BaloonManImage[0], (BM_BALOONMANX) - cameraX, (BM_BALOONMANY) - cameraY);
    if (sceneTimer > BM_DISAPPEAR)
        Engine.Blit(BaloonManImage[1], (BM_BALOONMANX) - cameraX, (BM_BALOONMANY) - cameraY - (sceneTimer % (BM_DISAPPEAR+1))/4);
}


/*
Oldman: Where's your giraffe?
Jozef: Giraffe?
Oldman: Yes, I gave you a pink giraffe.
Jozef: Oh it's you? You look... different.
Oldman: Yes I can have any form I wish.
I decided that this form 
will be more appealing for you.
Jozef: What made you think that
an old man in a coffee shop
will be more appealing for me!?
Oldman: I don't know. Your mind is a mystery for me too.
Jozef: What? You're insane!
Oldman: Aaaa!? Bastards! I hate you!
You're all the fucking same!!!
I can't stand it!!
always
drinking wine from glasses
driving 40 km per hour on the fast lane
eating chips on parties with your dirty hands
commenting crap aloud in the cinema
pissing on the fucken floor
dumping shit in the urinal!
stinking in buses with vinegar
touching me with your filthy hands after the toilet
vomiting on public seat places
*/

void CGame::CutScene_Boat()
{
    if (sceneTimer == 1)
		Engine.Sound.SpecialChannel = Engine.Sound.PlaySample(35);

    if (sceneTimer == BO_TURN)
    {
        Ludens[myLudens].state = RIGHT_PRESSED;
        //sceneTimer = BO_STARTHERO;
    }

    if (sceneTimer == BO_MANDIALOG)
    {
        Dialog.RestartDialog();
        Dialog.SetDialog("Where's your giraffe?", BO_MANX, BO_MANY, 85, sceneTimer);
    }
    if ((sceneTimer > BO_MANDIALOG)&&(sceneTimer < BO_STARTMIMETALK))
    {
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
            Dialog.SetDialog("Giraffe?", DIALOG_HERO_X, DIALOG_HERO_Y, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
            Dialog.SetDialog("Yes, I gave you a pink giraffe.", BO_MANX, BO_MANY, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 3))
            Dialog.SetDialog("Oh it's you? You look... different.", DIALOG_HERO_X, DIALOG_HERO_Y, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 4))
            Dialog.SetDialog("Yes I can have any form I wish.", BO_MANX, BO_MANY, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 5))
            Dialog.SetDialog("I decided that this form", BO_MANX, BO_MANY, 70, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 6))
            Dialog.SetDialog("will be more appealing for you.", BO_MANX, BO_MANY, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 7))
            Dialog.SetDialog("What made you think that", DIALOG_HERO_X, DIALOG_HERO_Y, 70, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 8))
            Dialog.SetDialog("an old man in a coffee shop", DIALOG_HERO_X, DIALOG_HERO_Y, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 9))
            Dialog.SetDialog("will be more appealing for me!?", DIALOG_HERO_X, DIALOG_HERO_Y, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 10))
            Dialog.SetDialog("I don't know. Your mind is a mystery for me too.", BO_MANX, BO_MANY, 80, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 11))
            Dialog.SetDialog("What? What are you talking about!?", DIALOG_HERO_X, DIALOG_HERO_Y, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 12))
            Dialog.SetDialog("Aaaa!? Bastards! I hate you!", BO_MANX, BO_MANY, 70, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 13))
            Dialog.SetDialog("You're all the fucking same!!!", BO_MANX, BO_MANY, 70, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 14))
            Dialog.SetDialog("I can't stand it!!", BO_MANX, BO_MANY, 60, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 15))
            Dialog.SetDialog("always", BO_MANX, BO_MANY, 40, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 16))
            Dialog.SetDialog("drinking your wine from glasses", BO_MANX, BO_MANY, 60, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 17))
            Dialog.SetDialog("driving 40 km per hour on the fast lane", BO_MANX, BO_MANY, 60, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 18))
            Dialog.SetDialog("vomiting on public seat places", BO_MANX, BO_MANY, 60, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 19))
            Dialog.SetDialog("commenting crap aloud in the cinema", BO_MANX, BO_MANY, 50, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 20))
            Dialog.SetDialog("pissing on the fucken floor", BO_MANX, BO_MANY, 50, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 21))
            Dialog.SetDialog("dumping shit in the urinal!", BO_MANX, BO_MANY, 50, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 22))
            Dialog.SetDialog("stinking with vinegar in buses", BO_MANX, BO_MANY, 40, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 23))
            Dialog.SetDialog("???", DIALOG_HERO_X, DIALOG_HERO_Y, 35, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 24))
            Dialog.SetDialog("touching me with your filthy hands after the toilet", BO_MANX, BO_MANY, 50, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 25))
            Dialog.SetDialog("making your stupid crappy games", BO_MANX, BO_MANY, 50, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 26))
            Dialog.SetDialog("Where did you go?", BO_MANX, BO_MANY, 50, sceneTimer);
    }


    if (sceneTimer == BO_STARTHERO)
    {
        sceneLudens[0] = AddLudens(HERO, 957 << FIX, 1166 << FIX);
        sceneLudens[1] = AddLudens(GUSTAV, 557 << FIX, 2176 << FIX);
    }

    if (sceneTimer == BO_STARTRUN)
    {
        Ludens[myLudens].state = LEFT_PRESSED;
    }
    if ((sceneTimer > BO_STARTRUN)&&(sceneTimer < BO_FALL))
    {
        Ludens[sceneLudens[0]].state = LEFT_PRESSED;
    }

    if ((sceneTimer > BO_STARTCHASE)&&(sceneTimer < BO_FALL2))
    {
        Ludens[myLudens].state = LEFT_PRESSED;
    }

    if (sceneTimer == BO_FALL2)
    {
        Ludens[sceneLudens[0]].kill();
    }

    if ((sceneTimer > BO_RUNRIGHT)&&(sceneTimer < BO_STOPRUNRIGHT))
    {
        Ludens[myLudens].state = RIGHT_PRESSED;
    }

    if (sceneTimer == BO_STARTMIMETALK)
    {
        Dialog.RestartDialog();
        Dialog.SetDialog("Where did he go!?", DIALOG_HERO_X, DIALOG_HERO_Y, 90, sceneTimer);
    }

    if ((sceneTimer > BO_STARTMIMETALK)&&(sceneTimer < BO_STOPJUMPINBOAT))
    {
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
            Dialog.SetDialog("I can't tell you", BO_MIMEX, BO_MIMEY, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
            Dialog.SetDialog("I'm a mime, I don't speak.", BO_MIMEX, BO_MIMEY, 80, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 3))
            Dialog.SetDialog("", DIALOG_HERO_X, DIALOG_HERO_Y, 95, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 4))
            Dialog.SetDialog("Um...", DIALOG_HERO_X, DIALOG_HERO_Y, 40, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 5))
            Dialog.SetDialog("...", DIALOG_HERO_X, DIALOG_HERO_Y, 40, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 6))
            Dialog.SetDialog("So, what are you doing on this boat?", DIALOG_HERO_X, DIALOG_HERO_Y, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 7))
            Dialog.SetDialog("I'm standing.", BO_MIMEX, BO_MIMEY, 75, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 8))
            Dialog.SetDialog("", DIALOG_HERO_X, DIALOG_HERO_Y, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 9))
            Dialog.SetDialog("Hey, can you help me", DIALOG_HERO_X, DIALOG_HERO_Y, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 10))
            Dialog.SetDialog("I want to get to the next level?", DIALOG_HERO_X, DIALOG_HERO_Y, 70, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 11))
            Dialog.SetDialog("Of course! Jump on the boat!", BO_MIMEX, BO_MIMEY, 70, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 12))
            Dialog.SetDialog("Thanks.", DIALOG_HERO_X, DIALOG_HERO_Y, 50, sceneTimer);
    }

    if ((sceneTimer > BO_JUMPINBOAT)&&(sceneTimer < BO_STOPJUMPINBOAT))
    {
        Ludens[myLudens].state = RIGHT_PRESSED;
    }

    if (sceneTimer == BO_STOPJUMPINBOAT)
    {
        Dialog.RestartDialog();
        Dialog.SetDialog("You're welcome.", BO_MIMEX, BO_MIMEY, 70, sceneTimer);
    }

    if ((sceneTimer > BO_STOPJUMPINBOAT)&&(sceneTimer < BO_MOONPOP))
    {
        Ludens[myLudens].state = 0;
        Ludens[myLudens].setAnimation(ANIM_HERO_STAND, 1, RIGHT, false, false);

        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
            Dialog.SetDialog("", BO_MIMEX, BO_MIMEY, 30, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
            Dialog.SetDialog("I am Gustav, the singing mime.", BO_MIMEX, BO_MIMEY, 80, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 3))
            Dialog.SetDialog("I will sing you a song", BO_MIMEX, BO_MIMEY, 70, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 4))
            Dialog.SetDialog("that will warm your heart", BO_MIMEX, BO_MIMEY, 65, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 5))
            Dialog.SetDialog("and soothe your spirit,", BO_MIMEX, BO_MIMEY, 60, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 6))
            Dialog.SetDialog("you will never notice when you get", BO_MIMEX, BO_MIMEY, 55, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 7))
            Dialog.SetDialog("to the next level.", BO_MIMEX, BO_MIMEY, 50, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 8))
            Dialog.SetDialog("", BO_MIMEX, BO_MIMEY, 30, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 9))
            Dialog.SetDialog("Lights.", BO_MIMEX, BO_MIMEY, 35, sceneTimer);
    }

    if ((sceneTimer > BO_LIGHTOUT)&&(sceneTimer < BO_NEWLIGHT))
    {
        if (Map.backgroundRed > 47)
            Map.backgroundRed -= 5;
        if (Map.backgroundGreen > 42)
            Map.backgroundGreen -= 5;
        if (Map.backgroundBlue > 96)
            Map.backgroundBlue -= 5;
    }

    if (sceneTimer > BO_SWIM)
    {
        Ludens[sceneLudens[1]].state = RIGHT_PRESSED;
    }
    else
        Ludens[sceneLudens[1]].state = 0;

    if (sceneTimer == BO_MOONPOP)
    {
        //sceneLudens[1] = AddLudens(GUSTAV, 557 << FIX, 2176 << FIX);
        Dialog.RestartDialog();
        Dialog.SetDialog(". . .", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 140, sceneTimer);
        Engine.Sound.SpecialChannel = Engine.Sound.PlaySample(29);
        ResetMusicCheck();
    }

    if (sceneTimer > BO_MOONPOP)
    {
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
            Dialog.SetDialog("Sing along with me,", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 52, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
            Dialog.SetDialog("sing with the singing mime...", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 52, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 3))
            Dialog.SetDialog("", Ludens[sceneLudens[1]].posX >> FIX, BO_MIMEY, 96, sceneTimer);

        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 4))
            Dialog.SetDialog("Tonight here,", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 35, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 5))
            Dialog.SetDialog("I sing this song", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 50, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 6))
            Dialog.SetDialog("for my beloved", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 48, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 7))
            Dialog.SetDialog("dearest one", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 27, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 8))
            Dialog.SetDialog("my heart!", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 34, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 9))
            Dialog.SetDialog("Tonight here,", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 39, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 10))
            Dialog.SetDialog("I cry my tears", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 44, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 11))
            Dialog.SetDialog("because of you", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 42, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 12))
            Dialog.SetDialog("destiny island", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 35, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 13))
            Dialog.SetDialog("Maadagaaaaskar", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 39, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 14))
            Dialog.SetDialog("you are so faaaar", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 43, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 15))
            Dialog.SetDialog("tonight", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 100, sceneTimer);

        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 16))
            Dialog.SetDialog("Madagaskar,", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 35, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 17))
            Dialog.SetDialog("it is the island", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 50, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 18))
            Dialog.SetDialog("of my dreams", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 48, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 19))
            Dialog.SetDialog("of lemurs too", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 27, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 20))
            Dialog.SetDialog("oh lemurs!", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 34, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 21))
            Dialog.SetDialog("Although you,", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 39, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 22))
            Dialog.SetDialog("don't have a future", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 44, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 23))
            Dialog.SetDialog("or modern dentistry", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 42, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 24))
            Dialog.SetDialog("you still have lemurs.", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 35, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 25))
            Dialog.SetDialog("Maadagaaaaskar", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 39, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 26))
            Dialog.SetDialog("you are so faaaar", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 43, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 27))
            Dialog.SetDialog("tonight", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 330, sceneTimer);

        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 28))
            Dialog.SetDialog("Madagaskar,", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 35, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 29))
            Dialog.SetDialog("it is the island", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 50, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 30))
            Dialog.SetDialog("of my dreams", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 48, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 31))
            Dialog.SetDialog("of lemurs too", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 27, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 32))
            Dialog.SetDialog("oh lemurs!", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 34, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 33))
            Dialog.SetDialog("Although you,", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 39, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 34))
            Dialog.SetDialog("don't have a future", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 44, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 35))
            Dialog.SetDialog("or a sewage system", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 42, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 36))
            Dialog.SetDialog("you still have lemurs.", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 35, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 37))
            Dialog.SetDialog("Maadagaaaaskar", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 39, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 38))
            Dialog.SetDialog("you are so faaaar", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 43, sceneTimer);
        //if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 39))
        //			Dialog.SetDialog("tonight", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 410, sceneTimer);

        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 39))
            Dialog.SetDialog("tonight", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 120, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 40))
            Dialog.SetDialog("Man your animation is crappy.", DIALOG_HERO_X, DIALOG_HERO_Y, 90, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 41))
            Dialog.SetDialog("", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 200, sceneTimer);


        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 42))
            Dialog.SetDialog("Maaa", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 43))
            Dialog.SetDialog("mamamamama", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 44))
            Dialog.SetDialog("Maaa", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 45))
            Dialog.SetDialog("mamamamama", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 46))
            Dialog.SetDialog("Maaa", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 47))
            Dialog.SetDialog("mamamamama", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 48))
            Dialog.SetDialog("Maaa", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
        if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 49))
            Dialog.SetDialog("ORCHESTRA!", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);

        for (int k=0; k < 6; k++)
        {
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 42 + k*8))
                Dialog.SetDialog("Maaa", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 43 + k*8))
                Dialog.SetDialog("mamamamama", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 44 + k*8))
                Dialog.SetDialog("Maaa", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 45 + k*8))
                Dialog.SetDialog("mamamamama", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 46 + k*8))
                Dialog.SetDialog("Maaa", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 47 + k*8))
                Dialog.SetDialog("mamamamama", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 48 + k*8))
                Dialog.SetDialog("Maaa", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 49 + k*8))
                Dialog.SetDialog("MADAGASKAR!", Ludens[sceneLudens[1]].posX >> FIX, BO_KARAOKEY, 21, sceneTimer);
        }

    }

    if ((sceneTimer > BO_NEWLIGHT)&&(sceneTimer < BO_GOAGAIN))
    {
        if (Map.backgroundRed < 250)
            Map.backgroundRed += 4;
        if (Map.backgroundGreen < 230)
            Map.backgroundGreen += 4;
        if (Map.backgroundBlue < 56)
            Map.backgroundBlue += 4;
    }

    if (sceneTimer > BO_ENDPARTSONG)
    {
        Ludens[myLudens].state = 0;
        Ludens[myLudens].setAnimation(ANIM_HERO_TRUMPET, 10, RIGHT, false, true);
    }
    //542
    //143
    //160

    //stop go
    if (
        ((sceneTimer > BO_MOONPOP)&&(sceneTimer < BO_MOONPOP + 340))
        ||((sceneTimer > BO_MOONPOP + 1455)&&(sceneTimer < BO_MOONPOP + 1645))
        ||((sceneTimer > BO_MOONPOP + 2330)&&(sceneTimer < BO_GOAGAIN))
    )
    {
        Ludens[sceneLudens[1]].state = LEFT_PRESSED;
        Ludens[sceneLudens[1]].velX = 0;
    }

    //stop play
    if (
        ((sceneTimer > BO_MOONPOP + 1415)&&(sceneTimer < BO_MOONPOP + 1455))
        ||((sceneTimer > BO_MOONPOP + 2180)&&(sceneTimer < BO_MOONPOP + 2320))
        ||((sceneTimer > BO_ENDPARTSONG))
    )
    {
        Ludens[sceneLudens[1]].state = 0;
        Ludens[sceneLudens[1]].velX = 0;
    }

    if (sceneTimer == BO_END)
        NextMap();

    /*Map.backgroundRed = 176;
    Map.backgroundGreen = 196;
    Map.backgroundBlue = 96;*/
}

void CGame::RenderCutScene_Boat()
{
    Engine.Blit(StrangerImage[0], (BO_MANX) - cameraX, (BO_MANY) - cameraY);

    if ((sceneTimer > BO_LIGHTOUT)&&(sceneTimer <= BO_MOONPOP))
        Engine.Blit(MoonImage[0], ((Ludens[sceneLudens[1]].posX - 20) >> FIX) - cameraX, (Ludens[sceneLudens[1]].posY >> FIX) - cameraY - (sceneTimer % BO_LIGHTOUT)*2);
    if ((sceneTimer > BO_MOONPOP)&&(sceneTimer < BO_NEWLIGHT))
        Engine.Blit(MoonImage[0], ((Ludens[sceneLudens[1]].posX - 20) >> FIX) - cameraX, (Ludens[sceneLudens[1]].posY >> FIX) - cameraY - (BO_MOONPOP - BO_LIGHTOUT)*2);
    if (sceneTimer > BO_NEWLIGHT)
        Engine.Blit(MoonImage[0], ((Ludens[sceneLudens[1]].posX - 20) >> FIX) - cameraX, (Ludens[sceneLudens[1]].posY >> FIX) - cameraY - (BO_MOONPOP - BO_LIGHTOUT)*2 - (sceneTimer % BO_NEWLIGHT));
}



void CGame::RenderCameraBox(int X, int Y, int W, int H)
{
    Engine.DrawRectangle(0, 0, X - W, Engine.Screen->h, 0, 0, 0);
    Engine.DrawRectangle(X + W, 0, Engine.Screen->w - (X + W), Engine.Screen->h, 0, 0, 0);

    Engine.DrawRectangle(0, 0, Engine.Screen->w, Y - H, 0, 0, 0);
    Engine.DrawRectangle(0, Y + H, Engine.Screen->w, Engine.Screen->h - (Y + H), 0, 0, 0);
}

bool CGame::Hearable(int X, int Y)
{
    if (myLudens < 0)
        return true;

    if ((abs(X - Ludens[myLudens].posX) < HEARABLE) && (abs(Y - Ludens[myLudens].posY) < HEARABLE))
        return true;
    else
        return false;
}

void CGame::MapAction(int mapNum)
{
    switch (mapNum)
    {
    case 1:
        if (Map.backgroundRed == 98)
        {
            Map.SetBackground(107, 82, 120);
        }
        if (mainTickCounter % 1 == 0)
        {
            if (Map.backgroundRed > 99)
                Map.backgroundRed--;
            if (Map.backgroundGreen > 54)
                Map.backgroundGreen--;
            if (Map.backgroundBlue > 20)
                Map.backgroundBlue--;
        }

        hintTimer++;
        if (hintTimer == 120)
            showHint = true;
        break;
    case 9:
        //Map.backgroundBlue = 0;
        if (showHint)
            hintTimer++;
        if (hintTimer == 120)
            showHint = false;
        break;
	case EPISODE_MINES + 2:
        Dialog.x = Dialog.x + (cameraX - cameraOX);
        Dialog.y = Dialog.y + (cameraY - cameraOY);
        switch (dialogStep)
        {
        case 1:
            if (Dialog.count == 0)
            {
				sceneTimer = 0;
                Dialog.RestartDialog();
                Dialog.SetDialog("You've collected all money bags.", DIALOG_VOICE_X , DIALOG_VOICE_Y, 80, sceneTimer, 1);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
            {
                Dialog.SetDialog("So what do you want?", DIALOG_VOICE_X, DIALOG_VOICE_Y, 55, sceneTimer, 1);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
            {
                Dialog.SetDialog("a medal?", DIALOG_VOICE_X, DIALOG_VOICE_Y, 45, sceneTimer, 1);
            }
            break;
		}
		sceneTimer++;
        break;
    case EPISODE_HYPOTHESIS:
        if (mainTickCounter % 1 == 0)
        {
            if (Map.backgroundRed > 45)
                Map.backgroundRed -= 5;
            if (Map.backgroundGreen > 40)
                Map.backgroundGreen -= 5;
            if (Map.backgroundBlue > 35)
                Map.backgroundBlue -= 5;
        }
        Dialog.x = Dialog.x + (cameraX - cameraOX);
        Dialog.y = Dialog.y + (cameraY - cameraOY);
        switch (dialogStep)
        {
        case 1:
            if (Dialog.count == 0)
            {
                Dialog.RestartDialog();
                Dialog.SetDialog("Joseph.", DIALOG_VOICE_X , DIALOG_VOICE_Y, 55, sceneTimer, 1);
                Map.SetBackground(95, 90, 85);
                ShakeCamera(4, 3);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
                Dialog.SetDialog("What? What is that?", DIALOG_HERO_X, DIALOG_HERO_Y, 55, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
            {
                Dialog.SetDialog("Joseph, listen to me.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 65, sceneTimer, 1);
                Map.SetBackground(80, 75, 70);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 3))
                Dialog.SetDialog("Where are you?", DIALOG_HERO_X, DIALOG_HERO_Y, 45, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 4))
            {
                Dialog.SetDialog("I am everywhere right now.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 65, sceneTimer, 1);
                Map.SetBackground(75, 70, 65);
            }
            break;
        case 2:
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 5))
                Dialog.SetDialog("Are you in my head!?", DIALOG_HERO_X, DIALOG_HERO_Y, 45, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 6))
            {
                Dialog.SetDialog("Yes.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 40, sceneTimer, 1);
                Map.SetBackground(75, 70, 65);
            }

            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 7))
                Dialog.SetDialog("What's going on!?", DIALOG_HERO_X, DIALOG_HERO_Y, 40, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 8))
                Dialog.SetDialog("Are you that freaky guy from the coffee shop?", DIALOG_HERO_X, DIALOG_HERO_Y, 70, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 9))
            {
                Dialog.SetDialog("No. That was just an auxilary character", DIALOG_VOICE_X - 30, DIALOG_VOICE_Y, 70, sceneTimer, 1);
                Map.SetBackground(75, 70, 65);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 10))
            {
                Dialog.SetDialog("that has no importance anymore.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 65, sceneTimer, 1);
                Map.SetBackground(50, 45, 40);
            }
            break;
        case 3:
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 11))
            {
                Dialog.SetDialog("Joseph, listen to me.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 50, sceneTimer, 1);
                Map.SetBackground(90, 70, 65);
                ShakeCamera(2, 2);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 12))
            {
                Dialog.SetDialog("I want to tell you about your presence here,", DIALOG_VOICE_X, DIALOG_VOICE_Y, 75, sceneTimer, 1);
                Map.SetBackground(95, 75, 70);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 13))
            {
                Dialog.SetDialog("in this... world.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 70, sceneTimer, 1);
                Map.SetBackground(95, 75, 70);
                ShakeCamera(2, 2);
            }
            break;
        case 4:
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 14))
            {
                Dialog.SetDialog("Your life Joseph,", DIALOG_VOICE_X, DIALOG_VOICE_Y, 80, sceneTimer, 1);
                Map.SetBackground(130, 105, 100);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 15))
            {
                Dialog.SetDialog("your life, is a video game.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 90, sceneTimer, 1);
                Map.SetBackground(195, 165, 160);
                Engine.Sound.PlaySample(3);
                ShakeCamera(8, 4);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 16))
            {
                Dialog.SetDialog("?!", DIALOG_HERO_X, DIALOG_HERO_Y, 50, sceneTimer);
                dialogStep = 5;
                ShakeCamera(8, 3);
            }
            break;
        case 5:
            if (Engine.random(8) == 0)
            {
                Engine.Sound.PlaySample(27);
            }
            int tx = ((Ludens[myLudens].posX )  >> FIX) / TILE_WIDTH;
            int ty = ((Ludens[myLudens].posY >> FIX) + TILE_HEIGHT) / TILE_HEIGHT;

            if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH-1) && (ty < MAP_HEIGHT-1))
                if (Map.getCell(tx, ty) == 0)
                {
                    DeleteTile(tx, ty);
                    AddPart(P_PUFF, (tx*TILE_WIDTH << FIX), (ty*TILE_HEIGHT << FIX));
                }
            tx = ((Ludens[myLudens].posX  >> FIX) + TILE_WIDTH) / TILE_WIDTH;
            ty = ((Ludens[myLudens].posY >> FIX) + TILE_HEIGHT) / TILE_HEIGHT;

            if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH-1) && (ty < MAP_HEIGHT-1))
                if (Map.getCell(tx, ty) == 0)
                {
                    DeleteTile(tx, ty);
                    AddPart(P_PUFF, (tx*TILE_WIDTH << FIX), (ty*TILE_HEIGHT << FIX));
                }
            tx = ((Ludens[myLudens].posX  >> FIX) - TILE_WIDTH) / TILE_WIDTH;
            ty = ((Ludens[myLudens].posY >> FIX) + TILE_HEIGHT) / TILE_HEIGHT;

            if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH-1) && (ty < MAP_HEIGHT-1))
                if (Map.getCell(tx, ty) == 0)
                {
                    DeleteTile(tx, ty);
                    AddPart(P_PUFF, (tx*TILE_WIDTH << FIX), (ty*TILE_HEIGHT << FIX));
                }
            tx = ((Ludens[myLudens].posX  >> FIX) - 2*TILE_WIDTH + Engine.random(3)*TILE_WIDTH) / TILE_WIDTH;
            ty = ((Ludens[myLudens].posY >> FIX) - 2*TILE_HEIGHT + Engine.random(3)*TILE_HEIGHT) / TILE_HEIGHT;

            if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH-1) && (ty < MAP_HEIGHT-1))
                if (Map.getCell(tx, ty) == 0)
                {
                    DeleteTile(tx, ty);
                    AddPart(P_PUFF, (tx*TILE_WIDTH << FIX), (ty*TILE_HEIGHT << FIX));
                }
            Ludens[myLudens].velX = 0;
            break;
        }
        sceneTimer++;
        break;
    case EPISODE_HYPOTHESIS+1:
        if (mainTickCounter % 1 == 0)
        {
            if (Map.backgroundRed > 45)
                Map.backgroundRed -= 5;
            if (Map.backgroundGreen > 40)
                Map.backgroundGreen -= 5;
            if (Map.backgroundBlue > 35)
                Map.backgroundBlue -= 5;
        }
        Dialog.x = Dialog.x + (cameraX - cameraOX);
        Dialog.y = Dialog.y + (cameraY - cameraOY);
        switch (dialogStep)
        {
        case 1:
            if (Dialog.count == 0)
            {
                Dialog.RestartDialog();
                Dialog.SetDialog("You are a computer animated sprite.", DIALOG_VOICE_X + 80 , DIALOG_VOICE_Y, 75, sceneTimer, 1);
                Map.SetBackground(75, 90, 95);
                ShakeCamera(2, 3);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
            {
                Dialog.SetDialog("An artificial character,", DIALOG_VOICE_X, DIALOG_VOICE_Y, 65, sceneTimer, 1);
                Map.SetBackground(70, 75, 80);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
            {
                Dialog.SetDialog("created and existing only in digital form.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 75, sceneTimer, 1);
                Map.SetBackground(70, 75, 80);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 3))
                Dialog.SetDialog("OK, you're nuts.", DIALOG_HERO_X, DIALOG_HERO_Y, 55, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 4))
                Dialog.SetDialog("Get out of my head now.", DIALOG_HERO_X, DIALOG_HERO_Y, 65, sceneTimer);
            break;
        case 2:
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 5))
            {
                Dialog.SetDialog("Joseph. Your entire life is an illusion.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 75, sceneTimer, 1);
                Map.SetBackground(70, 75, 80);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 6))
            {
                Dialog.SetDialog("You exist only when this game is played.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 75, sceneTimer, 1);
                Map.SetBackground(70, 75, 80);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 7))
                Dialog.SetDialog("That's impossible.", DIALOG_HERO_X, DIALOG_HERO_Y, 50, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 8))
                Dialog.SetDialog("I don't remember anyone turning me off.", DIALOG_HERO_X, DIALOG_HERO_Y, 75, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 9))
            {
                Dialog.SetDialog("How could you have a memory of a time when you didn't exist?", DIALOG_VOICE_X - 50, DIALOG_VOICE_Y, 85, sceneTimer, 1);
                Map.SetBackground(80, 75, 80);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 10))
                Dialog.SetDialog("I have memories, years of memories!", DIALOG_HERO_X, DIALOG_HERO_Y, 70, sceneTimer);
            break;
        case 3:
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 11))
            {
                Dialog.SetDialog("Your memories?", DIALOG_VOICE_X, DIALOG_VOICE_Y, 75, sceneTimer, 1);
                Map.SetBackground(75, 85, 77);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 12))
            {
                Dialog.SetDialog("... everything is coded.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 75, sceneTimer, 1);
                Map.SetBackground(85, 85, 77);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 13))
                Dialog.SetDialog("... I am not coded. I know I exist!", DIALOG_HERO_X, DIALOG_HERO_Y, 70, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 14))
            {
                Dialog.SetDialog("How can you prove that?", DIALOG_VOICE_X, DIALOG_VOICE_Y, 70, sceneTimer, 1);
                Map.SetBackground(75, 85, 77);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 15))
                Dialog.SetDialog("How can you disprove that!?", DIALOG_HERO_X, DIALOG_HERO_Y, 70, sceneTimer);
            break;
        case 4:
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 16))
                Dialog.SetDialog("What about my free will?", DIALOG_HERO_X, DIALOG_HERO_Y, 70, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 17))
            {
                Dialog.SetDialog("Your free will?", DIALOG_VOICE_X, DIALOG_VOICE_Y, 55, sceneTimer, 1);
                Map.SetBackground(75, 89, 67);
                ShakeCamera(1, 2);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 18))
            {
                Dialog.SetDialog("How do you know you have free will?", DIALOG_VOICE_X-40, DIALOG_VOICE_Y, 70, sceneTimer, 1);
                Map.SetBackground(75, 89, 67);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 19))
                Dialog.SetDialog("Because I can do whatever I want.", DIALOG_HERO_X, DIALOG_HERO_Y, 70, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 20))
            {
                Dialog.SetDialog("How do you know your actions are not scripted?", DIALOG_VOICE_X, DIALOG_VOICE_Y, 100, sceneTimer, 1);
                Map.SetBackground(80, 85, 90);
            }
            break;
        case 5:
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 21))
                Dialog.SetDialog("Well I have choice...", DIALOG_HERO_X, DIALOG_HERO_Y, 60, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 22))
                Dialog.SetDialog("I have choice of everything.", DIALOG_HERO_X, DIALOG_HERO_Y, 60, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 23))
                Dialog.SetDialog("I'm thinking this up as I'm talking to you.", DIALOG_HERO_X, DIALOG_HERO_Y, 70, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 24))
                Dialog.SetDialog("I can move wherever I like", DIALOG_HERO_X, DIALOG_HERO_Y, 55, sceneTimer);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 25))
                Dialog.SetDialog("and do whatever I want to at the moment.", DIALOG_HERO_X, DIALOG_HERO_Y, 70, sceneTimer);
            break;
        }
        if (dialogStep > 5)
        {
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 26))
            {
                Dialog.SetDialog("Really?", DIALOG_VOICE_X, DIALOG_VOICE_Y, 100, sceneTimer, 1);
                Map.SetBackground(135, 135, 150);
                ShakeCamera(9, 3);
            }
            if (Engine.random(8) == 0)
                Engine.Sound.PlaySample(27);
            int tx = ((Ludens[myLudens].posX )  >> FIX) / TILE_WIDTH;
            int ty = ((Ludens[myLudens].posY >> FIX) + TILE_HEIGHT) / TILE_HEIGHT;

            if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH-1) && (ty < MAP_HEIGHT-1))
                if (Map.getCell(tx, ty) == 0)
                {
                    DeleteTile(tx, ty);
                    AddPart(P_PUFF, (tx*TILE_WIDTH << FIX), (ty*TILE_HEIGHT << FIX));
                }
            tx = ((Ludens[myLudens].posX  >> FIX) + TILE_WIDTH) / TILE_WIDTH;
            ty = ((Ludens[myLudens].posY >> FIX) + TILE_HEIGHT) / TILE_HEIGHT;

            if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH-1) && (ty < MAP_HEIGHT-1))
                if (Map.getCell(tx, ty) == 0)
                {
                    DeleteTile(tx, ty);
                    AddPart(P_PUFF, (tx*TILE_WIDTH << FIX), (ty*TILE_HEIGHT << FIX));
                }
            tx = ((Ludens[myLudens].posX  >> FIX) - TILE_WIDTH) / TILE_WIDTH;
            ty = ((Ludens[myLudens].posY >> FIX) + TILE_HEIGHT) / TILE_HEIGHT;
            Ludens[myLudens].velX = 0;
        }

        sceneTimer++;
        break;
    case EPISODE_HYPOTHESIS+2:
        if (Dialog.count < 30)
        {
            if (Map.backgroundRed < 250)
                Map.backgroundRed += 2;
            if (Map.backgroundGreen < 250)
                Map.backgroundGreen += 2;
            if (Map.backgroundBlue < 250)
                Map.backgroundBlue += 2;
        }
        else
        {
            if (Map.backgroundRed > 4)
                Map.backgroundRed -= 2;
            if (Map.backgroundGreen > 4)
                Map.backgroundGreen -= 2;
            if (Map.backgroundBlue > 4)
                Map.backgroundBlue -= 2;
        }
        if (dialogStep < 3)
        {
            Dialog.x = Dialog.x + (cameraX - cameraOX);
            Dialog.y = Dialog.y + (cameraY - cameraOY);
        }
        switch (dialogStep)
        {
        case 1:
            if (Dialog.count == 0)
            {
                Dialog.RestartDialog();
                Dialog.SetDialog("Joseph.", DIALOG_VOICE_X + 80 , DIALOG_VOICE_Y, 75, sceneTimer, FONT_BBIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 1))
            {
                Dialog.SetDialog("Your entire life was created in someones mind.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 75, sceneTimer, FONT_BBIG);
                Map.SetBackground(230, 235, 240);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 2))
            {
                Dialog.SetDialog("Your presence is only manifested ", DIALOG_VOICE_X, DIALOG_VOICE_Y, 60, sceneTimer, FONT_BBIG);
                Map.SetBackground(230, 235, 240);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 3))
            {
                Dialog.SetDialog("by what the game player can see or hear.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 80, sceneTimer, FONT_BBIG);
                Map.SetBackground(230, 235, 240);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 4))
            {
                Dialog.SetDialog("The choices you make are not your choices.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 80, sceneTimer, FONT_BBIG);
                Map.SetBackground(230, 235, 240);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 5))
            {
                Dialog.SetDialog("What you say is hard-coded,", DIALOG_VOICE_X, DIALOG_VOICE_Y, 70, sceneTimer, FONT_BBIG);
                Map.SetBackground(230, 235, 240);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 6))
            {
                Dialog.SetDialog("you can't even edit it in a text file.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 75, sceneTimer, FONT_BBIG);
                Map.SetBackground(230, 235, 240);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 7))
            {
                Dialog.SetDialog("You are a two dimensional character that lacks", DIALOG_VOICE_X, DIALOG_VOICE_Y, 75, sceneTimer, FONT_BBIG);
                Map.SetBackground(230, 235, 240);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 8))
            {
                Dialog.SetDialog("of everything needed to even pretend to be real.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 80, sceneTimer, FONT_BBIG);
                Map.SetBackground(230, 235, 240);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 9))
            {
                Dialog.SetDialog("You're not even three dimensional.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 80, sceneTimer, FONT_BBIG);
                ShakeCamera(3, 2);
                Map.SetBackground(238, 225, 230);
            }
            break;
        case 2:
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 10))
            {
                Dialog.SetDialog("OK, I may not be 3d.", DIALOG_HERO_X, DIALOG_HERO_Y, 80, sceneTimer, FONT_BSMALL);
                int tx = 1878 / TILE_HEIGHT;
                int ty = 2252 / TILE_WIDTH;
                Map.setCell(tx, ty, 0);
                PlaceModTile(tx - 1, ty);
                PlaceModTile(tx + 1, ty);
                PlaceModTile(tx, ty - 1);
                PlaceModTile(tx, ty + 1);
                Map.setCell(tx, ty-1, 0);
                PlaceModTile(tx - 1, ty);
                PlaceModTile(tx + 1, ty);
                PlaceModTile(tx, ty - 1);
                PlaceModTile(tx, ty + 1);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 11))
                Dialog.SetDialog("I may not have a 'real' life.", DIALOG_HERO_X, DIALOG_HERO_Y, 70, sceneTimer, FONT_BSMALL);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 12))
                Dialog.SetDialog("I may be a poor character in a lousy game.", DIALOG_HERO_X, DIALOG_HERO_Y, 75, sceneTimer, FONT_BSMALL);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 13))
                Dialog.SetDialog("But that is what you think!", DIALOG_HERO_X, DIALOG_HERO_Y, 70, sceneTimer, FONT_BSMALL);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 14))
                Dialog.SetDialog("You can never take away my thoughts", DIALOG_HERO_X, DIALOG_HERO_Y, 70, sceneTimer, FONT_BSMALL);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 15))
                Dialog.SetDialog("and my self-awareness.", DIALOG_HERO_X, DIALOG_HERO_Y, 60, sceneTimer, FONT_BSMALL);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 16))
                Dialog.SetDialog("My dreams and my desires!", DIALOG_HERO_X, DIALOG_HERO_Y, 70, sceneTimer, FONT_BSMALL);
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 17))
            {
                Dialog.SetDialog("Come in here please.", DIALOG_VOICE_X, DIALOG_VOICE_Y, 80, sceneTimer, FONT_BBIG);
                ShakeCamera(3, 2);
                Map.SetBackground(230, 225, 230);
                DeleteTile(2163 / TILE_HEIGHT, 2315 / TILE_WIDTH);
                DeleteTile(2163 / TILE_HEIGHT, 2285 / TILE_WIDTH);
                sceneLudens[0] = AddLudens(HERO, 2858 << FIX, 2315 << FIX);
            }
            break;
        case 3:
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 18))
            {
                Dialog.SetDialog("That is the flaw, you see.", DIALOG_HIM_X, DIALOG_HIM_Y, 90, sceneTimer, FONT_BBIG);
                int tx = 2562 / TILE_HEIGHT;
                int ty = 2310 / TILE_WIDTH;

                Map.setCell(tx, ty, 0);
                PlaceModTile(tx - 1, ty);
                PlaceModTile(tx + 1, ty);
                PlaceModTile(tx, ty - 1);
                PlaceModTile(tx, ty + 1);
                Map.setCell(tx, ty-1, 0);
                PlaceModTile(tx - 1, ty);
                PlaceModTile(tx + 1, ty);
                PlaceModTile(tx, ty - 1);
                PlaceModTile(tx, ty + 1);

                Map.setCell(tx+1, ty-1, 0);
                PlaceModTile(tx + 0, ty - 1);
                PlaceModTile(tx + 2, ty - 1);
                PlaceModTile(tx + 1, ty - 2);
                PlaceModTile(tx + 1, ty + 0);
                Map.setCell(tx+1, ty-0, 0);
                PlaceModTile(tx + 0, ty - 0);
                PlaceModTile(tx + 2, ty - 0);
                PlaceModTile(tx + 1, ty - 1);
                PlaceModTile(tx + 1, ty + 1);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 19))
            {
                Dialog.SetDialog("We can never be 100 percent sure.", DIALOG_HIM_X, DIALOG_HIM_Y, 80, sceneTimer, FONT_BBIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 20))
            {
                Dialog.SetDialog("I must say this,", DIALOG_HIM_X, DIALOG_HIM_Y, 70, sceneTimer, FONT_BBIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 21))
            {
                Dialog.SetDialog("although my message might not be received.", DIALOG_HIM_X, DIALOG_HIM_Y, 75, sceneTimer, FONT_BBIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 22))
            {
                Dialog.SetDialog("We have not created a test", DIALOG_HIM_X, DIALOG_HIM_Y, 85, sceneTimer, FONT_BBIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 23))
            {
                Dialog.SetDialog("to determine if an artificial being is self-aware.", DIALOG_HIM_X, DIALOG_HIM_Y, 85, sceneTimer, FONT_BBIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 24))
            {
                Dialog.SetDialog("Or even check if a real one is.", DIALOG_HIM_X, DIALOG_HIM_Y, 85, sceneTimer, FONT_BBIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 25))
            {
                Dialog.SetDialog("That is why you were created.", DIALOG_HIM_X, DIALOG_HIM_Y, 90, sceneTimer, FONT_BBIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 26))
            {
                Dialog.SetDialog("That is why you are in this game", DIALOG_HIM_X, DIALOG_HIM_Y, 90, sceneTimer, FONT_BBIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 27))
            {
                Dialog.SetDialog("That is why I'm speaking to you.", DIALOG_HIM_X, DIALOG_HIM_Y, 90, sceneTimer, FONT_BBIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 28))
            {
                Dialog.SetDialog("You are the greatest mystery of all.", DIALOG_HIM_X, DIALOG_HIM_Y, 90, sceneTimer, FONT_BBIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 29))
            {
                Dialog.SetDialog("Ever.", DIALOG_HIM_X, DIALOG_HIM_Y, 130, sceneTimer, FONT_BBIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 30))
            {
                Dialog.SetDialog("After we have accomplished everything,", DIALOG_HIM_X, DIALOG_HIM_Y, 95, sceneTimer, FONT_BIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 31))
            {
                Dialog.SetDialog("it will be the last unknown in the equation.", DIALOG_HIM_X, DIALOG_HIM_Y, 95, sceneTimer, FONT_BIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 32))
            {
                Dialog.SetDialog("We will never know if you have thoughts.", DIALOG_HIM_X, DIALOG_HIM_Y, 95, sceneTimer, FONT_BIG);
                Map.SetBackground(100, 85, 80);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 33))
            {
                Dialog.SetDialog("We will never know if you have dreams.", DIALOG_HIM_X, DIALOG_HIM_Y, 95, sceneTimer, FONT_BIG);
                Map.SetBackground(100, 85, 80);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 34))
            {
                Dialog.SetDialog("You are a supreme being, Joseph.", DIALOG_HIM_X, DIALOG_HIM_Y, 95, sceneTimer, FONT_BIG);
                Map.SetBackground(130, 105, 100);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 35))
            {
                Dialog.SetDialog("You are invincible,", DIALOG_HIM_X, DIALOG_HIM_Y, 70, sceneTimer, FONT_BIG);
                Map.SetBackground(140, 115, 110);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 36))
            {
                Dialog.SetDialog("since you don't live.", DIALOG_HIM_X, DIALOG_HIM_Y, 80, sceneTimer, FONT_BIG);
                Map.SetBackground(140, 115, 110);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 37))
            {
                Dialog.SetDialog("You are infinite,", DIALOG_HIM_X, DIALOG_HIM_Y, 70, sceneTimer, FONT_BIG);
                Map.SetBackground(150, 125, 120);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 38))
            {
                Dialog.SetDialog("since time does not exist for you.", DIALOG_HIM_X, DIALOG_HIM_Y, 80, sceneTimer, FONT_BIG);
                Map.SetBackground(150, 125, 120);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 39))
            {
                Dialog.SetDialog("You are nothing,", DIALOG_HIM_X, DIALOG_HIM_Y, 70, sceneTimer, FONT_BIG);
                Map.SetBackground(160, 135, 130);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 40))
            {
                Dialog.SetDialog("since that is what illusions are.", DIALOG_HIM_X, DIALOG_HIM_Y, 80, sceneTimer, FONT_BIG);
                Map.SetBackground(160, 135, 130);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 41))
            {
                Dialog.SetDialog("You are everything that ever was and will be,", DIALOG_HIM_X, DIALOG_HIM_Y, 80, sceneTimer, FONT_BIG);
                Map.SetBackground(160, 135, 130);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 42))
            {
                Dialog.SetDialog("since illusions are eternal.", DIALOG_HIM_X, DIALOG_HIM_Y, 80, sceneTimer, FONT_BIG);
                Map.SetBackground(170, 155, 150);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 43))
            {
                Dialog.SetDialog("Joseph,", DIALOG_HIM_X, DIALOG_HIM_Y, 90, sceneTimer, FONT_BIG);
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 44))
            {
                Dialog.SetDialog("You are GOD.", DIALOG_HIM_X, DIALOG_HIM_Y, 105, sceneTimer, FONT_BIG);
                Map.SetBackground(230, 150, 160);
            }
            if ((Dialog.count == 45)&&(sceneTimer % 2 == 0))
            {
                ShakeCamera(2, 1);
                Map.SetBackground(150+Engine.random(40), 115+Engine.random(20), 120+Engine.random(20));
            }
            if ((sceneTimer == Dialog.lastTime + Dialog.duration)&&(Dialog.count == 45))
            {
                Dialog.SetDialog("You are GOD.", DIALOG_HIM_X, DIALOG_HIM_Y, 105, sceneTimer, FONT_BIG);
                Map.SetBackground(180, 185, 230);
                MyLudensDie();

            }
            break;
        }

        sceneTimer++;
        break;
    case ZORTHPLAY_MAP:
        //Map.backgroundRed = 48;
        if (Map.backgroundRed == 48)
        {
            Map.backgroundRed = 152;
            Map.backgroundGreen = 152;
            Map.backgroundBlue = 152;
        }
        if ((Ludens[myLudens].posY > Ludens[myLudens].oldY)&&(Ludens[myLudens].posY > 440 << FIX)&&(mainTickCounter % 4 == 0))
        {
            if (Map.backgroundRed > 49)
                Map.backgroundRed--;
            if (Map.backgroundGreen > 53)
                Map.backgroundGreen--;
            if (Map.backgroundBlue > 43)
                Map.backgroundBlue--;
        }
		break;
	case 26:
        for (int i=0; i<CREDITS_NUM; i++)
            if (CreditsY[i] > 1*MENU_STARTY + i*MENU_SPACE)
                CreditsY[i]--;
		break;
    default:
        break;
    }
}