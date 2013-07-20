#ifndef GAME_H
#define GAME_H

#include "preheader.h"
#include "engine.h"
#include "tilemap.h"
#include "globals.h"
#include "ludens.h"
#include "part.h"
#include "cutscenes.h"

static char *Levels[] =
    { "R intro",
      "Episode I : Volcano", "The great comeback", "Don't forget the trampoline", "Run, Joseph run", "Cutscene 'Baloonman'",
      "Episode II : Swamp", "Little trouble", "Saggy balls", "Roller-coaster", "Cutscene 'Gustav'",
      "Episode III : Dream", ".not done", ".not done", ".not done",
	  "Episode IV : Disney Land", "Miami Vice", ".not done", 
	  "Episode V : Mines", "Strangler prison", "Dig dug",
      "Episode VI : The Hypothesis", "Forget about Joseph", "The End",
      "Episode VII : The Wizard", "Eternal Joseph", "They captured you and placed in a prison cell with an old man. The end."
    };
//"The Wizard"

class CGame
{
    bool isRunning;

private:
    int cameraX, cameraY, cameraVX, cameraVY, cameraOX, cameraOY;

public:
    CEngine Engine;

    CTileMap Map;

    CLudens Ludens[MAX_LUDENS];

    CPart Part[MAX_PART];

    CSprite *DrawList[MAX_SPRITES];

    int myLudens;

    // SBITMAPS
    SBITMAP *VolcanoImage, *HomeImage, *SwampImage,
		*OublietteImage, *EndImage, *PlumImage, *BlackImage, 
		*MinesImage;
    SBITMAP *HeroImage, *HeroImageMirror;
    SBITMAP *TrackerImage, *TrackerImageMirror;
    SBITMAP *CrabImage, *CrabImageMirror;
    SBITMAP *BunnyImage;
    SBITMAP *LightImage;
    SBITMAP *ExitImage;
    SBITMAP *HexImage;
    SBITMAP *AshImage, *DustImage, *RainImage, *FlowImage, *SandImage, *LeafsImage, *JetsImage, *ExplosionImage;
    SBITMAP *PuffImage;
    SBITMAP *MiniImage;
    SBITMAP *KodamaImage, *KodamaImageMirror;
    SBITMAP *HutImage;
    SBITMAP *StranglerImage, *StranglerImageMirror;
    SBITMAP *BallImage, *BallImageMirror;
    SBITMAP *DoorImage;
    SBITMAP *SwitchImage;
	SBITMAP *Switch2Image;
    SBITMAP *ElevatorImage;
    SBITMAP *ZorthImage, *ZorthImageMirror;
    SBITMAP *PlazmaImage;
    SBITMAP *GrenadeImage;
    SBITMAP *SpringImage;
    SBITMAP *VSpringImage;
    SBITMAP *RazorImage, *RazorImageMirror;
    SBITMAP *BlockImage;
    SBITMAP *RabbitImage, *RabbitImageMirror;
    SBITMAP *PlatformImage;
    SBITMAP *HoverImage, *HoverImageMirror;
    SBITMAP *LineImage;
    SBITMAP *HideImage;
    SBITMAP *BikeImage, *BikeImageMirror;
    SBITMAP *DestructImage;
    SBITMAP *SecretImage;
    SBITMAP *GustavImage;
    SBITMAP *DomeImage;
    SBITMAP *WaterImage, *WaterImageMirror;
    SBITMAP *RiddlerImage;
    SBITMAP *DudeImage;
    SBITMAP *FishmanImage;
    SBITMAP *TerminalImage;
    SBITMAP *MoleImage;
    SBITMAP *BagImage;
	SBITMAP *BloodImage;
	SBITMAP *OldmanImage;
	SBITMAP *ChangerImage;

    SBITMAP *ThunderImage;
    SBITMAP *BaloonManImage;
    SBITMAP *TravoltaBackImage;
    SBITMAP *BananaImage;
    SBITMAP *StrangerImage;
    SBITMAP *MoonImage;
    SBITMAP *CloudsImage;
    SBITMAP *GoodCoImage;
    SBITMAP *InterruptImage;

    SBITMAP MiniMap;

    char *RootDirectory;

	bool debugMode;

    //{********** NUMBER27's TIMING ROUTINES ***********}
    int TimeInMil, TimeInMilLast;
    int TimePassed;
    int Seconds, SecondsLast;
    int Ticks,TicksPerSecond;
    int Frames, FramesPerSecond, TickTime, TickTimeLast;
    int GoalTicks;
    int	frc, fps, frp;

    int mainTickCounter;

    bool editMode;
    int debugLudens;

    bool miniMap;
    int viewX, viewY;
    int shakeCounter, shakeMagnitude, shakeNorm;

    int mapNum, level;
    char *mapName, *mapFileName;

    bool showMenu;
    bool canMenuPos;
    int menuLayer, menuPos;
    int CreditsY[CREDITS_NUM];
    bool setKeys;
    int settingKey;
    int cursorY;

    char *currentMODfile;
    int currentMusic;
    int MusicFadeOut;

    char *centerCaption;
    int centerCaptionTimer;

    bool cutScene;
    int sceneTimer;
    CDialogText Dialog;
    int lastDialogTime;
    bool startSecret;
    int oldSecretX, oldSecretY;
    int sceneLudens[2];
    int oldT;
    int pick;

	int bagsPicked;

    int lastLudens, lastLastLudens;
    int editLudens, editLudensNum;
    char *editLudensName;
    bool canPress;

