#define DEFAULT_GOALTICKS 24

#define DEBUG debugMode

#define MAX_LUDENS 128
#define MAX_PART 64
#define MAX_SPRITES MAX_LUDENS + MAX_PART
#define MAX_ANIMS 30

#define CAMERA_SPEED 4

#define FIX 8

#define LEFT -1
#define RIGHT 1
#define UP -2
#define DOWN 2

#define ANIM_DEFAULT 0

#define UP_PRESSED 2
#define DOWN_PRESSED 64
#define LEFT_PRESSED 4
#define RIGHT_PRESSED 32
#define FIRE_PRESSED 256
#define GAME_A_PRESSED 512
#define GAME_B_PRESSED 1024
#define GAME_C_PRESSED 2048
#define GAME_D_PRESSED 4096

#define MAX_POSARCHIVE 50

#define MAP_ANIMSPEED 3

#define COL_STEPS 16

#define DEFAULT_LIVES 3

#define VIEW_MAX 480

#define XORVALUE 11

#define LUDENS_IDLE_TIME 34
#define LUDENS_IDLE_TIME2 140

#define MENU_STARTX 10
#define MENU_STARTY 24
#define MENU_SPACE 20
#define CREDITS_NUM 22

#define SETKEYS_WAIT 500

#define HOME_SET 0
#define VOLCANO_SET 1
#define SWAMP_SET 2
#define OUBLIETTE_SET 3
#define PLUM_SET 4
#define BLACK_SET 5
#define END_SET 6
#define MINES_SET 7

#define CENTERCAPTION_TIME 85

#define CAMERABOX_SIZEX 250
#define CAMERABOX_SIZEY 260

#define HEARABLE (400 << FIX)

// EPISODE MAP NUMS
#define EPISODE_MINES 18
#define EPISODE_HYPOTHESIS 21

#define ZORTHPLAY_MAP 25
#define ZORTHEND_MAP 26

#define TERMINAL_STARTX 150
#define TERMINAL_STARTY 65
#define TERMINAL_TEXT_SPACE 15
#define TERMINAL_TEXT_LENGTH 88
#define TERMINAL_TEXT_LINES 9
#define TERMINAL_6_1 ( (map == EPISODE_MINES)&&(terminalNum == 15) )
#define TERMINAL_6_2a ( (map == EPISODE_MINES+2)&&(terminalNum == 1) )
#define TERMINAL_6_2b ( (map == EPISODE_MINES+2)&&(terminalNum == 30) )
#define TERMINAL_6_3a ( (map == EPISODE_MINES+1)&&(terminalNum == 10) )
#define TERMINAL_6_3b ( (map == EPISODE_MINES+1)&&(terminalNum == 14) )
#define TERMINAL_6_3c ( (map == EPISODE_MINES+1)&&(terminalNum == 35) )

