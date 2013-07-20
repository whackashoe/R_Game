#ifndef CUTSCENES_H
#define CUTSCENES_H
#define DIALOG_Y 20
#define DIALOG_HERO_X (Ludens[myLudens].posX >> FIX)
#define DIALOG_HERO_Y ((Ludens[myLudens].posY >> FIX) - DIALOG_Y)
#define DIALOG_RIDDLER_X (Ludens[num].posX >> FIX)
#define DIALOG_RIDDLER_Y ((Ludens[num].posY >> FIX) - DIALOG_Y)
#define DIALOG_VOICE_X ((Ludens[myLudens].posX >> FIX) - 50 + Engine.random(100))
#define DIALOG_VOICE_Y ((Ludens[myLudens].posY >> FIX) - 200 + Engine.random(100))
#define DIALOG_HIM_X (Ludens[sceneLudens[0]].posX >> FIX)
#define DIALOG_HIM_Y ((Ludens[sceneLudens[0]].posY >> FIX) - 80)
#define FONT_SMALL 0
#define FONT_BIG 1
#define FONT_BSMALL 2
#define FONT_BBIG 3
#define THUNDER_FRAMES 1
#define BALOONMAN_FRAMES 2
#define TRAVOLTABACK_FRAMES 3
#define BANANA_FRAMES 1
#define STRANGER_FRAMES 1
#define MOON_FRAMES 1
#define CLOUDS_FRAMES 3
#define GOODCO_FRAMES 1
#define INTERRUPT_FRAMES 1
#define OPENCURTAIN 24
// INTRO
#define INTRO_STARTCREDITS 160
#define INTRO_CREDITSX (cameraX + 400)
#define INTRO_CREDITSY (cameraY + 300)
#define INTRO_ENDSCROLL 1741
#define INTRO_STARTNARRATE (INTRO_ENDSCROLL + 20)
#define INTRO_NARRATEX (cameraX + 360)
#define INTRO_NARRATEY (cameraY + 520)
#define INTRO_SHOUTX (cameraX + 360)
#define INTRO_SHOUTY (cameraY + 370)
#define INTRO_SHOUT2X (cameraX + 395)
#define INTRO_SHOUT2Y (cameraY + 415)
#define INTRO_STARTRUN (INTRO_STARTNARRATE + 1430)
#define INTRO_JOSEPHX 555
#define INTRO_JOSEPHY 2470
#define INTRO_BUNNYAPPEAR (INTRO_STARTRUN + 40)
#define INTRO_RABBITX 725
#define INTRO_RABBITY 2480
#define INTRO_BUNNYRUN (INTRO_BUNNYAPPEAR + 20)
#define INTRO_FALL (INTRO_BUNNYRUN + 236)
#define INTRO_STARTRAIN (INTRO_FALL + 80)
#define INTRO_THUNDER (INTRO_FALL + 314)
#define INTRO_END (INTRO_FALL + 680)

// TRAVOLTA
#define TV_BACKX 1555
#define TV_BACKY 295
#define TV_STARTDANCE 1840
#define TV_DIALOGSTART 130
#define TV_BANANADIALOGSTART 2150
#define TV_DANCEEND 2310
#define TV_TRAVOLTAX (DIALOG_HERO_X + 85)
#define TV_TRAVOLTAY (DIALOG_HERO_Y - 20)
#define TV_BANANAX (DIALOG_HERO_X - 5)
#define TV_BANANAY (DIALOG_HERO_Y - 60)
#define TV_END 2340
// BALOONMAN
#define BM_BALOONMANX 1516
#define BM_BALOONMANY 1922
#define BM_HEROSTOP 89
#define BM_MANAPPEAR BM_HEROSTOP + 55
#define BM_DIALOGSTART BM_MANAPPEAR + 40
#define BM_DISAPPEAR BM_DIALOGSTART + 1426
#define BM_END BM_DISAPPEAR + 55
// BOAT
#define BO_MANX 1154
#define BO_MANY 1550
#define BO_TURN 20
#define BO_MANDIALOG BO_TURN + 20
#define BO_STARTHERO BO_MANDIALOG + 1450
#define BO_STARTRUN BO_STARTHERO + 40
#define BO_STARTCHASE BO_STARTRUN + 30
#define BO_FALL BO_STARTCHASE + 50
#define BO_FALL2 BO_FALL + 55
#define BO_RUNRIGHT BO_FALL2 + 20
#define BO_STOPRUNRIGHT BO_RUNRIGHT + 20
#define BO_STARTMIMETALK BO_STOPRUNRIGHT + 15
#define BO_MIMEX 565
#define BO_MIMEY 2143
#define BO_JUMPINBOAT BO_STARTMIMETALK + 890
#define BO_STOPJUMPINBOAT BO_JUMPINBOAT + 5
#define BO_LIGHTOUT (BO_STOPJUMPINBOAT + 550)
#define BO_MOONPOP (BO_LIGHTOUT + 25)
#define BO_SWIM (BO_MOONPOP + 70)
#define BO_KARAOKEX 565
#define BO_KARAOKEY (BO_MIMEY + 75)
#define BO_NEWLIGHT (BO_MOONPOP + 1638)
#define BO_GOAGAIN (BO_NEWLIGHT + 560)
#define BO_ENDPARTSONG (BO_MOONPOP + 3570)
#define BO_END 7600
//BO_STOPJUMPINBOAT + 550 //(BO_LIGHTOUT + 25)
class CDialogText
{
public:
    char *text;
    int x, y;
    int time, lastTime, allTime;
    int count, duration;
    int font;
    void SetDialog(char *newText, int newX, int newY, int newTime, int newLastTime, int newFont = 0);
    void RestartDialog();
};
#endif