    int startLudens;

    bool showHint;
    char *hint[15];
    int hintTimer;

    int musicCheck;
    int musicStepCount, oldMusicStep;
    int musicStep;
    bool useMusicCheck;

    int interruptCount, interruptTimer, interruptNum;

    int dialogStep;

    bool choiceMenu;
    char *choiceText[3];

	bool usingTerminal;
	int terminalNum;
    int terminalLayer, terminalPos;
    char **terminalText;
	int terminalTextLines, terminalTextPos;


    /////////////////////////////////////////

    void StartGame(char *arg);

    void QuitGame();

    int  InitGame();

    void ManageKeys();

    void Number27Timing();

    void MainGameLoop();

    void RenderFrame();

    void ShakeCamera(int time, int magnitude);

    void UpdateCamera(int num);

    int  AddLudens(int style, int newPosX, int newPosY, int newId = -1);

    int  AddPart(int style, int posX, int posY);

    void LudensResolveDependencies();

    void TestMapCollision(int sX, int sY, int *r);

    void PlaceModTile(int tx, int ty);

    void EditTick(int num);

    void LudensTick(int num);

    int  ClosestStyleLudens(int m, int style, int style2, int side = 0);

    void LudensAttach(int num, int who, int radiusScale = 1, int centerY = 0);

    int  LudensCanGo(int num, int direction, bool fallCheck, int radiusScale = 2);

    int  LudensSee(int m, int style, int sightx, int sighty);

    void LudensAI(int num);

    int  LudensCollideOne(int m, int j);

    int  LudensCollide(int m, int style, int &any);

    void LudensPush(int num, int style, int direction, bool move = true);

    bool LudensPhysics(int num);

    void SpawnParts();

    void PartTick(int num);

    void SpriteDraw(CSprite &Sprite);

    void DrawTileMap(int cX, int cY);

    char *filePlusDir(char *file);

    char *mapFile(char *file);

    void SortDrawList();

    int  LoadTileMap(char *fileName);

    int  SaveTileMap(char *fileName);

    void NextMap();

    void MyLudensDie();

    int  LoadGame();

    int  SaveGame();

    bool Menu();

    void DrawMenu();

    void LoadDefaultConfig(ConfigHeader &cfg);

    int  DecideMusic();

    void DeleteTile(int tx, int ty);

    void StartCutScene();

    void ProcessCutScene(int mapNum);

    void RenderCutScene(int mapNum);
    void RenderAfterCutScene(int mapNum);

    void CutScene_Intro();
    void RenderCutScene_Intro();
    void CutScene_Travolta();
    void RenderCutScene_Travolta();
    void CutScene_BaloonMan();
    void RenderCutScene_BaloonMan();
    void CutScene_Boat();
    void RenderCutScene_Boat();

    void RenderCameraBox(int X, int Y, int W, int H);

    bool Hearable(int X, int Y);

    void MapAction(int mapNum);

    void ResetMusicCheck();

	bool TerminalMenu(int map);
    void DrawTerminalMenu(int map);
	void LoadTerminalText(char* filename);
	void DrawTerminalText();
};


#define OLDMAN_LINES_NUM 50
static char *OldmanLines[] =
    { 
"Oooh... I miss Martha" ,
"Go away, go away, damn hobbits", 
"I wonder how my daughter, Jango Fett is doing", 
"Ooohh, aaaahh" ,
"...and then they keep banging about my bills",
"Damn refrigerators! Stop the buzz!!!" ,
"Hmm my socks smell funny" ,
"Got a bong?" ,
"Stop! Hammer time!" ,
"I think that Celine Dion is pretty hot." ,
"The Monkees was helluva good band",
"Hmm did The Animals release that new album yet?" ,
"They should vote for Nixon" ,
"Damn The Flintstones are so funny" ,
"Stop it! I hate it when you lick my shoes" ,
"Rudolf the red reindeer is gay" ,
"I hate you cause you're all fuckin' same",
"You can be gay all day back home but stay away from my kids!",
"Captain planet has a cool haircut" ,
"It's funny because it's true" ,
"Fear is the path to the dark side" ,
"Damn spoiled brats, listening to the Beatles or some other hellish music." ,
"That led zepellin dude is kinda lame",
"What's with the land of the ice and snow?",
"There was my house in New Orleans, they call it... *cough* *cough*",
"I once had a red bicycle. It was red.",
"When I was a child... It was different.",
"I don't wanna talk anymore",
"Your lips move but I can't hear what you're saying",
"And then he said, can you show me where it hurts?",
"I got elastic bands keepin my shoes on.",
"I got thirteen channels of shit on the T.V. to choose from",
"Why did I do it!?",
"Ladybird, ladybird...",
"I met Vanilli one, nice chap. Not like the other one, he was a bastard.",
"Want to throw some peanuts with me?",
"Once a squirrel bit off my nuts.",
"Why did I kill you!?",
"I want to ride my bicycle, I want to ride my bike!",
"My grandfather was a mountain climber that lived in the bottom of the ocean.",
"Have you met my son? Oh... you don't like queers eh?",
"I kind of fancy that new James Bond, George Lazenby is it?",
"I pooped my pants.",
"Odd little fellow, are you.",
"Never had any children. Dear old Martha was just too ugly.",
"I should've hid his body better.",
"Are you the one?",
"They took our jobs!",
"And then he said 'that's not my penis!'. HAhahahaa.",
"Your welcome."
    };

#endif
