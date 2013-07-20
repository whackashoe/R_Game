// R source by Michal Marcinkowski
// You are free to do whatever you like with it
// questions? e-mail: michal.marcinkowski@gmail.com

#include "preheader.h"
#include "game.h"

void CGame::StartGame(char *arg)
{
    int systemState, gameState;

    RootDirectory = arg;

    isRunning = false;

    LoadDefaultConfig(Engine.Config);
    LoadGame();

    systemState = Engine.InitSystem();

    gameState = InitGame();

    if ((gameState>0)&&(systemState>0))
        isRunning = true;

    MainGameLoop();

    QuitGame();
}

void CGame::QuitGame()
{
    int i;

    delete [] RootDirectory;

    // free surfaces
    for (i=0; i<VOLCANO_FRAMES; i++)
        Engine.FreeBitmap(VolcanoImage[i]);
    for (i=0; i<VOLCANO_FRAMES; i++)
        Engine.FreeBitmap(HomeImage[i]);
    for (i=0; i<SWAMP_FRAMES; i++)
        Engine.FreeBitmap(SwampImage[i]);
    for (i=0; i<VOLCANO_FRAMES; i++)
        Engine.FreeBitmap(OublietteImage[i]);
    for (i=0; i<VOLCANO_FRAMES; i++)
        Engine.FreeBitmap(EndImage[i]);
    for (i=0; i<VOLCANO_FRAMES; i++)
        Engine.FreeBitmap(PlumImage[i]);
    for (i=0; i<VOLCANO_FRAMES; i++)
        Engine.FreeBitmap(BlackImage[i]);
    for (i=0; i<SWAMP_FRAMES; i++)
        Engine.FreeBitmap(MinesImage[i]);
    for (i=0; i<HERO_FRAMES; i++)
    {
        Engine.FreeBitmap(HeroImage[i]);
        Engine.FreeBitmap(HeroImageMirror[i]);
    }
    for (i=0; i<TRACKER_FRAMES; i++)
    {
        Engine.FreeBitmap(TrackerImage[i]);
        Engine.FreeBitmap(TrackerImageMirror[i]);
    }
    for (i=0; i<CRAB_FRAMES; i++)
    {
        Engine.FreeBitmap(CrabImage[i]);
        Engine.FreeBitmap(CrabImageMirror[i]);
    }
    for (i=0; i<KODAMA_FRAMES; i++)
    {
        Engine.FreeBitmap(KodamaImage[i]);
        Engine.FreeBitmap(KodamaImageMirror[i]);
    }
    for (i=0; i<LIGHT_FRAMES; i++)
        Engine.FreeBitmap(LightImage[i]);
    for (i=0; i<BUNNY_FRAMES; i++)
        Engine.FreeBitmap(BunnyImage[i]);
    for (i=0; i<EXIT_FRAMES; i++)
        Engine.FreeBitmap(ExitImage[i]);
    for (i=0; i<HEX_FRAMES; i++)
        Engine.FreeBitmap(HexImage[i]);
    for (i=0; i<ASH_FRAMES; i++)
        Engine.FreeBitmap(AshImage[i]);
    for (i=0; i<DUST_FRAMES; i++)
        Engine.FreeBitmap(DustImage[i]);
    for (i=0; i<FLOW_FRAMES; i++)
        Engine.FreeBitmap(FlowImage[i]);
    for (i=0; i<RAIN_FRAMES; i++)
        Engine.FreeBitmap(RainImage[i]);
    for (i=0; i<MINI_FRAMES; i++)
        Engine.FreeBitmap(MiniImage[i]);
    for (i=0; i<THUNDER_FRAMES; i++)
        Engine.FreeBitmap(ThunderImage[i]);
    for (i=0; i<HUT_FRAMES; i++)
        Engine.FreeBitmap(HutImage[i]);
    for (i=0; i<STRANGLER_FRAMES; i++)
    {
        Engine.FreeBitmap(StranglerImage[i]);
        Engine.FreeBitmap(StranglerImageMirror[i]);
    }
    for (i=0; i<BALL_FRAMES; i++)
    {
        Engine.FreeBitmap(BallImage[i]);
        Engine.FreeBitmap(BallImageMirror[i]);
    }
    for (i=0; i<DOOR_FRAMES; i++)
        Engine.FreeBitmap(DoorImage[i]);
    for (i=0; i<SWITCH_FRAMES; i++)
        Engine.FreeBitmap(SwitchImage[i]);
    for (i=0; i<SWITCH2_FRAMES; i++)
        Engine.FreeBitmap(Switch2Image[i]);
    for (i=0; i<ELEVATOR_FRAMES; i++)
        Engine.FreeBitmap(ElevatorImage[i]);
    for (i=0; i<ZORTH_FRAMES; i++)
    {
        Engine.FreeBitmap(ZorthImage[i]);
        Engine.FreeBitmap(ZorthImageMirror[i]);
    }
    for (i=0; i<PLAZMA_FRAMES; i++)
        Engine.FreeBitmap(PlazmaImage[i]);
    for (i=0; i<SPRING_FRAMES; i++)
        Engine.FreeBitmap(SpringImage[i]);
    for (i=0; i<VSPRING_FRAMES; i++)
        Engine.FreeBitmap(VSpringImage[i]);
    for (i=0; i<GRENADE_FRAMES; i++)
        Engine.FreeBitmap(GrenadeImage[i]);
    for (i=0; i<RAZOR_FRAMES; i++)
    {
        Engine.FreeBitmap(RazorImage[i]);
        Engine.FreeBitmap(RazorImageMirror[i]);
    }
    for (i=0; i<BLOCK_FRAMES; i++)
        Engine.FreeBitmap(BlockImage[i]);
    for (i=0; i<BALOONMAN_FRAMES; i++)
        Engine.FreeBitmap(BaloonManImage[i]);
    for (i=0; i<RABBIT_FRAMES; i++)
    {
        Engine.FreeBitmap(RabbitImage[i]);
        Engine.FreeBitmap(RabbitImageMirror[i]);
    }
    for (i=0; i<JETS_FRAMES; i++)
        Engine.FreeBitmap(JetsImage[i]);
    for (i=0; i<EXPLOSION_FRAMES; i++)
        Engine.FreeBitmap(ExplosionImage[i]);
    for (i=0; i<PUFF_FRAMES; i++)
        Engine.FreeBitmap(PuffImage[i]);
    for (i=0; i<PLATFORM_FRAMES; i++)
        Engine.FreeBitmap(PlatformImage[i]);
    for (i=0; i<HOVER_FRAMES; i++)
    {
        Engine.FreeBitmap(HoverImage[i]);
        Engine.FreeBitmap(HoverImageMirror[i]);
    }
    for (i=0; i<LINE_FRAMES; i++)
        Engine.FreeBitmap(LineImage[i]);
    for (i=0; i<HIDE_FRAMES; i++)
        Engine.FreeBitmap(HideImage[i]);
    for (i=0; i<BIKE_FRAMES; i++)
    {
        Engine.FreeBitmap(BikeImage[i]);
        Engine.FreeBitmap(BikeImageMirror[i]);
    }
    for (i=0; i<DESTRUCT_FRAMES; i++)
        Engine.FreeBitmap(DestructImage[i]);
    for (i=0; i<SECRET_FRAMES; i++)
        Engine.FreeBitmap(SecretImage[i]);
    for (i=0; i<TRAVOLTABACK_FRAMES; i++)
        Engine.FreeBitmap(TravoltaBackImage[i]);
    for (i=0; i<BANANA_FRAMES; i++)
        Engine.FreeBitmap(BananaImage[i]);
    for (i=0; i<GUSTAV_FRAMES; i++)
        Engine.FreeBitmap(GustavImage[i]);
    for (i=0; i<STRANGER_FRAMES; i++)
        Engine.FreeBitmap(StrangerImage[i]);
    for (i=0; i<MOON_FRAMES; i++)
        Engine.FreeBitmap(MoonImage[i]);
    for (i=0; i<DOME_FRAMES; i++)
        Engine.FreeBitmap(DomeImage[i]);
    for (i=0; i<WATER_FRAMES; i++)
    {
        Engine.FreeBitmap(WaterImage[i]);
        Engine.FreeBitmap(WaterImageMirror[i]);
    }
    for (i=0; i<CLOUDS_FRAMES; i++)
        Engine.FreeBitmap(CloudsImage[i]);
    for (i=0; i<GOODCO_FRAMES; i++)
        Engine.FreeBitmap(GoodCoImage[i]);
    for (i=0; i<INTERRUPT_FRAMES; i++)
        Engine.FreeBitmap(InterruptImage[i]);
    for (i=0; i<RIDDLER_FRAMES; i++)
        Engine.FreeBitmap(RiddlerImage[i]);
    for (i=0; i<FISHMAN_FRAMES; i++)
        Engine.FreeBitmap(FishmanImage[i]);
    for (i=0; i<DUDE_FRAMES; i++)
        Engine.FreeBitmap(DudeImage[i]);
    for (i=0; i<TERMINAL_FRAMES; i++)
        Engine.FreeBitmap(TerminalImage[i]);
    for (i=0; i<MOLE_FRAMES; i++)
        Engine.FreeBitmap(MoleImage[i]);
    for (i=0; i<BAG_FRAMES; i++)
        Engine.FreeBitmap(BagImage[i]);
    for (i=0; i<BLOOD_FRAMES; i++)
        Engine.FreeBitmap(BloodImage[i]);
    for (i=0; i<OLDMAN_FRAMES; i++)
        Engine.FreeBitmap(OldmanImage[i]);
    for (i=0; i<CHANGER_FRAMES; i++)
        Engine.FreeBitmap(ChangerImage[i]);

    Engine.FreeBitmap(MiniMap);

    Engine.ShutSystem();
}

int CGame::InitGame()
{
    int i;

	debugMode = 0;

    // Timing variables
    GoalTicks = DEFAULT_GOALTICKS;
    TimeInMil = 0;
    TimeInMilLast = 0;
    TimePassed = 0;
    Seconds = 0;
    SecondsLast = 0;
    Ticks = 0;
    TicksPerSecond = 0;
    Frames = 0;
    FramesPerSecond = 0;
    TickTime = 0;
    TickTimeLast = 0;
    frc = fps = frp = 0;

    // load fonts
    Engine.font = initFont(filePlusDir("f/smallfont"));
    Engine.bigfont = initFont(filePlusDir("f/bigfont"));
    Engine.blackfont = initFont(filePlusDir("f/smallfont"), 0, 0, 0);
    Engine.bigblackfont = initFont(filePlusDir("f/bigfont"), 0, 0, 0);
    Engine.terminalfont = initFont(filePlusDir("f/terminalfont"), 30, 230, 210);

    // load sounds
    Engine.Sound.samples[0] = Engine.LoadSound(filePlusDir("s/burn.wav"));
    Engine.Sound.samples[1] = Engine.LoadSound(filePlusDir("s/glight.wav"));
    Engine.Sound.samples[2] = Engine.LoadSound(filePlusDir("s/hexlight.wav"));
    Engine.Sound.samples[3] = Engine.LoadSound(filePlusDir("s/klong.wav"));
    Engine.Sound.samples[4] = Engine.LoadSound(filePlusDir("s/trackersee.wav"));
    Engine.Sound.samples[5] = Engine.LoadSound(filePlusDir("s/electr.wav"));
    Engine.Sound.samples[6] = Engine.LoadSound(filePlusDir("s/new.wav"));
    Engine.Sound.samples[7] = Engine.LoadSound(filePlusDir("s/crabwalk.wav"));
    Engine.Sound.samples[8] = Engine.LoadSound(filePlusDir("s/crabatk.wav"));
    Engine.Sound.samples[9] = Engine.LoadSound(filePlusDir("s/atk.wav"));
    Engine.Sound.samples[10] = Engine.LoadSound(filePlusDir("s/umb.wav"));
    Engine.Sound.samples[11] = Engine.LoadSound(filePlusDir("s/razor.wav"));
    Engine.Sound.samples[12] = Engine.LoadSound(filePlusDir("s/grenadeexpl.wav"));
    Engine.Sound.samples[13] = Engine.LoadSound(filePlusDir("s/zorthgrenade.wav"));
    Engine.Sound.samples[14] = Engine.LoadSound(filePlusDir("s/zorthrazor.wav"));
    Engine.Sound.samples[15] = Engine.LoadSound(filePlusDir("s/zorthfire.wav"));
    Engine.Sound.samples[16] = Engine.LoadSound(filePlusDir("s/zorthspot.wav"));
    Engine.Sound.samples[17] = Engine.LoadSound(filePlusDir("s/zorthmad.wav"));
    Engine.Sound.samples[18] = Engine.LoadSound(filePlusDir("s/zorthalert.wav"));
    Engine.Sound.samples[19] = Engine.LoadSound(filePlusDir("s/plazmahit.wav"));
    Engine.Sound.samples[20] = Engine.LoadSound(filePlusDir("s/stranglersmash.wav"));
    Engine.Sound.samples[21] = Engine.LoadSound(filePlusDir("s/jet.wav"));
    Engine.Sound.samples[22] = Engine.LoadSound(filePlusDir("s/bike.wav"));
    Engine.Sound.samples[23] = Engine.LoadSound(filePlusDir("s/doorswitch.wav"));
    Engine.Sound.samples[24] = Engine.LoadSound(filePlusDir("s/metalbounce.wav"));
    Engine.Sound.samples[25] = Engine.LoadSound(filePlusDir("s/razorhit.wav"));
    Engine.Sound.samples[26] = Engine.LoadSound(filePlusDir("s/benny.wav"));
    Engine.Sound.samples[27] = Engine.LoadSound(filePlusDir("s/groundbreak.wav"));
    Engine.Sound.samples[28] = Engine.LoadSound(filePlusDir("s/squash.wav"));
    Engine.Sound.samples[29] = Engine.LoadSound(filePlusDir("s/m/wes.wav"));
    Engine.Sound.samples[30] = Engine.LoadSound(filePlusDir("s/barrier.wav"));
    Engine.Sound.samples[31] = Engine.LoadSound(filePlusDir("s/m/rtheme.wav"));
    Engine.Sound.samples[32] = Engine.LoadSound(filePlusDir("s/water.wav"));
    Engine.Sound.samples[33] = Engine.LoadSound(filePlusDir("s/m/rintro2.wav"));
    Engine.Sound.samples[34] = Engine.LoadSound(filePlusDir("s/m/arabesque.wav"));
    Engine.Sound.samples[35] = Engine.LoadSound(filePlusDir("s/m/rb.wav"));

    // load music
    Engine.Sound.music[0] = 0;
    Engine.Sound.music[1] = 0;
    Engine.Sound.music[2] = 0;
    Engine.Sound.music[3] = 0;
    Engine.Sound.music[4] = 0;
    Engine.Sound.music[5] = 0;
    Engine.Sound.music[6] = 0;
    Engine.Sound.music[7] = 0;
    Engine.Sound.music[8] = 0;

    Engine.Sound.music[0] = Engine.LoadSound(filePlusDir("s/m/rww1.wav"));
    Engine.Sound.music[1] = Engine.LoadSound(filePlusDir("s/m/reading.wav"));
    Engine.Sound.music[2] = Engine.LoadSound(filePlusDir("s/m/run.wav"));
    Engine.Sound.music[3] = Engine.LoadSound(filePlusDir("s/m/rot.wav"));
    Engine.Sound.music[4] = Engine.LoadSound(filePlusDir("s/m/ryk.wav"));
    Engine.Sound.music[5] = Engine.LoadSound(filePlusDir("s/m/itmust.wav"));
	Engine.Sound.music[6] = Engine.LoadSound(filePlusDir("s/m/rr.wav"));
	Engine.Sound.music[7] = Engine.LoadSound(filePlusDir("s/m/reading2.wav"));
	Engine.Sound.music[8] = Engine.LoadSound(filePlusDir("s/m/relhard.wav"));

    Engine.Sound.playMusics = (bool)Engine.Config.music;
    Engine.Sound.playSounds = (bool)Engine.Config.sound;

    // load bitmaps
    // map
    VolcanoImage = new SBITMAP[VOLCANO_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/volcano.bmp"), VolcanoImage, VOLCANO_FRAMES, 32, 32, 98, 52, 18);
    HomeImage = new SBITMAP[VOLCANO_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/home.bmp"), HomeImage, VOLCANO_FRAMES, 32, 32, 192, 230, 230);
    SwampImage = new SBITMAP[SWAMP_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/swamp.bmp"), SwampImage, SWAMP_FRAMES, 32, 32, 186, 206, 106);
    OublietteImage = new SBITMAP[VOLCANO_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/oubliette.bmp"), OublietteImage, VOLCANO_FRAMES, 32, 32, 30, 30, 30);
    EndImage = new SBITMAP[VOLCANO_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/end.bmp"), EndImage, VOLCANO_FRAMES, 32, 32, 30, 30, 30);
    PlumImage = new SBITMAP[VOLCANO_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/plum.bmp"), PlumImage, VOLCANO_FRAMES, 32, 32, 125, 177, 142);
    BlackImage = new SBITMAP[VOLCANO_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/black.bmp"), BlackImage, VOLCANO_FRAMES, 32, 32, 48, 52, 42);
    MinesImage = new SBITMAP[SWAMP_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/mines.bmp"), MinesImage, SWAMP_FRAMES, 32, 32, 65, 42, 39);

    // ludens
    HeroImage = new SBITMAP[HERO_FRAMES];
    HeroImageMirror = new SBITMAP[HERO_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/c.bmp"), HeroImage, HERO_FRAMES, 50, 50, 255, 0, 255);
    Engine.LoadImageFrames(filePlusDir("g/c-mirror.bmp"), HeroImageMirror, HERO_FRAMES, 50, 50, 255, 0, 255);
    TrackerImage = new SBITMAP[TRACKER_FRAMES];
    TrackerImageMirror = new SBITMAP[TRACKER_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/tracker.bmp"), TrackerImage, TRACKER_FRAMES, 18, 20, 255, 0, 255);
    Engine.LoadImageFrames(filePlusDir("g/tracker-mirror.bmp"), TrackerImageMirror, TRACKER_FRAMES, 18, 20, 255, 0, 255);
    CrabImage = new SBITMAP[CRAB_FRAMES];
    CrabImageMirror = new SBITMAP[CRAB_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/crab.bmp"), CrabImage, CRAB_FRAMES, 32, 32, 255, 0, 255);
    Engine.LoadImageFrames(filePlusDir("g/crab-mirror.bmp"), CrabImageMirror, CRAB_FRAMES, 32, 32, 255, 0, 255);
    LightImage = new SBITMAP[LIGHT_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/light.bmp"), LightImage, LIGHT_FRAMES, 15, 15, 255, 0, 255);
    BunnyImage = new SBITMAP[BUNNY_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/bunny.bmp"), BunnyImage, BUNNY_FRAMES, 18, 18, 255, 0, 255);
    ExitImage = new SBITMAP[EXIT_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/exit.bmp"), ExitImage, EXIT_FRAMES, 40, 40, 255, 0, 255);
    HexImage = new SBITMAP[HEX_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/hex.bmp"), HexImage, HEX_FRAMES, 17, 15, 255, 0, 255);
    KodamaImage = new SBITMAP[KODAMA_FRAMES];
    KodamaImageMirror = new SBITMAP[KODAMA_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/kodama.bmp"), KodamaImage, KODAMA_FRAMES, 13, 18, 255, 0, 255);
    Engine.LoadImageFrames(filePlusDir("g/kodama-mirror.bmp"), KodamaImageMirror, KODAMA_FRAMES, 13, 18, 255, 0, 255);
    HutImage = new SBITMAP[HUT_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/hut.bmp"), HutImage, HUT_FRAMES, 38, 38, 255, 0, 255);
    StranglerImage = new SBITMAP[STRANGLER_FRAMES];
    StranglerImageMirror = new SBITMAP[STRANGLER_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/strangler.bmp"), StranglerImage, STRANGLER_FRAMES, 64, 64, 255, 0, 255);
    Engine.LoadImageFrames(filePlusDir("g/strangler-mirror.bmp"), StranglerImageMirror, STRANGLER_FRAMES, 64, 64, 255, 0, 255);
    BallImage = new SBITMAP[BALL_FRAMES];
    BallImageMirror = new SBITMAP[BALL_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/ball.bmp"), BallImage, BALL_FRAMES, 32, 32, 255, 0, 255);
    Engine.LoadImageFrames(filePlusDir("g/ball-mirror.bmp"), BallImageMirror, BALL_FRAMES, 32, 32, 255, 0, 255);
    DoorImage = new SBITMAP[DOOR_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/door.bmp"), DoorImage, DOOR_FRAMES, 32, 64, 255, 0, 255);
    SwitchImage = new SBITMAP[SWITCH_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/switch.bmp"), SwitchImage, SWITCH_FRAMES, 20, 35, 255, 0, 255);
    Switch2Image = new SBITMAP[SWITCH2_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/elevswitch.bmp"), Switch2Image, SWITCH2_FRAMES, 20, 35, 255, 0, 255);
    ElevatorImage = new SBITMAP[ELEVATOR_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/elevator.bmp"), ElevatorImage, ELEVATOR_FRAMES, 64, 32, 255, 0, 255);
    ZorthImage = new SBITMAP[ZORTH_FRAMES];
    ZorthImageMirror = new SBITMAP[ZORTH_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/zorth.bmp"), ZorthImage, ZORTH_FRAMES, 38, 38, 255, 0, 255);
    Engine.LoadImageFrames(filePlusDir("g/zorth-mirror.bmp"), ZorthImageMirror, ZORTH_FRAMES, 38, 38, 255, 0, 255);
    PlazmaImage = new SBITMAP[PLAZMA_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/plazma.bmp"), PlazmaImage, PLAZMA_FRAMES, 50, 50, 255, 0, 255);
    SpringImage = new SBITMAP[SPRING_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/spring.bmp"), SpringImage, SPRING_FRAMES, 24, 24, 255, 0, 255);
    VSpringImage = new SBITMAP[VSPRING_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/vspring.bmp"), VSpringImage, VSPRING_FRAMES, 24, 24, 255, 0, 255);
    GrenadeImage = new SBITMAP[GRENADE_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/grenade.bmp"), GrenadeImage, GRENADE_FRAMES, 10, 8, 255, 0, 255);
    RazorImage = new SBITMAP[RAZOR_FRAMES];
    RazorImageMirror = new SBITMAP[RAZOR_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/razor.bmp"), RazorImage, RAZOR_FRAMES, 12, 12, 255, 0, 255);
    Engine.LoadImageFrames(filePlusDir("g/razor-mirror.bmp"), RazorImageMirror, RAZOR_FRAMES, 12, 12, 255, 0, 255);
    BlockImage = new SBITMAP[BLOCK_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/block.bmp"), BlockImage, BLOCK_FRAMES, 32, 32, 255, 0, 255);
    RabbitImage = new SBITMAP[RABBIT_FRAMES];
    RabbitImageMirror = new SBITMAP[RABBIT_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/rabbit.bmp"), RabbitImage, RABBIT_FRAMES, 18, 18, 255, 0, 255);
    Engine.LoadImageFrames(filePlusDir("g/rabbit-mirror.bmp"), RabbitImageMirror, RABBIT_FRAMES, 18, 18, 255, 0, 255);
    PlatformImage = new SBITMAP[PLATFORM_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/platform.bmp"), PlatformImage, PLATFORM_FRAMES, 32, 32, 255, 0, 255);
    HoverImage = new SBITMAP[HOVER_FRAMES];
    HoverImageMirror = new SBITMAP[HOVER_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/hover.bmp"), HoverImage, HOVER_FRAMES, 36, 14, 255, 0, 255);
    Engine.LoadImageFrames(filePlusDir("g/hover-mirror.bmp"), HoverImageMirror, HOVER_FRAMES, 36, 14, 255, 0, 255);
    LineImage = new SBITMAP[LINE_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/line.bmp"), LineImage, LINE_FRAMES, 8, 8, 255, 0, 255);
    HideImage = new SBITMAP[HIDE_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/hide.bmp"), HideImage, HIDE_FRAMES, 32, 32, 255, 0, 255);
    BikeImage = new SBITMAP[BIKE_FRAMES];
    BikeImageMirror = new SBITMAP[BIKE_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/bike.bmp"), BikeImage, BIKE_FRAMES, 70, 50, 255, 0, 255);
    Engine.LoadImageFrames(filePlusDir("g/bike-mirror.bmp"), BikeImageMirror, BIKE_FRAMES, 70, 50, 255, 0, 255);
    DestructImage = new SBITMAP[DESTRUCT_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/destruct.bmp"), DestructImage, DESTRUCT_FRAMES, 32, 32, 255, 0, 255);
    SecretImage = new SBITMAP[SECRET_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/flow.bmp"), SecretImage, SECRET_FRAMES, 24, 24, 255, 0, 255);
    GustavImage = new SBITMAP[GUSTAV_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/gustav.bmp"), GustavImage, GUSTAV_FRAMES, 68, 46, 255, 0, 255);
    DomeImage = new SBITMAP[DOME_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/dome.bmp"), DomeImage, DOME_FRAMES, 360, 360, 255, 0, 255);
    WaterImage = new SBITMAP[WATER_FRAMES];
    WaterImageMirror = new SBITMAP[WATER_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/water.bmp"), WaterImage, WATER_FRAMES, 96, 96, 255, 0, 255);
    Engine.LoadImageFrames(filePlusDir("g/water-mirror.bmp"), WaterImageMirror, WATER_FRAMES, 96, 96, 255, 0, 255);
    RiddlerImage = new SBITMAP[RIDDLER_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/riddler.bmp"), RiddlerImage, RIDDLER_FRAMES, 38, 38, 255, 0, 255);
    DudeImage = new SBITMAP[DUDE_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/dude.bmp"), DudeImage, DUDE_FRAMES, 50, 50, 255, 0, 255);
    FishmanImage = new SBITMAP[FISHMAN_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/fishman.bmp"), FishmanImage, FISHMAN_FRAMES, 50, 50, 255, 0, 255);
    TerminalImage = new SBITMAP[TERMINAL_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/terminal.bmp"), TerminalImage, TERMINAL_FRAMES, 40, 40, 255, 0, 255);
    MoleImage = new SBITMAP[MOLE_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/mole.bmp"), MoleImage, MOLE_FRAMES, 64, 64, 255, 0, 255);
    BagImage = new SBITMAP[BAG_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/bag.bmp"), BagImage, BAG_FRAMES, 32, 32, 255, 0, 255);
    OldmanImage = new SBITMAP[OLDMAN_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/oldman.bmp"), OldmanImage, OLDMAN_FRAMES, 46, 50, 255, 0, 255);
    ChangerImage = new SBITMAP[CHANGER_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/changer.bmp"), ChangerImage, CHANGER_FRAMES, 120, 120, 255, 0, 255);


    // part
    AshImage = new SBITMAP[ASH_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/ash.bmp"), AshImage, ASH_FRAMES, 32, 32, 255, 0, 255);
    DustImage = new SBITMAP[DUST_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/dust.bmp"), DustImage, DUST_FRAMES, 5, 5, 255, 0, 255);
    RainImage = new SBITMAP[RAIN_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/rain.bmp"), RainImage, RAIN_FRAMES, 48, 48, 255, 0, 255);
    FlowImage = new SBITMAP[FLOW_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/flow.bmp"), FlowImage, FLOW_FRAMES, 32, 32, 255, 0, 255);
    SandImage = new SBITMAP[SAND_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/sand.bmp"), SandImage, SAND_FRAMES, 48, 48, 255, 0, 255);
    LeafsImage = new SBITMAP[LEAFS_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/leafs.bmp"), LeafsImage, LEAFS_FRAMES, 32, 32, 255, 0, 255);
    JetsImage = new SBITMAP[JETS_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/jets.bmp"), JetsImage, JETS_FRAMES, 8, 8, 255, 0, 255);
    ExplosionImage = new SBITMAP[EXPLOSION_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/explosion.bmp"), ExplosionImage, EXPLOSION_FRAMES, 60, 85, 255, 0, 255);
    PuffImage = new SBITMAP[PUFF_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/puff.bmp"), PuffImage, PUFF_FRAMES, 46, 47, 255, 0, 255);
    BloodImage = new SBITMAP[BLOOD_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/blood.bmp"), BloodImage, BLOOD_FRAMES, 24, 24, 255, 0, 255);

    // other
    MiniImage = new SBITMAP[MINI_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/mini.bmp"), MiniImage, MINI_FRAMES, 2, 2, 255, 0, 255);

    ThunderImage = new SBITMAP[THUNDER_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/thunder.bmp"), ThunderImage, THUNDER_FRAMES, 36, 164, 255, 0, 255);
    BaloonManImage = new SBITMAP[BALOONMAN_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/baloonman.bmp"), BaloonManImage, BALOONMAN_FRAMES, 60, 60, 255, 0, 255);
    TravoltaBackImage = new SBITMAP[TRAVOLTABACK_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/cs-back1.bmp"), TravoltaBackImage, TRAVOLTABACK_FRAMES, 214, 160, 255, 0, 255);
    BananaImage = new SBITMAP[BANANA_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/banana.bmp"), BananaImage, BANANA_FRAMES, 26, 45, 255, 0, 255);
    StrangerImage = new SBITMAP[STRANGER_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/stranger.bmp"), StrangerImage, STRANGER_FRAMES, 46, 50, 255, 0, 255);
    MoonImage = new SBITMAP[MOON_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/moon.bmp"), MoonImage, MOON_FRAMES, 149, 149, 255, 0, 255);
    CloudsImage = new SBITMAP[CLOUDS_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/cloud.bmp"), CloudsImage, CLOUDS_FRAMES, 103, 65, 255, 0, 255);
    GoodCoImage = new SBITMAP[GOODCO_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/goodco.bmp"), GoodCoImage, GOODCO_FRAMES, 624, 409, 255, 0, 255);
    InterruptImage = new SBITMAP[INTERRUPT_FRAMES];
    Engine.LoadImageFrames(filePlusDir("g/traszka.bmp"), InterruptImage, INTERRUPT_FRAMES, 189, 186, 255, 0, 255);

    // load music
    //currentMODfile = filePlusDir("s/rd.it");
    //if (Engine.Config.music == 1)
    //	Engine.Sound.PlayMOD(currentMODfile);

    for (i=0; i<MAX_LUDENS; i++)
        Ludens[i].active = false;
    for (i=0; i<MAX_PART; i++)
        Part[i].active = false;

    // init variables
    cameraX = 0;
    cameraY = 0;
    cameraVX = 0;
    cameraVY = 0;
    editMode = false;
    editLudens = 1;

    menuLayer = 0;
    menuPos = 0;
    showMenu = false;
    showHint = false;

    sceneTimer = 0;
    hintTimer = 0;

    MusicFadeOut = 0;
    currentMusic = -1;

    useMusicCheck = false;
    musicStepCount = musicCheck = 0;

    lastLastLudens = lastLudens = -1;

   //mapNum = 2;
    NextMap();
    //editMode = true;

    //Map.NewTileMap(98, 52, 18);
    //	Map.tileSet = 0; Map.TilesBitmap = HomeImage;

/*    Map.NewTileMap(65, 42, 39);
    Map.tileSet = MINES_SET; Map.TilesBitmap = MinesImage;
    myLudens = AddLudens(HERO, 125 << FIX, 90 << FIX);
    mapName = "map";
    mapFileName = mapFile(mapName);*/
    //mapNum = 11;
    /*
    	Map.backgroundRed = 250;
    	Map.backgroundGreen = 250;
    	Map.backgroundBlue = 250;
    */
    return 1;
}

void CGame::ManageKeys()
{
    if (Engine.key_esc)
    {
		if (showMenu)
		{
			showMenu = false;
			Engine.Sound.PauseChannel(Engine.Sound.SpecialChannel, false);
			Engine.key_esc = false;
		} else
		{
			menuLayer = 0;
			menuPos = 0;
			showMenu = true;
			usingTerminal = false;
			Engine.Sound.PauseChannel(Engine.Sound.SpecialChannel, true);
		}
   }


    if (Engine.key_f9)
        editMode = true;

    if (Engine.key_f10)
        editMode = false;

    if (Engine.key_f6)
    {
        LoadTileMap(filePlusDir(mapFile("new")));
        mapName = "map";
        mapFileName = mapFile(mapName);
        Engine.Delay(250);
    }

    oldT++;
    if (Engine.key_f5)
        if (oldT > 8)
        {
            printf("%i \n", oldT);
            oldT = 0;
        }

    //oldT++;
    if (Engine.key_f7)
        //if (oldT > 8)
    {
        LoadTileMap(filePlusDir(mapFileName));
        Engine.Delay(250);
        //	printf("%i \n", oldT);
        //	oldT = 0;
    }

    if (Engine.key_f8)
    {
        SaveTileMap(filePlusDir(mapFileName));
        Engine.Delay(250);
    }

    if (Engine.key_map)
        miniMap = true;
    else
        miniMap = false;

    if (Engine.key_f1)
        if (oldT > 8)
        {
            if (showHint)
                showHint = false;
            else
                showHint = true;
            oldT = 0;
        }
}

void CGame::Number27Timing()
{
    TimeInMilLast = TimeInMil;
    TimeInMil = Engine.getTicks();
    if (TimeInMil-TimeInMilLast>2000)
        TimeInMilLast = TimeInMil;
    TimePassed = TimePassed + (TimeInMil-TimeInMilLast);

    SecondsLast = Seconds;
    Seconds = TimePassed/1000;
    if (Seconds != SecondsLast)
    {
        TicksPerSecond = Ticks;
        Ticks = 0;
        FramesPerSecond = Frames;
        Frames = 0;
    }
    Frames += 1;
    TickTimeLast = TickTime;
    TickTime = TimePassed/(1000/GoalTicks);
}

void CGame::MainGameLoop()
{
    int i, mainControl, loopTicks;

    int oldTicks, delay;

    while(isRunning == true)
    {
        oldTicks = Engine.getTicks();

        Number27Timing();

        Engine.CheckSystemEvents(isRunning);

        // char buffer [33];
        //itoa((TickTime),buffer,10);
        // SDL_WM_SetCaption(buffer, NULL);

        loopTicks = TickTime-TickTimeLast;
        for (mainControl = 0; mainControl<loopTicks; mainControl++)
        {
            // frame rate independent code //(TickTime-TickTimeLast)
            // timers
            Ticks += 1;
            mainTickCounter += 1;

            //Engine.Sound.PlayMusic(currentMusic);

            if (usingTerminal)
                usingTerminal = TerminalMenu(mapNum);

            if (showMenu)
                showMenu = Menu();
            else
            {
                // timers
                if (centerCaptionTimer > -1)
                    centerCaptionTimer -= 1;
                if (MusicFadeOut > -1)
                {
                    MusicFadeOut -= 5;
                    Engine.Sound.SetMusicVolume(MusicFadeOut);
                    if ((MusicFadeOut < 0)&&(!cutScene))
                    {
                        Engine.Sound.PlayMusic(currentMusic);
                        if (Engine.Config.music == 1)
                            Engine.Sound.PauseMusic(false);
                        Engine.Sound.SetMusicVolume(Engine.Sound.DefaultVolume);
                    }
                    if ((MusicFadeOut < 0)&&(cutScene))
                    {
                        //	Engine.Sound.PauseMusic(true);
                    }

                }
                if (shakeCounter > -1)
                {
                    shakeCounter -= 1;
                    viewX = viewX + ((-shakeMagnitude + Engine.random(2*shakeMagnitude + 1)) << FIX);
                    viewY = viewY + ((-shakeMagnitude + Engine.random(2*shakeMagnitude + 1)) << FIX);
                }
                if (Dialog.time > -1)
                    Dialog.time -= 1;
                if ((useMusicCheck)&&(!FSOUND_GetPaused(Engine.Sound.SpecialChannel)))
                {
                    musicCheck++;
                    if (musicCheck % MUSICMODSTEP == 0)
                    {
                        int k=FSOUND_GetCurrentPosition(Engine.Sound.SpecialChannel);
                        int step = k - oldMusicStep;
                        //printf("sync %i\n", step);

                        if ((k == 0)&&(musicStepCount > 0))
                        {
                            ResetMusicCheck();
                        }
                        else
                        {
                            oldMusicStep = k;
                            musicStepCount++;
                            if ( (k > (musicStepCount*MUSICSTEP + MUSICBOUND)) || (k < (musicStepCount*MUSICSTEP - MUSICBOUND)) )
                            {
                                FSOUND_SetCurrentPosition(Engine.Sound.SpecialChannel, musicStepCount*MUSICSTEP);
                                //	printf("Audio out of sync\n");
                                //	printf("%i\n", k - musicStepCount*MUSICSTEP);
                            }
                        }
                    }
                }
                if (interruptTimer > -1)
                {
                    interruptTimer--;
                }

                if (!editMode)
                    MapAction(mapNum);

                if (cutScene)
                    ProcessCutScene(mapNum);

                ManageKeys();

                for (i=0; i<MAX_LUDENS; i++)
                    if (Ludens[i].active)
                        LudensTick(i);

                for (i=0; i<MAX_PART; i++)
                    if (Part[i].active)
                        PartTick(i);

                if (mainTickCounter % MAP_ANIMSPEED == 0)
                    Map.animate();

                SpawnParts();
            }

            UpdateCamera(myLudens);

            SortDrawList();
        }

        // frame rate dependent Code
        RenderFrame();

        if (Engine.Config.limitfps == 1)
        {
            delay = (1000/DEFAULT_GOALTICKS)-(Engine.getTicks()-oldTicks);
            if (delay>0)//&&(delay < DEFAULT_GOALTICKS)
                Engine.Delay(delay);
        }
        else
            Engine.Delay(1);
    }


    //SaveGame();
}

void CGame::RenderFrame()
{
    int i;
	char buffer[10];

    Engine.FillBackground(Map.backgroundRed, Map.backgroundGreen, Map.backgroundBlue);

    if (cutScene)
        RenderCutScene(mapNum);

    for (i=0; i<MAX_SPRITES; i++)
    {
        if (DrawList[i])
            SpriteDraw(*DrawList[i]);

		if (debugMode)
			drawString(Engine.Screen, Engine.font, (Ludens[i].posX >> FIX) - cameraX, (Ludens[i].posY >> FIX) - cameraY, "x");
    }
    for (i=0; i<MAX_LUDENS; i++)
    {
        // draw lines
        if ((Ludens[i].active)&&(Ludens[i].style == LINE)&&(Ludens[i].target > -1))
            Engine.DrawLine((Ludens[i].posX >> FIX) - cameraX, (Ludens[i].posY >> FIX) - cameraY, (Ludens[Ludens[i].target].posX >> FIX) - cameraX, (Ludens[Ludens[i].target].posY >> FIX) - cameraY, 5, 5, 45);

        // draw secret lines
        if (DEBUG)
            //			if ((Ludens[i].active)&&(Ludens[i].style == SECRET)&&(Ludens[i].target > -1))
            if ((Ludens[i].active)&&(Ludens[i].target > -1))
                Engine.DrawLine((Ludens[i].posX >> FIX) - cameraX, (Ludens[i].posY >> FIX) - cameraY, (Ludens[Ludens[i].target].posX >> FIX) - cameraX, (Ludens[Ludens[i].target].posY >> FIX) - cameraY, 115, 75, 45);
    }

    if (!startSecret)
        DrawTileMap(cameraX, cameraY);

    if (cutScene)
        RenderAfterCutScene(mapNum);

    if (myLudens > -1)
        if (Ludens[myLudens].anchor > -1)
            RenderCameraBox(Engine.Screen->w/2, Engine.Screen->h/2, 400, 300);
    //RenderCameraBox((Ludens[myLudens].posX >> FIX) - cameraX, (Ludens[myLudens].posY >> FIX) - cameraY, 200, 200);

    // mini map sprites
    if (miniMap)
        for (i=0; i<MAX_LUDENS; i++)
            if (Ludens[i].active)
            {
                if (i == myLudens)
                    Engine.Blit(MiniImage[1], ((Ludens[i].posX >> FIX) / TILE_WIDTH)*2 + 1, ((Ludens[i].posY >> FIX) / TILE_HEIGHT)*2 + 2*SCREEN_HEIGHT/3);
                else
                    if ((Ludens[i].style ==  HEX)||(Ludens[i].style ==  EXIT)||(Ludens[i].style ==  HUT)||(Ludens[i].style ==  DOOR)||(Ludens[i].style ==  SWITCH)||(Ludens[i].style ==  TERMINAL)
                            ||(Ludens[i].style ==  SWITCH2)||(Ludens[i].style ==  SWITCH3)||(Ludens[i].style ==  ELEVATOR))
                        Engine.Blit(MiniImage[4], ((Ludens[i].posX >> FIX) / TILE_WIDTH)*2 + 1, ((Ludens[i].posY >> FIX) / TILE_HEIGHT)*2 + 2*SCREEN_HEIGHT/3);
                    else
                        if (Ludens[i].style ==  LIGHT)
                            Engine.Blit(MiniImage[3], ((Ludens[i].posX >> FIX) / TILE_WIDTH)*2 + 1, ((Ludens[i].posY >> FIX) / TILE_HEIGHT)*2 + 2*SCREEN_HEIGHT/3);
                        else
                            Engine.Blit(MiniImage[2], ((Ludens[i].posX >> FIX) / TILE_WIDTH)*2 + 1, ((Ludens[i].posY >> FIX) / TILE_HEIGHT)*2 + 2*SCREEN_HEIGHT/3);
            }

    // Captions
    if ((centerCaptionTimer > -1)&&(centerCaption))
    {
        drawString(Engine.Screen, Engine.font, SCREEN_WIDTH/2 - (strlen(centerCaption)*7)/2 , SCREEN_HEIGHT/2 + 12, centerCaption);
    }

    // Dialogs
    if (Dialog.time > 0)
    {
        if (Dialog.font == FONT_SMALL)
            drawString(Engine.Screen, Engine.font, Dialog.x - stringWidth(Engine.font, Dialog.text)/2 - cameraX, Dialog.y - cameraY - DIALOG_Y, Dialog.text);
        if (Dialog.font == FONT_BIG)
            drawString(Engine.Screen, Engine.bigfont, Dialog.x - stringWidth(Engine.bigfont, Dialog.text)/2 - cameraX, Dialog.y - cameraY - DIALOG_Y, Dialog.text);
        if (Dialog.font == FONT_BSMALL)
            drawString(Engine.Screen, Engine.blackfont, Dialog.x - stringWidth(Engine.blackfont, Dialog.text)/2 - cameraX, Dialog.y - cameraY - DIALOG_Y, Dialog.text);
        if (Dialog.font == FONT_BBIG)
            drawString(Engine.Screen, Engine.bigblackfont, Dialog.x - stringWidth(Engine.bigblackfont, Dialog.text)/2 - cameraX, Dialog.y - cameraY - DIALOG_Y, Dialog.text);
    }

    // Choices
    if (choiceMenu)
    {
        drawString(Engine.Screen, Engine.font, DIALOG_HERO_X - cameraX, DIALOG_HERO_Y + 50 - cameraY, "1.");
        drawString(Engine.Screen, Engine.font, DIALOG_HERO_X - cameraX, DIALOG_HERO_Y + 70 - cameraY, "2.");
        drawString(Engine.Screen, Engine.font, DIALOG_HERO_X - cameraX, DIALOG_HERO_Y + 90 - cameraY, "3.");

        drawString(Engine.Screen, Engine.font, DIALOG_HERO_X + 20 - cameraX, DIALOG_HERO_Y + 50 - cameraY, choiceText[0]);
        drawString(Engine.Screen, Engine.font, DIALOG_HERO_X + 20 - cameraX, DIALOG_HERO_Y + 70 - cameraY, choiceText[1]);
        drawString(Engine.Screen, Engine.font, DIALOG_HERO_X + 20 - cameraX, DIALOG_HERO_Y + 90 - cameraY, choiceText[2]);
    }

    // Interrupt
    if ((interruptTimer > -1)&&(interruptTimer < 106))
    {
        Engine.Blit(InterruptImage[interruptNum], SCREEN_WIDTH/2 - 95, SCREEN_HEIGHT/2 - 93);
    }

	// Editor
    if (editMode)
    {
        drawString(Engine.Screen, Engine.font, 0, SCREEN_HEIGHT-20, "edit");

        drawString(Engine.Screen, Engine.font, 0, SCREEN_HEIGHT-40, "Sprite: ");
        drawString(Engine.Screen, Engine.font, 60, SCREEN_HEIGHT-40, editLudensName);

		drawString(Engine.Screen, Engine.font, SCREEN_WIDTH-160, SCREEN_HEIGHT-40, "Sprite Num: ");
        itoa(editLudensNum,buffer,10);
		drawString(Engine.Screen, Engine.font, SCREEN_WIDTH-80, SCREEN_HEIGHT-40, buffer);

        // debug
        if (DEBUG)
            for (i=0; i<MAX_POSARCHIVE; i++)
                if (i == Ludens[debugLudens].trackIndex)
                    drawString(Engine.Screen, Engine.font, (Ludens[myLudens].posArchiveX[i] >> FIX) - cameraX, (Ludens[myLudens].posArchiveY[i] >> FIX) - cameraY, "o");
                else
                    drawString(Engine.Screen, Engine.font, (Ludens[myLudens].posArchiveX[i] >> FIX) - cameraX, (Ludens[myLudens].posArchiveY[i] >> FIX) - cameraY, ".");

        drawString(Engine.Screen, Engine.font, (((Ludens[myLudens].posX >> FIX) >> 5) << 5) + 13 - cameraX, (((Ludens[myLudens].posY >> FIX) >> 5) << 5) + 7 - cameraY, "x");
    }

    if (usingTerminal)
    {
        DrawTerminalMenu(mapNum);
    }

    if (showMenu)
    {
        DrawMenu();
    }
    else
        if (DEBUG)
        {
            drawString(Engine.Screen, Engine.font, 0, 0, Engine.LastVideoError);
           
            drawString(Engine.Screen, Engine.font, 0, 20, "XY");
            itoa(Ludens[myLudens].posX >> FIX, buffer,10);
            drawString(Engine.Screen, Engine.font, 40, 20, buffer);
            itoa(Ludens[myLudens].posY >> FIX, buffer,10);
            drawString(Engine.Screen, Engine.font, 80, 20, buffer);

            itoa(mapNum,buffer,10);
            drawString(Engine.Screen, Engine.font, 0, 40, "map:");
            drawString(Engine.Screen, Engine.font, 40, 40, buffer);

            itoa(sceneTimer,buffer,10);
            drawString(Engine.Screen, Engine.font, 0, 60, "timer:");
            drawString(Engine.Screen, Engine.font, 40, 60, buffer);

            itoa(fps,buffer,10);
            drawString(Engine.Screen, Engine.font, 0, 80, "fps:");
            drawString(Engine.Screen, Engine.font, 40, 80, buffer);

            itoa(Ludens[1].counter,buffer,10);
            drawString(Engine.Screen, Engine.font, 0, 100, "c:");
            drawString(Engine.Screen, Engine.font, 40, 100, buffer);

            if (useMusicCheck)
            {
                int k = FSOUND_GetCurrentPosition(Engine.Sound.SpecialChannel);
                itoa(k,buffer,10);
                drawString(Engine.Screen, Engine.font, 0, 120, "mlen:");
                drawString(Engine.Screen, Engine.font, 40, 120, buffer);
            }
        }

    if (showHint)
    {
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 100, hint[0]);
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 120, hint[1]);
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 140, hint[2]);
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 160, hint[3]);
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 180, hint[4]);
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 200, hint[5]);
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 220, hint[6]);
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 240, hint[7]);
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 260, hint[8]);
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 280, hint[9]);
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 300, hint[10]);
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 320, hint[11]);
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 340, hint[12]);
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 360, hint[13]);
        drawString(Engine.Screen, Engine.font, 2*SCREEN_WIDTH/3, 380, hint[14]);
    }

	if (mapNum == 26) //credits
	{
        drawString(Engine.Screen, Engine.font, SCREEN_WIDTH/2 - 4, CreditsY[0], "R");
        drawString(Engine.Screen, Engine.font, SCREEN_WIDTH/2 - 15, CreditsY[1], "part I");
        drawString(Engine.Screen, Engine.font, SCREEN_WIDTH/2 - 86, CreditsY[2], "'Weary dreams of melon rust'");
        	drawString(Engine.Screen, Engine.font, 4*MENU_STARTX, CreditsY[3], "a flawed masterpiece by");
        	drawString(Engine.Screen, Engine.font, 5*MENU_STARTX, CreditsY[4], "Michal Marcinkowski");
        	drawString(Engine.Screen, Engine.font, 6*MENU_STARTX, CreditsY[5], "Matt Plant");
        	drawString(Engine.Screen, Engine.font, 7*MENU_STARTX, CreditsY[6], "&");
        	drawString(Engine.Screen, Engine.font, 8*MENU_STARTX, CreditsY[7], "Dolny");
        	drawString(Engine.Screen, Engine.font, 9*MENU_STARTX, CreditsY[8], "");
        drawString(Engine.Screen, Engine.font, 1*MENU_STARTX, CreditsY[9], "For our naked pics and MM's newest game Crimson Glory visit:");
        drawString(Engine.Screen, Engine.font, 1*MENU_STARTX, CreditsY[10], "http://www.crimsonengine.com");
	}

    // FPS Handling
    frc++;
    if (frc == 25)
    {
        frc = 0;
        fps = frp;
        frp = Engine.getTicks();
        fps = 25000/(frp-fps);
    }

    Engine.FlipBuffer();
}

void CGame::ShakeCamera(int time, int magnitude)
{
    shakeCounter = time;
    shakeMagnitude = magnitude;
}

void CGame::UpdateCamera(int num)
{
    if (num<0)
        return;

    int w, h;
    w = SCREEN_WIDTH;
    h = SCREEN_HEIGHT;
    int spd = CAMERA_SPEED;

    if (showMenu)
        spd = CAMERA_SPEED*2;
    if (shakeCounter > 0)
        spd = CAMERA_SPEED/4;

    /* if (Dialog.font == 1)
     {
    Dialog.x = Dialog.x + (cameraX - cameraOX);
    Dialog.y = Dialog.y + (cameraY - cameraOY);
     }*/

    cameraVX += ((Ludens[num].posX + viewX) - ( (w / 2) << FIX) - cameraVX) / spd;
    cameraVY += ((Ludens[num].posY + viewY) - ( (h / 2) << FIX) - cameraVY) / spd;
    cameraOX =  cameraX;
    cameraOY =  cameraY;
    cameraX = cameraVX >> FIX;
    cameraY = cameraVY >> FIX;

    if (cameraX < 0)
        cameraX = 0;
    if (cameraY < 0)
        cameraY = 0;
    if (cameraX > ( (MAP_WIDTH - (SCREEN_WIDTH >> 5)) << 5) - (TILE_WIDTH >> 1))
        cameraX = ( (MAP_WIDTH - (SCREEN_WIDTH >> 5)) << 5) - (TILE_WIDTH >> 1);
    if (cameraY > ( (MAP_HEIGHT - (SCREEN_HEIGHT >> 5)) << 5) - TILE_HEIGHT)
        cameraY = ( (MAP_HEIGHT - (SCREEN_HEIGHT >> 5)) << 5) - TILE_HEIGHT;
}


void CGame::TestMapCollision(int sX, int sY, int *r)
{
    int tx, ty;
    int cell = -255;

    tx = (sX >> FIX) / TILE_WIDTH;
    ty = (sY >> FIX) / TILE_HEIGHT;

    if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH) && (ty < MAP_HEIGHT))
        cell = Map.getCell(tx, ty);
    else
    {
        r[0] = 1;
        r[1] = (tx * TILE_WIDTH) << FIX;
        r[2] = (ty * TILE_HEIGHT) << FIX;
        return;
    }

    if (cell == 0)
    {
        r[0] = 1;
        r[1] = (tx * TILE_WIDTH) << FIX;
        r[2] = (ty * TILE_HEIGHT) << FIX;
        return;
    }
    if ((cell == 46)||(cell > 48))
    {
        r[0] = 2;
        r[1] = (tx * TILE_WIDTH) << FIX;
        r[2] = (ty * TILE_HEIGHT) << FIX;
        return;
    }
    r[0] = 0;
}



int CGame::AddLudens(int style, int newPosX, int newPosY, int newId)
{
    int i, c;

    if (newId == -1)
    {
        for (i=0; i<MAX_LUDENS+1; i++)
        {
            c = i;
            if (i == MAX_LUDENS)
                return -1;
            if (!Ludens[i].active)
                break;
        }
    }
    else
        c = newId;
    //c is now the active ludens

    switch(style)
    {
    case HERO:
        Ludens[c].InitLudens(c, HeroImage, HeroImageMirror, style, newPosX, newPosY,
                             0, 50, 50, HERO_MAXSPEED, HERO_GRAVITY, 25, 33, HERO_RADIUSX, HERO_RADIUSY);
        break;
    case LIGHT:
        Ludens[c].InitLudens(c, LightImage, LightImage, style, newPosX, newPosY,
                             AI_RUNAWAY, 15, 15, LIGHT_MAXSPEED - (1 << FIX) + (Engine.random(2) << FIX),
                             LIGHT_GRAVITY, 7, 7, 12 << FIX, 12 << FIX);
        break;
    case TRACKER:
        Ludens[c].InitLudens(c, TrackerImage, TrackerImageMirror, style, newPosX, newPosY,
                             AI_RUNAWAY, 18, 20, TRACKER_MAXSPEED, TRACKER_GRAVITY, 9, 14, 12 << FIX, 12 << FIX);
        break;
    case CRAB:
        Ludens[c].InitLudens(c, CrabImage, CrabImageMirror, style, newPosX, newPosY,
                             0, 32, 32, CRAB_MAXSPEED, CRAB_GRAVITY, 16, 21, 12 << FIX, 12 << FIX);
        break;
    case EXIT:
        Ludens[c].InitLudens(c, ExitImage, ExitImage, style, newPosX, newPosY,
                             0, 40, 40, 0, 0, 20, 20, 20 << FIX, 20 << FIX);
        break;
    case HEX:
        Ludens[c].InitLudens(c, HexImage, HexImage, style, (newPosX / (11 << FIX))*(11 << FIX), (newPosY / (7 << FIX))*(7 << FIX),
                             0, 17, 15, 0, 0, 7, 7, 32 << FIX, 32 << FIX);
        break;
    case BUNNY:
        Ludens[c].InitLudens(c, BunnyImage, BunnyImage, style, newPosX, newPosY,
                             AI_NOTHING, 18, 18, BUNNY_MAXSPEED,
                             BUNNY_GRAVITY, 9, 8, 13 << FIX, 13 << FIX);
        break;
    case BUNNY2:
        Ludens[c].InitLudens(c, BunnyImage, BunnyImage, style, newPosX, newPosY,
                             AI_NOTHING, 18, 18, BUNNY_MAXSPEED,
                             BUNNY_GRAVITY, 9, 9, 13 << FIX, 13 << FIX);
        break;
    case BUNNY3:
        Ludens[c].InitLudens(c, BunnyImage, BunnyImage, style, newPosX, newPosY,
                             AI_NOTHING, 18, 18, BUNNY_MAXSPEED,
                             BUNNY_GRAVITY, 9, 9, 13 << FIX, 13 << FIX);
        break;
    case KODAMA:
        Ludens[c].InitLudens(c, KodamaImage, KodamaImageMirror, style, newPosX, newPosY,
                             AI_NOTHING, 12, 18, KODAMA_MAXSPEED, KODAMA_GRAVITY, 6, 9, 10 << FIX, 11 << FIX);
        break;
    case HUT:
        Ludens[c].InitLudens(c, HutImage, HutImage, style, newPosX, newPosY,
                             0, 38, 38, 0, 0, 19, 19, 19 << FIX, 19 << FIX);
        break;
    case STRANGLER:
        Ludens[c].InitLudens(c, StranglerImage, StranglerImageMirror, style, newPosX, newPosY,
                             AI_NOTHING, 64, 64, STRANGLER_MAXSPEED, STRANGLER_GRAVITY, 15, 47, 28 << FIX, 20 << FIX);
        break;
    case BALL:
        Ludens[c].InitLudens(c, BallImage, BallImageMirror, style, newPosX, newPosY,
                             AI_NOTHING, 32, 32, BALL_MAXSPEED, BALL_GRAVITY, 23, 23, 13 << FIX, 6 << FIX);
        break;
    case DOOR:
        Ludens[c].InitLudens(c, DoorImage, DoorImage, style, newPosX, newPosY,
                             AI_NOTHING, 32, 64, 0, 0, 16, 32, 16 << FIX, 32 << FIX);
        break;
    case SWITCH:
        Ludens[c].InitLudens(c, SwitchImage, SwitchImage, style, newPosX, newPosY,
                             AI_NOTHING, 20, 35, 0, 0, 8, 8, 16 << FIX, 20 << FIX);
        Ludens[c].target = ClosestStyleLudens(c, DOOR, DOOR, 0);
        break;
    case SWITCH2:
        Ludens[c].InitLudens(c, Switch2Image, Switch2Image, style, newPosX, newPosY,
                             AI_NOTHING, 20, 35, 0, 0, 8, 8, 16 << FIX, 20 << FIX);
        Ludens[c].target = ClosestStyleLudens(c, ELEVATOR, ELEVATOR, 0);
        break;
    case SWITCH3:
        Ludens[c].InitLudens(c, SwitchImage, SwitchImage, style, newPosX, newPosY,
                             AI_NOTHING, 20, 35, 0, 0, 8, 8, 16 << FIX, 20 << FIX);
        Ludens[c].target = ClosestStyleLudens(c, DOOR, DOOR, 0);
        break;
    case ELEVATOR:
        Ludens[c].InitLudens(c, ElevatorImage, ElevatorImage, style, newPosX, newPosY,
                             AI_NOTHING, 64, 32, ELEVATOR_MAXSPEED, 0, 32, 19, 32 << FIX, 22 << FIX);
        Ludens[c].attitude = Ludens[c].target = 100;
        if (LudensCanGo(c, DOWN, false))
            Ludens[c].attitude = Ludens[c].target = 101;
        break;
    case ZORTH:
        Ludens[c].InitLudens(c, ZorthImage,ZorthImageMirror, style, newPosX, newPosY,
                             AI_NOTHING, 38, 38, ZORTH_MAXSPEED, ZORTH_GRAVITY, 20, 19, 16 << FIX, 20 << FIX);
        debugLudens = c;
        Ludens[c].ammoType = ZORTH_AMMOPLAZMA;
        Ludens[c].ammoCount = 2 + Engine.random(3);
        break;
    case PLAZMA:
        Ludens[c].InitLudens(c, PlazmaImage, PlazmaImage, style, newPosX, newPosY,
                             AI_NOTHING, 50, 50, PLAZMA_MAXSPEED, PLAZMA_GRAVITY, 25, 25, 4 << FIX, 4 << FIX);
        break;
    case GRENADE:
        Ludens[c].InitLudens(c, GrenadeImage, GrenadeImage, style, newPosX, newPosY,
                             AI_NOTHING, 10, 8, GRENADE_MAXSPEED, GRENADE_GRAVITY, 5, 4, 4 << FIX, 4 << FIX);
        break;
    case SPRING:
        Ludens[c].InitLudens(c, SpringImage, SpringImage, style, newPosX, newPosY,
                             AI_NOTHING, 24, 24, SPRING_MAXSPEED, SPRING_GRAVITY, 12, 6, 12 << FIX, 18 << FIX);
        break;
    case VSPRING:
        Ludens[c].InitLudens(c, VSpringImage, VSpringImage, style, newPosX, newPosY,
                             AI_NOTHING, 24, 24, VSPRING_MAXSPEED, VSPRING_GRAVITY, 12, 6, 12 << FIX, 18 << FIX);
        break;
    case RAZOR:
        Ludens[c].InitLudens(c, RazorImage, RazorImageMirror, style, newPosX, newPosY,
                             AI_NOTHING, 12, 12, RAZOR_MAXSPEED, RAZOR_GRAVITY, 5, 5, 5 << FIX, 5 << FIX);
        break;
    case BLOCK:
        Ludens[c].InitLudens(c, BlockImage, BlockImage, style, newPosX, newPosY,
                             AI_NOTHING, 32, 32, BLOCK_MAXSPEED, BLOCK_GRAVITY, 16, 8, 22 << FIX, 24 << FIX);
        break;
    case RABBIT:
        Ludens[c].InitLudens(c, RabbitImage, RabbitImageMirror, style, newPosX, newPosY,
                             AI_NOTHING, 12, 18, RABBIT_MAXSPEED, RABBIT_GRAVITY, 9, 14, 10 << FIX, 6 << FIX);
        break;
    case PLATFORM:
        Ludens[c].InitLudens(c, PlatformImage, PlatformImage, style, newPosX, newPosY,
                             AI_NOTHING, 32, 32, PLATFORM_MAXSPEED, PLATFORM_GRAVITY, 16, 20, 20 << FIX, 18 << FIX);
        break;
    case HOVER:
        Ludens[c].InitLudens(c, HoverImage, HoverImageMirror, style, newPosX, newPosY,
                             AI_NOTHING, 36, 14, HOVER_MAXSPEED, HOVER_GRAVITY, 18, 7, 18 << FIX, 11 << FIX);
        break;
    case LINE:
        Ludens[c].InitLudens(c, LineImage, LineImage, style, newPosX, newPosY,
                             AI_NOTHING, 8, 8, 0, 0, 4, 4, 16 << FIX, 16 << FIX);
        break;
    case HIDE:
        Ludens[c].InitLudens(c, HideImage, HideImage, style, newPosX, newPosY,
                             AI_NOTHING, 32, 32, 0, 0, 16, 48, 8 << FIX, 64 << FIX);
        break;
    case BIKE:
        Ludens[c].InitLudens(c, BikeImage, BikeImageMirror, style, newPosX, newPosY,
                             AI_NOTHING, 70, 50, BIKE_MAXSPEED, BIKE_GRAVITY, 36, 36, 32 << FIX, 24 << FIX);
        break;
    case DESTRUCT:
        Ludens[c].InitLudens(c, DestructImage, DestructImage, style, newPosX, newPosY,
                             AI_NOTHING, 32, 32, 0, 0, 16, 16, 16 << FIX, 16 << FIX);
        break;
    case SECRET:
        Ludens[c].InitLudens(c, SecretImage, SecretImage, style, newPosX, newPosY,
                             AI_NOTHING, 24, 24, 0, 0, 12, 12, 12 << FIX, 12 << FIX);
        break;
    case GUSTAV:
        Ludens[c].InitLudens(c, GustavImage, GustavImage, style, newPosX, newPosY,
                             AI_NOTHING, 68, 46, GUSTAV_MAXSPEED, 0, 34, 23, 34 << FIX, 23 << FIX);
        break;
    case DOME:
        Ludens[c].InitLudens(c, DomeImage, DomeImage, style, newPosX, newPosY,
                             AI_NOTHING, 360, 360, 0, 0, 180, 180, 180 << FIX, 180 << FIX);
        break;
    case WATER:
        Ludens[c].InitLudens(c, WaterImage, WaterImageMirror, style, newPosX, newPosY,
                             AI_NOTHING, 96, 96, WATER_MAXSPEED, WATER_GRAVITY, 36, 48, 12 << FIX, 24 << FIX);
        break;
    case RIDDLER:
        Ludens[c].InitLudens(c, RiddlerImage, RiddlerImage, style, newPosX, newPosY,
                             AI_NOTHING, 38, 38, 0, 0, 19, 19, 19 << FIX, 19 << FIX);
        break;
    case DUDE:
        Ludens[c].InitLudens(c, DudeImage, DudeImage, style, newPosX, newPosY,
                             AI_NOTHING, 50, 50, 0, 0, 25, 25, 25 << FIX, 15 << FIX);
        break;
    case FISHMAN:
        Ludens[c].InitLudens(c, FishmanImage, FishmanImage, style, newPosX, newPosY,
                             AI_NOTHING, 50, 50, 0, 0, 25, 25, 25 << FIX, 15 << FIX);
        break;
    case STEP:
        Ludens[c].InitLudens(c, DestructImage, DestructImage, style, newPosX, newPosY,
                             AI_NOTHING, 32, 32, 0, 0, 16, 16, 36 << FIX, 36 << FIX);
        break;
    case TERMINAL:
        Ludens[c].InitLudens(c, TerminalImage, TerminalImage, style, newPosX, newPosY,
                             AI_NOTHING, 40, 40, 0, 0, 20, 20, 20 << FIX, 20 << FIX);
        break;
    case MOLE:
        Ludens[c].InitLudens(c, MoleImage, MoleImage, style, newPosX, newPosY,
                             AI_NOTHING, 64, 64, MOLE_MAXSPEED, MOLE_GRAVITY, 32, 32, 16 << FIX, 16 << FIX);
        break;
    case BAG:
        Ludens[c].InitLudens(c, BagImage, BagImage, style, newPosX, newPosY,
                             AI_NOTHING, 32, 32, BAG_MAXSPEED, BAG_GRAVITY, 16, 16, 2 << FIX, 7 << FIX);
        break;
    case OLDMAN:
        Ludens[c].InitLudens(c, OldmanImage, OldmanImage, style, newPosX, newPosY,
                             AI_NOTHING, 46, 50, 0, 0, 23, 25, 23 << FIX, 25 << FIX);
        break;
    case CHANGER:
        Ludens[c].InitLudens(c, ChangerImage, ChangerImage, style, newPosX, newPosY,
                             AI_NOTHING, 120, 120, 0, 0, 60, 50, 60 << FIX, 15 << FIX);
        break;
    };

    return c;
}

int CGame::AddPart(int style, int posX, int posY)
{
    int i, c;
    for (i=0; i<MAX_PART+1; i++)
    {
        c = i;
        if (i == MAX_PART)
            return -1;
        if (!Part[i].active)
            break;
    }
    //c is now the active part

    switch(style)
    {
    case P_ASH:
        Part[c].InitPart(AshImage, style, posX, posY,
                         ASH_MAXSPEED + ((-3 + Engine.random(6)) << FIX), ASH_GRAVITY, 16, 16, ASH_ANIMSPEED*ASH_FRAMES, ASH_ANIMSPEED);
        break;
    case P_DUST:
        Part[c].InitPart(DustImage, style, posX, posY,
                         DUST_MAXSPEED, DUST_GRAVITY, 2, 2, DUST_ANIMSPEED*DUST_FRAMES, DUST_ANIMSPEED);
        break;
    case P_RAIN:
        Part[c].InitPart(RainImage, style, posX, posY,
                         RAIN_MAXSPEED + ((-2 + Engine.random(4)) << FIX), RAIN_GRAVITY, 24, 24, RAIN_ANIMSPEED, RAIN_ANIMSPEED);
        break;
    case P_FLOW:
        Part[c].InitPart(FlowImage, style, posX, posY,
                         FLOW_MAXSPEED, FLOW_GRAVITY, 16, 16, FLOW_ANIMSPEED*FLOW_FRAMES, FLOW_ANIMSPEED);
        break;
    case P_SAND:
        Part[c].InitPart(SandImage, style, posX, posY,
                         SAND_MAXSPEED + ((-3 + Engine.random(6)) << FIX), SAND_GRAVITY, 24, 24, SAND_ANIMSPEED, SAND_ANIMSPEED);
        break;
    case P_LEAFS:
        Part[c].InitPart(LeafsImage, style, posX, posY,
                         LEAFS_MAXSPEED, LEAFS_GRAVITY, 16, 16, 8*24, LEAFS_ANIMSPEED);
        break;
    case P_JETS:
        Part[c].InitPart(JetsImage, style, posX, posY,
                         JETS_MAXSPEED, JETS_GRAVITY, 4, 4, JETS_ANIMSPEED*JETS_FRAMES, JETS_ANIMSPEED);
        break;
    case P_EXPLOSION:
        Part[c].InitPart(ExplosionImage, style, posX, posY,
                         0, 0, -15, 42, EXPLOSION_ANIMSPEED*EXPLOSION_FRAMES, EXPLOSION_ANIMSPEED);
        break;
    case P_PUFF:
        Part[c].InitPart(PuffImage, style, posX, posY,
                         0, 0, -4, 12, PUFF_ANIMSPEED*PUFF_FRAMES, PUFF_ANIMSPEED);
        break;
    case P_BLOOD:
        Part[c].InitPart(BloodImage, style, posX, posY,
                         24, 24, 0, 12, BLOOD_ANIMSPEED*BLOOD_FRAMES, BLOOD_ANIMSPEED);
        break;
    };

    return c;
}

void CGame::PlaceModTile(int tx, int ty)
{
    int i;
    int c1, c2, c3, c4;

    if (Map.getCell(tx, ty) == 0)
        return;

    for (i=0; i < 16; i++)
    {
        if (i == 15)
            break;
        c1 = Map.getCell(tx - 1, ty)+1;
        c2 = Map.getCell(tx + 1, ty)+1;
        c3 = Map.getCell(tx, ty - 1)+1;
        c4 = Map.getCell(tx, ty + 1)+1;
        if (c1 > 1)
            c1 = 0;
        if (c2 > 1)
            c2 = 0;
        if (c3 > 1)
            c3 = 0;
        if (c4 > 1)
            c4 = 0;
        if (( tilesMatrixL[i]==c1 )&&(tilesMatrixR[i]==c2 )&&( tilesMatrixU[i]==c3 )&&( tilesMatrixD[i]==c4 ))
            break;
    }
    if (i !=15 )
        Map.setCell(tx, ty, i*3 + 1 + Engine.random(3));
}

void CGame::EditTick(int num)
{
    int tx, ty, px, py;
    int cell = -255;
    int i, j, c;
    int mspeed;

    tx = (Ludens[num].posX >> FIX) / TILE_WIDTH;
    ty = (Ludens[num].posY >> FIX) / TILE_HEIGHT;

    if ( (tx > 0) && (ty > 0) && (tx < MAP_WIDTH-1) && (ty < MAP_HEIGHT-1))
        cell = Map.getCell(tx, ty);

    // move cursor
    if (Engine.key_shift)
        mspeed = HERO_MAXSPEED;
    else
        mspeed = HERO_MOVE;

    if (Engine.key_left)
        Ludens[num].moveSprite(-mspeed, 0);
    if (Engine.key_right)
        Ludens[num].moveSprite(mspeed, 0);
    if (Engine.key_up||Engine.key_jump)
        Ludens[num].moveSprite(0, -mspeed);
    if (Engine.key_down)
        Ludens[num].moveSprite(0, mspeed);

    if ((tx > 0)&&(tx < MAP_WIDTH-1)&&(ty > 0)&&(ty < MAP_HEIGHT-1))
    {
        // place tile
        if (Engine.key_z)
        {
            Map.setCell(tx, ty, 0);

            PlaceModTile(tx - 1, ty);
            PlaceModTile(tx + 1, ty);
            PlaceModTile(tx, ty + 1);
            PlaceModTile(tx, ty - 1);
		}

        // delete tile
        if (Engine.key_x)
        {
            DeleteTile(tx, ty);

            if (Engine.key_ctrl)
            {
                DeleteTile(tx - 1, ty);
                DeleteTile(tx + 1, ty);
                DeleteTile(tx, ty - 1);
                DeleteTile(tx, ty + 1);
                DeleteTile(tx - 1, ty - 1);
                DeleteTile(tx + 1, ty + 1);
                DeleteTile(tx + 1, ty - 1);
                DeleteTile(tx - 1, ty + 1);
            }
        }

        // create mini map
        if ((Engine.key_z)||(Engine.key_x))
        {
            //Engine.FreeBitmap(MiniMap);
            //Engine.CreateSurface(MiniMap, MAP_WIDTH*2, MAP_HEIGHT*2);
            //for (i=0; i<MAP_WIDTH; i++)
            //    for (j=0; j<MAP_HEIGHT; j++)
            //    {
            //        if (!Map.tiles[j][i])
            //        {
            //            Engine.BlitTo(MiniImage[0], MiniMap, i*2, j*2);
            //        }
            //    }
        }
    }

    // place special tiles
    if (Engine.key_8)
    {
        Map.setCell(tx, ty, 46);
    }

    if (Engine.key_9)
    {
        Map.setCell(tx, ty, 47);
    }

    // iterate operation
    for (i = 0; i < MAX_LUDENS; i++)
        if ((Ludens[i].active)&&(i != myLudens))
        {
            px = (Ludens[i].posX >> FIX) / TILE_WIDTH;
            py = (Ludens[i].posY >> FIX) / TILE_HEIGHT;
            if ((px == tx)&&(py == ty))
            {
                if (Engine.key_q) // delete
                    Ludens[i].active = false;

                if (Engine.key_w) // pick
				{
                    editLudens = Ludens[i].style;
					lastLastLudens = lastLudens = i;
				}

                if (Engine.key_r) // pick number
                    editLudensNum = i;

                if (canPress)
                    if (Engine.key_e) // change dir
                    {
                        if (Ludens[i].animDirection == RIGHT)
                        {
                            Ludens[i].setAnimation(Ludens[i].animNum, Ludens[i].animSpeed, LEFT, Ludens[i].animBlock, Ludens[i].animLoop);
                            Ludens[i].animDirection = LEFT;
                        }
                        else
                        {
                            Ludens[i].setAnimation(Ludens[i].animNum, Ludens[i].animSpeed, RIGHT, Ludens[i].animBlock, Ludens[i].animLoop);
                            Ludens[i].animDirection = RIGHT;
                        }
                        canPress = false;
                    }

                if (canPress)
                    if (Engine.key_t) // assign target
                    {
                        if (lastLastLudens > -1)
                            Ludens[lastLastLudens].target = i;
                        else
                            if (lastLudens > -1)
                                Ludens[lastLudens].target = i;
                    }

                break;
            }
        }

    if (canPress)
    {
        if (Engine.key_s)
        {
            editLudens++;
            canPress = false;
        }

        if (Engine.key_a)
        {
            editLudens--;
            canPress = false;
        }


        int max = LASTLUDENS;
        if (editLudens < 0)
            editLudens = max;
        if (editLudens > max)
            editLudens = 0;

        if (Engine.key_c)
        {
            c = AddLudens(editLudens, Ludens[num].posX, Ludens[num].posY);
            lastLastLudens = lastLudens;
            lastLudens = c;
            canPress = false;
        }
        if (Engine.key_y)
        {
            lastLastLudens = lastLudens = -1;
            canPress = false;
        }
        if (Engine.key_u)
        {
            Ludens[lastLudens].active = false;
            lastLudens = lastLastLudens;
            canPress = false;
        }
    }

    if ((!Engine.key_c)&&(!Engine.key_a)&&(!Engine.key_s)&&(!Engine.key_e)&&(!Engine.key_t)&&(!Engine.key_u))
        canPress = true;

    switch (editLudens)
    {
    case (HERO):
                    editLudensName = "HERO";
        break;
    case (LIGHT):
                    editLudensName = "LIGHT";
        break;
    case (TRACKER):
                    editLudensName = "TRACKER";
        break;
    case (CRAB):
                    editLudensName = "CRAB";
        break;
    case (EXIT):
                    editLudensName = "EXIT";
        break;
    case (HEX):
                    editLudensName = "HEX";
        break;
    case (BUNNY):
                    editLudensName = "JUMP BUNNY";
        break;
    case (BUNNY2):
                    editLudensName = "IMPULSE BUNNY";
        break;
    case (BUNNY3):
                    editLudensName = "PUSH BUNNY";
        break;
    case (KODAMA):
                    editLudensName = "KODAMA";
        break;
    case (HUT):
                    editLudensName = "KODAMA HUT";
        break;
    case (STRANGLER):
                    editLudensName = "STRANGLER";
        break;
    case (BALL):
                    editLudensName = "BALL";
        break;
    case (DOOR):
                    editLudensName = "DOOR";
        break;
    case (SWITCH):
                    editLudensName = "DOOR SWITCH";
        break;
    case (ELEVATOR):
                    editLudensName = "ELEVATOR";
        break;
    case (ZORTH):
                    editLudensName = "ZORTH";
        break;
    case (PLAZMA):
                    editLudensName = "PLAZMA";
        break;
    case (SWITCH2):
                    editLudensName = "ELEVATOR SWITCH";
        break;
    case (GRENADE):
                    editLudensName = "GRENADE";
        break;
    case (SPRING):
                    editLudensName = "HORIZONTAL SPRING";
        break;
    case (RAZOR):
                    editLudensName = "RAZOR";
        break;
    case (SWITCH3):
                    editLudensName = "ZORTH DOOR SWITCH";
        break;
    case (BLOCK):
                    editLudensName = "PUSH BLOCK";
        break;
    case (RABBIT):
                    editLudensName = "RABBIT";
        break;
    case (PLATFORM):
                    editLudensName = "PLATFORM";
        break;
    case (HOVER):
                    editLudensName = "HOVERBOARD";
        break;
    case (LINE):
                    editLudensName = "LINE";
        break;
    case (HIDE):
                    editLudensName = "HIDE";
        break;
    case (VSPRING):
                    editLudensName = "VERTICAL SPRING";
        break;
    case (BIKE):
                    editLudensName = "HOVERBIKE";
        break;
    case (DESTRUCT):
                    editLudensName = "DESTRUCT";
        break;
    case (SECRET):
                    editLudensName = "SECRET";
        break;
    case (GUSTAV):
                    editLudensName = "GUSTAV";
        break;
    case (DOME):
                    editLudensName = "DOME";
        break;
    case (WATER):
                    editLudensName = "WATER";
        break;
    case (RIDDLER):
                    editLudensName = "RIDDLER";
        break;
    case (DUDE):
                    editLudensName = "DUDE";
        break;
    case (FISHMAN):
                    editLudensName = "FISHMAN";
        break;
    case (STEP):
                    editLudensName = "DIALOG STEP";
        break;
    case (TERMINAL):
                    editLudensName = "TERMINAL";
        break;
    case (MOLE):
                    editLudensName = "MOLE";
        break;
    case (BAG):
                    editLudensName = "BAG";
        break;
    case (OLDMAN):
                    editLudensName = "OLDMAN";
        break;
    case (CHANGER):
                    editLudensName = "CHANGER";
        break;
    default:
        editLudensName = "_UNKNOWN";
        break;
    }

    // no 2 ludenson same point
    /*	if (Engine.key_c || Engine.key_t || Engine.key_l || Engine.key_n || Engine.key_m
    		 || Engine.key_o || Engine.key_p || Engine.key_i || Engine.key_k || Engine.key_h || Engine.key_y
    		 || Engine.key_u || Engine.key_d || Engine.key_s || Engine.key_a || Engine.key_e || Engine.key_w
    		 || Engine.key_g || Engine.key_r || Engine.key_j || Engine.key_b || Engine.key_f || Engine.key_5
    		 || Engine.key_v || Engine.key_4 || Engine.key_3)
    		for (i = 0; i < MAX_LUDENS; i++)
    			if ((Ludens[i].active)&&(i != myLudens))
    			{
    				if ((Ludens[num].posX == Ludens[i].posX)&&(Ludens[num].posY == Ludens[i].posY))
    				{
    					Ludens[i].active = false;
    					break;
    				}
    			}

    	//if (Map.getCell(tx, ty) != 0)
    	{
    		c = -1;
    		// put Crab
    		if (Engine.key_c)
    			c = AddLudens(CRAB, Ludens[num].posX, Ludens[num].posY);	
    		// put Tracker
    		if (Engine.key_t)
    			c = AddLudens(TRACKER, Ludens[num].posX, Ludens[num].posY);	
    		// put Light
    		if (Engine.key_l)
    			c = AddLudens(LIGHT, Ludens[num].posX, Ludens[num].posY);	
    		// put Bunny
    		if (Engine.key_i)
    			c = AddLudens(BUNNY, Ludens[num].posX, Ludens[num].posY);	
    		// put Bunny2
    		if (Engine.key_o)
    			c = AddLudens(BUNNY2, Ludens[num].posX, Ludens[num].posY);	
    		// put Bunny3
    		if (Engine.key_p)
    			c = AddLudens(BUNNY3, Ludens[num].posX, Ludens[num].posY);
    		// put Exit
    		if (Engine.key_m)
    			c = AddLudens(EXIT, Ludens[num].posX, Ludens[num].posY);	
    		// put Hex
    		if (Engine.key_n)
    			c = AddLudens(HEX, Ludens[num].posX, Ludens[num].posY);	
    		// put Kodama
    		if (Engine.key_k)
    			c = AddLudens(KODAMA, Ludens[num].posX, Ludens[num].posY);	
    		// put Hut
    		if (Engine.key_h)
    			c = AddLudens(HUT, Ludens[num].posX, Ludens[num].posY);	
    		// put Strangler
    		if (Engine.key_y)
    			c = AddLudens(STRANGLER, Ludens[num].posX, Ludens[num].posY);	
    		// put Ball
    		if (Engine.key_u)
    			c = AddLudens(BALL, Ludens[num].posX, Ludens[num].posY);	
    		// put Door
    		if (Engine.key_d)
    			c = AddLudens(DOOR, Ludens[num].posX, Ludens[num].posY);
    		// put Switch
    		if (Engine.key_s)
    			c = AddLudens(SWITCH, Ludens[num].posX, Ludens[num].posY);
    		// put Switch2
    		if (Engine.key_w)
    			c = AddLudens(SWITCH2, Ludens[num].posX, Ludens[num].posY);
    		// put Switch3
    		if (Engine.key_r)
    			c = AddLudens(SWITCH3, Ludens[num].posX, Ludens[num].posY);
    		// put Elevator
    		if (Engine.key_e)
    			c = AddLudens(ELEVATOR, Ludens[num].posX, Ludens[num].posY);
    		// put Zorth
    		if (Engine.key_a)
    			c = AddLudens(ZORTH, Ludens[num].posX, Ludens[num].posY);	
    		// put Spring
    		if (Engine.key_g)
    			c = AddLudens(SPRING, Ludens[num].posX, Ludens[num].posY);
    		// put VSpring
    		if (Engine.key_3)
    			c = AddLudens(VSPRING, Ludens[num].posX, Ludens[num].posY);
    		// put Block
    		if (Engine.key_b)
    			c = AddLudens(BLOCK, Ludens[num].posX, Ludens[num].posY);
    		// put Rabbit
    		if (Engine.key_j)
    			c = AddLudens(RABBIT, Ludens[num].posX, Ludens[num].posY);
    		// put Platform
    		if (Engine.key_f)
    			c = AddLudens(PLATFORM, Ludens[num].posX, Ludens[num].posY);
    		// put Hover
    		if (Engine.key_5)
    			c = AddLudens(HOVER, Ludens[num].posX, Ludens[num].posY);
    		// put Line
    		if (Engine.key_v)
    			c = AddLudens(LINE, Ludens[num].posX, Ludens[num].posY);
    		// put Hide
    		if (Engine.key_4)
    			c = AddLudens(HIDE, Ludens[num].posX, Ludens[num].posY);

    		if (c > -1)
    		{
    			if (Engine.random(2) == 0)
    				Ludens[c].animDirection = RIGHT;
    			else
    				Ludens[c].animDirection = LEFT;

    			if (Ludens[c].style == LINE)
    			{
    				if (lastLine > -1)
    					Ludens[lastLine].target = c;

    				lastLine = c;
    			}

    			if (Ludens[c].style == HIDE)
    			{
    				Ludens[c].target = Engine.random(2);
    			}
    		}
    		
    	}*/


    Ludens[num].convertPosition();

    Ludens[num].velX = Ludens[num].velY = 0;
}


int CGame::ClosestStyleLudens(int m, int style, int style2, int side)
{
    int i;
    int dist, minDist;
    int min = -1;

    minDist = 99999 << FIX;
    for (i=0; i<MAX_LUDENS; i++)
        if ((Ludens[i].active)&&(i != m)&&((Ludens[i].style == style)||(Ludens[i].style == style2)))
            if (((side == RIGHT)&&(Ludens[i].posX > Ludens[m].posX))||((side == LEFT)&&(Ludens[i].posX < Ludens[m].posX))||(side == 0))
            {
                dist = abs(Ludens[i].posX - Ludens[m].posX);
                if (dist < minDist)
                {
                    minDist = dist;
                    min = i;
                }
            }

    return min;
}

void CGame::LudensAttach(int num, int who, int radiusScale, int centerY)
{
    if ((Ludens[num].anchor > -1)||(Ludens[who].anchor > 0))
        return;
    Ludens[num].anchor = who;
    Ludens[num].anchorX = (-Ludens[who].radiusX/radiusScale) + (Engine.random(2*(Ludens[who].radiusX >> FIX)/radiusScale + 1 + centerY) << FIX);
    Ludens[num].anchorY = (-Ludens[who].radiusY/radiusScale) + (Engine.random(2*(Ludens[who].radiusY >> FIX)/radiusScale + 1 + centerY) << FIX);
}

int CGame::LudensCanGo(int num, int direction, bool fallCheck, int radiusScale)
{
    int collision[3];
    bool go, temp, temp2;
    go = temp = temp2 = false;

    if (direction == RIGHT)
    {
        if (fallCheck)
        {
            TestMapCollision(Ludens[num].posX + radiusScale*(TILE_WIDTH << FIX)/2, Ludens[num].posY + (TILE_HEIGHT << FIX), collision);
            if (collision[0] == 1)
                go = true;
        }
        else
            go = true;

        TestMapCollision(Ludens[num].posX + radiusScale*(TILE_WIDTH << FIX)/2, Ludens[num].posY, collision);
        if (collision[0] == 1)
            go = false;
    }

    if (direction == LEFT)
    {
        if (fallCheck)
        {
            TestMapCollision(Ludens[num].posX - radiusScale*(TILE_WIDTH << FIX)/2, Ludens[num].posY + (TILE_HEIGHT << FIX), collision);
            if (collision[0] == 1)
                go = true;
        }
        else
            go = true;

        TestMapCollision(Ludens[num].posX - radiusScale*(TILE_WIDTH << FIX)/2, Ludens[num].posY, collision);
        if (collision[0] == 1)
            go = false;
    }


    if (direction == UP)
    {
        TestMapCollision(Ludens[num].posX - (TILE_WIDTH << FIX) - (6 << FIX), Ludens[num].posY - (TILE_HEIGHT << FIX)/2, collision);
        if (collision[0] == 1)
            temp = true;

        TestMapCollision(Ludens[num].posX + (TILE_WIDTH << FIX) + (6 << FIX), Ludens[num].posY - (TILE_HEIGHT << FIX)/2, collision);
        if (collision[0] == 1)
            temp2 = true;

        go = temp | temp2;

        if (!go)
            if (Ludens[num].interest < 0)
            {
                if (Ludens[num].target == 101)
                    Ludens[num].target = 100;
                else
                    if (Ludens[num].target == 100)
                        Ludens[num].target = 101;

                Ludens[num].interest = 3*ELEVATOR_WAITTIME;
            }
    }

    if (direction == DOWN)
    {
        TestMapCollision(Ludens[num].posX, Ludens[num].posY + ((TILE_HEIGHT-8) << FIX), collision);
        if (collision[0] == 0)
            go = true;

        if (!go)
            if (Ludens[num].interest < 0)
            {
                if (Ludens[num].target == 101)
                    Ludens[num].target = 100;
                else
                    if (Ludens[num].target == 100)
                        Ludens[num].target = 101;

                Ludens[num].interest = 3*ELEVATOR_WAITTIME;
            }
    }

    return go;
}

int CGame::LudensSee(int m, int style, int sightx, int sighty)
{
    int collision[3];
    int distX, distY;
    int OX, OY, TX, TY, stepX, stepY;
    bool visible = false;
    bool left, right, up, down;
    bool tooFar;
    left = right = up = down = false;

    for (int j = 0; j < MAX_LUDENS; j++)
        if (Ludens[j].active)
            if ((Ludens[j].style == style)&&(j != m))
            {
                TX = Ludens[j].posX;
                TY = Ludens[j].posY;
                OX = Ludens[m].posX;
                OY = Ludens[m].posY;
                distX = abs(OX - TX) / COL_STEPS;
                distY = abs(OY - TY) / COL_STEPS;

                tooFar = false;

                if ( (distX > sightx) || (distY > sighty))
                    tooFar = true;

                if (!tooFar)
                {
                    visible = true;

                    if (TX > OX)
                    {
                        stepX = distX;
                        left = true;
                    }
                    else
                    {
                        stepX = -distX;
                        right = true;
                    }
                    if (TY > OY)
                    {
                        stepY = distY;
                        up = true;
                    }
                    else
                    {
                        stepY = -distY;
                        down = true;
                    }

                    for (int i = 0; i < COL_STEPS; i++)
                    {
                        TestMapCollision(OX, OY, collision);
                        if (collision[0] == 1)
                        {
                            left = right = up = down = false;
                            visible = false;
                            break;
                        }
                        OX = OX + stepX;
                        OY = OY + stepY;
                    }
                }

                if ((left)||(right)||(up)||(down))
                    return j;
            }

    return -1;
}

int CGame::LudensCollideOne(int m, int j)
{
    for (int k = 1; k < 10; k++)
        if ( (abs(Ludens[m].oldX + (k-1)*Ludens[m].velX/k - Ludens[j].posX) < Ludens[m].radiusX)
                && (abs(Ludens[m].oldY + (k-1)*Ludens[m].velY/k - Ludens[j].posY) < Ludens[m].radiusY))
        {
            return j;
        }

    return -1;
}

int CGame::LudensCollide(int m, int style, int &any)
{
    int c;
    for (int j = 0; j < MAX_LUDENS; j++)
        if (Ludens[j].active)
            if ((Ludens[j].style == style)&&(j != m))
            {
                c = LudensCollideOne(m, j);
                if (c > -1)
                    return c;
                /*		for (int k = 1; k < 10; k++)
                		if ( (abs(Ludens[m].oldX + (k-1)*Ludens[m].velX/k - Ludens[j].posX) < Ludens[m].radiusX)
                			&& (abs(Ludens[m].oldY + (k-1)*Ludens[m].velY/k - Ludens[j].posY) < Ludens[m].radiusY))
                		{
                			if (any == -1)
                				any = j;
                			return j;
                		}*/
            }

    return -1;
}

void CGame::LudensPush(int num, int style, int direction, bool move)
{
    if (direction == 0)
    {
        if (Ludens[num].posX > Ludens[style].posX)
        {
            if (move)
                Ludens[num].posX = Ludens[style].posX + Ludens[style].radiusX;
            Ludens[num].velX = abs(Ludens[style].velX);
        }
        else
        {
            if (move)
                Ludens[num].posX = Ludens[style].posX - Ludens[style].radiusX;
            Ludens[num].velX = -abs(Ludens[style].velX);
        }
    }

    if (direction == 1)
    {
        if (Ludens[num].posY > Ludens[style].posY)
        {
            if (move)
                Ludens[num].posY = Ludens[style].posY + Ludens[style].radiusY;
            Ludens[num].velY = abs(Ludens[style].velY);
        }
        else
        {
            if (move)
                Ludens[num].posY = Ludens[style].posY - Ludens[style].radiusY;
            Ludens[num].velY = Ludens[style].velY;
        }
    }
}

void CGame::SpawnParts()
{
    int x,y;

    // ashes
    if ((Map.tileSet == VOLCANO_SET)||(Map.tileSet == BLACK_SET)||(Map.tileSet == MINES_SET))
        if (Engine.random(4) == 0)
        {
            x = Engine.random(SCREEN_WIDTH);
            AddPart(P_ASH, (cameraX + x) << FIX, ((MAP_HEIGHT-2) << 5) << FIX);
        }

    //rain
    if (Map.tileSet == HOME_SET)
        if (sceneTimer > INTRO_STARTRAIN)
            if (Engine.random(2) == 0)
            {
                x = Engine.random(SCREEN_WIDTH);
                AddPart(P_RAIN, (cameraX + x - 50) << FIX, (INTRO_JOSEPHY - TILE_HEIGHT*8) << FIX);
            }

    // flow things
    if (Map.tileSet == PLUM_SET)
        if (Engine.random(6) == 0)
        {
            x = Engine.random(SCREEN_WIDTH);
            y = Engine.random(SCREEN_HEIGHT);
            AddPart(P_FLOW, (cameraX + x) << FIX, ((cameraY + y) << FIX));
        }

    // sand
    if (Map.tileSet == OUBLIETTE_SET)
        if (Engine.random(3) == 0)
        {
            y = Engine.random(SCREEN_HEIGHT);
            AddPart(P_SAND, (cameraX) << FIX, (cameraY + y - 50) << FIX);
        }

    //leafs
    if (Map.tileSet == SWAMP_SET)
        if (Engine.random(15) == 0)
        {
            x = Engine.random(SCREEN_WIDTH);
            AddPart(P_LEAFS, (cameraX + x - 50) << FIX, ((cameraY - 30) << FIX));
        }
}

void CGame::PartTick(int num)
{
    Part[num].life--;
    if (Part[num].life<0)
        Part[num].active = false;

    Part[num].oldX = Part[num].posX;
    Part[num].oldY = Part[num].posY;

    Part[num].moveSprite(0, Part[num].gravity);

    if ((Part[num].style == P_SAND)||(Part[num].style == P_FLOW))
        Part[num].moveSprite(Part[num].maxSpeed, 0);

    Part[num].advanceAnimations();

    Part[num].convertPosition();
}

void CGame::SpriteDraw(CSprite &Sprite)
{
    Engine.Blit(Sprite.ActiveImage[Sprite.anims[Sprite.animNum].animList[Sprite.animTick]],
                Sprite.screenX - cameraX - Sprite.refX, Sprite.screenY - cameraY - Sprite.refY);
}

void CGame::DrawTileMap(int cX, int cY)
{
    int i, j, t, k;
    int MX, MY, SW, SH, OX, OY;

    SW = (SCREEN_WIDTH / TILE_WIDTH) + 2;
    SH = (SCREEN_HEIGHT / TILE_HEIGHT) + 2;
    MX = (cX >> 5);
    MY = (cY >> 5);
    OX = (cX % TILE_WIDTH);
    OY = (cY % TILE_HEIGHT);

    for (i=0; i<SW; i++)
        for (j=0; j<SH; j++)
            if ((((MX + i) > -1)&&((MX + i) < MAP_WIDTH))&&(((MY + j) > -1)&&((MY + j) < MAP_HEIGHT)))
            {
                t = Map.tiles[MY + j][MX + i];
                //if (t>-1)
				if (t > 0)
                {
                    Engine.Blit(Map.TilesBitmap[t], (i << 5) - OX, (j << 5) - OY);
                }
            }

    for (j=0; j<SH; j++)
        for (i=0; i<SW; i++)
            if ((((MX + i) > -1)&&((MX + i) < MAP_WIDTH))&&(((MY + j) > -1)&&((MY + j) < MAP_HEIGHT)))
            {
                t = Map.tiles[MY + j][MX + i];
				if (t == 0)
                {
					for (k=i; k<SW; k++)
					{
						t = Map.tiles[MY + j][MX + k];
						if (t > 0)
							break;
					}
					Engine.DrawRectangle((i << 5) - OX, (j << 5) - OY, (k-i)*TILE_WIDTH, TILE_HEIGHT, Map.foregroundRed, Map.foregroundGreen, Map.foregroundBlue);
					i = k;
                }
            }

    if (miniMap)
        Engine.Blit(MiniMap, 1, 2*SCREEN_HEIGHT/3);
}

char *CGame::filePlusDir(char *file)
{
    char *ret;
    ret = new char[strlen(RootDirectory)+strlen(file)+1];
    strcpy(ret, RootDirectory);
    strcat(ret, file);
    return ret;
}

char *CGame::mapFile(char *file)
{
    char *ret;
    ret = new char[2+strlen(file)+4+1];
    strcpy(ret, "m/");
    strcat(ret, file);
    strcat(ret, ".rmp");
    return ret;
}

void CGame::SortDrawList()
{
    int i, j;
    int il, c;
    CSprite *temp;

    for (i=0; i<MAX_SPRITES; i++)
    {
        DrawList[i] = NULL;
    }

    il = 0;
    for (i=0; i<MAX_LUDENS; i++)
        if (Ludens[i].active)
        {
            DrawList[il] = &Ludens[i];
            il++;
        }
    c = il;
    for (i=c; i<(c+MAX_PART); i++)
        if (Part[i-c].active)
        {
            DrawList[il] = &Part[i-c];
            il++;
        }

    for (i = 0; i < (il); i++)
    {
        for (j = i; j < (il); j++)
        {
            if ((DrawList[i]->posY + DrawList[i]->refY) > (DrawList[j]->posY+DrawList[j]->refY))
            {
                temp = DrawList[i];
                DrawList[i] = DrawList[j];
                DrawList[j] = temp;
            }
        }
    }
}

int CGame::LoadTileMap(char *fileName)
{
    int i, j;
    int c;
    MapSprite ms;
    MapHeader hd;
    // kill sprites
    for (i=0; i<MAX_LUDENS; i++)
        Ludens[i].kill();
    for (i=0; i<MAX_PART; i++)
        Part[i].kill();

    cameraX = 0;
    cameraY = 0;
    cameraVX = 0;
    cameraVY = 0;
    startSecret = false;
    ResetMusicCheck();
    Dialog.RestartDialog();
    myLudens = -1;
    dialogStep = sceneTimer = 0;
    choiceMenu = false;
	terminalLayer = terminalPos = terminalTextPos = 0;
	bagsPicked = 0;

    //GoalTicks = DEFAULT_GOALTICKS;
    //Number27Timing();

    FILE *pFile = fopen(fileName, "rb");
    if (pFile==NULL)
        return 0;
    fread(&hd, sizeof(MapHeader), 1, pFile);
    Map.tileSet = hd.tilesSet;
    switch (Map.tileSet)
    {
    case HOME_SET :
        Map.TilesBitmap = HomeImage;
        break;
    case VOLCANO_SET :
        Map.TilesBitmap = VolcanoImage;
        break;
    case SWAMP_SET :
        Map.TilesBitmap = SwampImage;
        break;
    case OUBLIETTE_SET :
        Map.TilesBitmap = OublietteImage;
        break;
    case END_SET :
        Map.TilesBitmap = EndImage;
        break;
    case PLUM_SET :
        Map.TilesBitmap = PlumImage;
        break;
    case BLACK_SET :
        Map.TilesBitmap = BlackImage;
        break;
    case MINES_SET :
        Map.TilesBitmap = MinesImage;
        break;
    default :
        Map.TilesBitmap = HomeImage;
        break;
    }
    Map.backgroundRed = hd.backgroundRed;
    Map.backgroundGreen = hd.backgroundGreen;
    Map.backgroundBlue = hd.backgroundBlue;
    for (i=0; i<MAX_LUDENS; i++)
    {
        fread(&ms, sizeof(MapSprite), 1, pFile);
        if (ms.style > -1)
        {
            j = AddLudens(ms.style, ms.x, ms.y, i);
            //j = AddLudens(ms.style, ms.x, ms.y, ms.id);
            Ludens[j].attitude = ms.attitude;
            if (ms.direction == RIGHT)
            {
                Ludens[j].setAnimation(Ludens[j].animNum, Ludens[j].animSpeed, RIGHT, Ludens[j].animBlock, Ludens[j].animLoop);
                Ludens[j].animDirection = RIGHT;
            }
            else
            {
                Ludens[j].setAnimation(Ludens[j].animNum, Ludens[j].animSpeed, LEFT, Ludens[j].animBlock, Ludens[j].animLoop);
                Ludens[j].animDirection = LEFT;
            }
            Ludens[j].animDirection = ms.direction;
            Ludens[j].target = ms.target;
            if ((ms.style == HERO)&&(myLudens == -1))
            {
                myLudens = j;
                //	startLudens = AddLudens(EXIT, Ludens[j].posX, Ludens[j].posY);
                //	if (startLudens > -1)
                //		Ludens[startLudens].attitude = 1;
                cameraVX = Ludens[j].posX;
                cameraVY = Ludens[j].posY;
            }
            if ((mapNum >= ZORTHPLAY_MAP)&&(mapNum <= ZORTHEND_MAP))
                if ((ms.style == ZORTH)&&(myLudens == -1))
                {
                    myLudens = j;
                    cameraVX = Ludens[j].posX;
                    cameraVY = Ludens[j].posY;
                }
        }
    }
    LudensResolveDependencies();
    for (i=0; i<MAP_WIDTH; i++)
        for (j=0; j<MAP_HEIGHT; j++)
        {
            fread(&c, sizeof(int), 1, pFile);
            Map.tiles[j][i] = c;
        }
    fclose (pFile);
    // create mini map
    Engine.CreateSurface(MiniMap, MAP_WIDTH*2, MAP_HEIGHT*2);
    for (i=0; i<MAP_WIDTH; i++)
        for (j=0; j<MAP_HEIGHT; j++)
        {
            if (!Map.tiles[j][i])
            {
                Engine.BlitTo(MiniImage[0], MiniMap, i*2, j*2);
            }
        }

	// get foregorund color
	int fcolor = Engine.GetPixel(0, 0, Map.TilesBitmap->Surface);
	Map.foregroundRed = Engine.GetColor(fcolor, 0);
	Map.foregroundGreen = Engine.GetColor(fcolor, 1);
	Map.foregroundBlue = Engine.GetColor(fcolor, 2);

    // Interrupt
    interruptCount++;
    if (interruptCount > 16)
        if (Engine.random(4) == 0)
        {
            interruptTimer = 120;
            interruptNum = 0;
            interruptCount = 0;
        }

	if (mapNum == 26)
      for (int i=0; i<CREDITS_NUM; i++)
        CreditsY[i] = 1.3*SCREEN_HEIGHT + 2*i*MENU_SPACE;


    //for (i=0; i<MAX_LUDENS; i++)
    //	if (Ludens[i].style == CRAB)
    //		Ludens[i].kill();
    return hd.tilesSet;
}
int CGame::SaveTileMap(char *fileName)
{
    int i, j;
    int c;
    MapHeader hd;
    MapSprite ms;
    hd.tilesSet = Map.tileSet;
    hd.backgroundRed = Map.backgroundRed;
    hd.backgroundGreen = Map.backgroundGreen;
    hd.backgroundBlue = Map.backgroundBlue;
    FILE *pFile = fopen(fileName,"wb");

    fwrite(&hd, sizeof(MapHeader), 1, pFile);

    for (i=0; i<MAX_LUDENS; i++)
    {
        if (Ludens[i].active)
        {
            //if (i != startLudens)
            {
				ms.style = Ludens[i].style;
                ms.x = Ludens[i].posX;
                ms.y = Ludens[i].posY;
                ms.attitude = Ludens[i].attitude;
                ms.direction = Ludens[i].animDirection;
                ms.target = Ludens[i].target;
                ms.id = i;
            }
        }
        else
        {
            ms.style = -1;
            ms.x = 0;
            ms.y = 0;
        }
        fwrite(&ms, sizeof(MapSprite), 1, pFile);
    }

    for (i=0; i<MAP_WIDTH; i++)
        for (j=0; j<MAP_HEIGHT; j++)
        {
            c = Map.tiles[j][i];
            fwrite(&c, sizeof(int), 1, pFile);
        }

    fclose(pFile);
    return 1;
}
void CGame::NextMap()
{
    char *map;
    char num[3];

    if (cutScene)
        MusicFadeOut = 9;

    mapNum++;

    //if (mapNum == 11)
    //	mapNum = 1;

    if (mapNum > level)
        level = mapNum;

    SaveGame();

    itoa (mapNum, num, 10);
    map = new char[2+strlen(mapName)+strlen(num)+4+1];
    strcpy(map, "m/");
    strcat(map, mapName);
    strcat(map, num);
    strcat(map, ".rmp");

    mapFileName = map;

    LoadTileMap(filePlusDir(map));

    ProcessCutScene(mapNum);
    if (cutScene)
    {
        StartCutScene();

        if ((mapNum+1) > level)
            level = mapNum+1;
    }
    //else
    //	Engine.Sound.PlaySample(6);

    Ludens[myLudens].idleCounter = 20;
    sceneTimer = 0;
    showHint = false;
    interruptCount = 0;
    interruptTimer = -1;

    // center caption on episodes
    centerCaption = "";
    centerCaptionTimer = CENTERCAPTION_TIME;
	if (mapNum == 26)
		centerCaptionTimer = 2*CENTERCAPTION_TIME;
    if (!cutScene)
        centerCaption = Levels[mapNum];

    //pick music
    int m = DecideMusic();
    if ((m != currentMusic)&&(m > -1))
    {
        currentMusic = m;
        MusicFadeOut = Engine.Sound.DefaultVolume;
    }

    //	for (int i=0; i<1500; i++)
    //		Engine.Delay(1);

}

void CGame::MyLudensDie()
{
	if (myLudens > -1)
		if (Ludens[myLudens].style == HERO)		
			Ludens[myLudens].setAnimation(ANIM_HERO_DIE, 1, Ludens[myLudens].animDirection, false, false);
		else
		{
			for (int i = 0; i < MAX_SPRITES; i++)
				if ((Ludens[i].active)&&(Ludens[i].style == HERO))
					Ludens[i].setAnimation(ANIM_HERO_DIE, 1, Ludens[i].animDirection, false, false);
		}
}
int CGame::LoadGame()
{
    FILE *pFile = fopen(filePlusDir("state.sav"), "rb");
    if (pFile==NULL)
        return 0;
    fread(&Engine.Config, sizeof(Engine.Config), 1, pFile);
    mapNum = Engine.Config.mapNum ^ XORVALUE;
    level = Engine.Config.tilesSet ^ XORVALUE;
    Engine.Sound.playMusics = (bool)Engine.Config.music;
    Engine.Sound.playSounds = (bool)Engine.Config.sound;


    return Engine.Config.tilesSet;
}
int CGame::SaveGame()
{
    FILE *pFile = fopen(filePlusDir("state.sav"),"wb");

    Engine.Config.tilesSet = level ^ XORVALUE;
    Engine.Config.mapNum = (mapNum-1) ^ XORVALUE;

    fwrite(&Engine.Config, sizeof(Engine.Config), 1, pFile);

    fclose(pFile);
    return 1;
}
// // // // // //
// MENU (menuLayer) menuPos
// (0) 0 continue game (1)
//     1 load game         0 back
//                         1 levels
//     2 options       (2) 0 keys
//										(3) 0 left
//										    1 right
//										    2 jump
//										    3 umbrella hit/open
//										    4 minimap
//										    5 load default
//										    4 back
//						   1 display	(4) 0 fullscreen
//										    1 limit fps
//										    2 back
//						   2 sound  	(5) 0 sound
//										    1 music
//										    2 back
//						   3 back
//     3 credits	   (6)
//     4 exit
bool CGame::Menu()
{
    int Positions = 0;
    bool Go = false;
    int i;

	usingTerminal = false;

    if ((!Engine.key_up)&&(!Engine.key_down)&&(!Engine.key_action))
        canMenuPos = true;

    if (canMenuPos)
    {
        if ((setKeys)&&(Engine.key_pressed > 0)&&(Engine.key_pressed != 300))
        {
            switch (settingKey)
            {
            case 0:
                Engine.Config.conf_keyleft = Engine.key_pressed;
                break;
            case 1:
                Engine.Config.conf_keyright = Engine.key_pressed;
                break;
            case 2:
                Engine.Config.conf_keyjump = Engine.key_pressed;
                break;
            case 3:
                Engine.Config.conf_keyduck = Engine.key_pressed;
                break;
            case 4:
                Engine.Config.conf_keyfire = Engine.key_pressed;
                break;
            case 5:
                Engine.Config.conf_key1 = Engine.key_pressed;
                break;
            }
            setKeys = false;
            canMenuPos = false;
            return true;
		}
        if (Engine.key_up)
        {
            menuPos--;
            canMenuPos = false;
        }
        if (Engine.key_down)
        {
            menuPos++;
            canMenuPos = false;
        }
        if (Engine.key_action)
        {
            Go = true;
            canMenuPos = false;
        }
    }
    switch (menuLayer)
    {
    case 0 :
        if (Go)
        {
            if (menuPos == 0)
            {   //continue game
                Engine.key_fire = false;
                Engine.Sound.PauseChannel(Engine.Sound.SpecialChannel, false);
                return false;
            }
            if (menuPos == 1)
            {
                menuLayer = 1;
                menuPos = 0;
                return true;
            }
            if (menuPos == 2)
            {
                menuLayer = 2;
                menuPos = 0;
                return true;
            }
            if (menuPos == 3)
            {
                menuLayer = 6;
                menuPos = 0;
                //currentMODfile = "s/rc.it";
                //Engine.Sound.PlayMOD(currentMODfile);
                for (i=0; i<CREDITS_NUM; i++)
                    CreditsY[i] = SCREEN_HEIGHT + 2*i*MENU_SPACE;
                return true;
            }
            if (menuPos == 4)
            {
                isRunning = false;
                SaveGame();
                return false;
            }
        }
        Positions = 5;
        break;
    case 1 :
        if (Go)
        {
            if (menuPos == 0)
            {
                menuLayer = 0;
                menuPos = 1;
                return true;
            }
            if (menuPos > 0) // select level
            {
                mapNum = menuPos-2;
                NextMap();
                //		mapNum = -1;
                //		mapName = "map";
                //		NextMap();
                return false;
            }
        }
        Positions = 2 + level;
        break;
    case 2 :
        if (Go)
        {
            if (menuPos == 0)
            {
                menuLayer = 3;
                menuPos = 0;
                return true;
            }
            if (menuPos == 1)
            {
                menuLayer = 4;
                menuPos = 0;
                return true;
            }
            if (menuPos == 2)
            {
                menuLayer = 5;
                menuPos = 0;
                return true;
            }
            if (menuPos == 3)
            {
                menuLayer = 0;
                menuPos = 2;
                return true;
            }
        }
        Positions = 4;
        break;
    case 3 : // keys
        if (Go)
        {
            if (menuPos == 0) // left
            {
                setKeys = true;
                settingKey = 0;
                return true;
            }
            if (menuPos == 1) // right
            {
                setKeys = true;
                settingKey = 1;
                return true;
            }
            if (menuPos == 2)
            {
                setKeys = true;
                settingKey = 2;
                return true;
            }
            if (menuPos == 3)
            {
                setKeys = true;
                settingKey = 3;
                return true;
            }
            if (menuPos == 4)
            {
                setKeys = true;
                settingKey = 4;
                return true;
            }
            if (menuPos == 5)
            {
                setKeys = true;
                settingKey = 5;
                return true;
            }
            if (menuPos == 6) // load defaults
            {
                //LoadDefaultConfig(Engine.Config);
                Engine.Config.conf_key1 = 0;
                Engine.Config.conf_keyfire = 0;
                Engine.Config.conf_keyleft = 0;
                Engine.Config.conf_keyright = 0;
                Engine.Config.conf_keyjump = 0;
                Engine.Config.conf_keyduck = 0;
                return true;
            }
            if (menuPos == 7)
            {
                menuLayer = 2;
                menuPos = 0;
                return true;
            }
        }
        Positions = 8;
        break;
    case 4 :
        if (Go)
        {
            if (menuPos == 0)
            {
                if (Engine.Config.fullscreen == 0)
                    Engine.Config.fullscreen = 1;
                else
                    Engine.Config.fullscreen = 0;
                return true;
            }
            if (menuPos == 1)
            {
                if (Engine.Config.limitfps == 0)
                    Engine.Config.limitfps = 1;
                else
                    Engine.Config.limitfps = 0;
                return true;
            }
            if (menuPos == 2)
            {
                menuLayer = 2;
                menuPos = 1;
                return true;
            }
        }
        Positions = 3;
        break;
    case 5 :
        if (Go)
        {
            if (menuPos == 0)
            {
                if (Engine.Config.sound == 0)
                    Engine.Config.sound = 1;
                else
                    Engine.Config.sound = 0;
                Engine.Sound.playSounds = (bool)Engine.Config.sound;
                return true;
            }
            if (menuPos == 1)
            {
                if (Engine.Config.music == 0)
                {
                    Engine.Config.music = 1;
                    Engine.Sound.playMusics = (bool)Engine.Config.music;
                    //Engine.Sound.PlayMOD(currentMODfile);
                    //currentMusic = DecideMusic();
                    //Engine.Sound.PlayMusic(currentMusic);
                    Engine.Sound.PauseMusic(false);
                }
                else
                {
                    Engine.Config.music = 0;
                    Engine.Sound.playMusics = (bool)Engine.Config.music;
                    //						Engine.Sound.StopMOD();
                    Engine.Sound.PauseMusic(true);
                }
                return true;
            }
            if (menuPos == 2)
            {
                menuLayer = 2;
                menuPos = 2;
                return true;
            }
        }
        Positions = 3;
        break;
    case 6 :
        if (Go)
        {
            if (menuPos == 0)
            {
                menuLayer = 0;
                menuPos = 3;
                return true;
            }
        }
        Positions = 1;
        for (i=0; i<CREDITS_NUM; i++)
            if (CreditsY[i] > 1*MENU_STARTY + i*MENU_SPACE)
                CreditsY[i]--;
        break;
    }
    if (menuPos < 0)
        menuPos = Positions-1;
    if (menuPos > (Positions-1))
        menuPos = 0;
    cursorY++;
    if (cursorY > 1)
        cursorY = 0;
    return true;
}
void CGame::DrawMenu()
{
    //	drawString(Engine.Screen, Engine.font, 0, 20, buffer);
    //	Engine.DrawRectangle(3, 3, 21*MENU_STARTX, SCREEN_HEIGHT-16, 0, 0, 0);
    if (Map.tileSet == END_SET)
        Engine.menufont = Engine.blackfont;
    else
        Engine.menufont = Engine.font;

    switch (menuLayer)
    {
    case 0 :
        drawString(Engine.Screen, Engine.menufont, 0, 0, "Game:");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 0*MENU_SPACE, "Continue");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 1*MENU_SPACE, "Select");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 2*MENU_SPACE, "Options");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 3*MENU_SPACE, "Credits");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 4*MENU_SPACE, "Exit");
        drawString(Engine.Screen, Engine.menufont, 3, MENU_STARTY + menuPos*MENU_SPACE + 2 + cursorY, "*");
        break;
    case 1 :
        int i;
        char buffer[10];

        drawString(Engine.Screen, Engine.menufont, 0, 0, "Select level:");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 0*MENU_SPACE, "Back");
        for (i=0; i<level+1; i++)
        {
            itoa(i,buffer,10);
            drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + (i+1)*MENU_SPACE, buffer);
            drawString(Engine.Screen, Engine.menufont, MENU_STARTX + 30, MENU_STARTY + (i+1)*MENU_SPACE, Levels[i]);
        }
        /*			drawString(Engine.Screen, Engine.menufont, 0, MENU_SPACE, "Are you sure?");
        			drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 1*MENU_SPACE, "No");
        			drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 2*MENU_SPACE, "Yes");*/
        drawString(Engine.Screen, Engine.menufont, 3, MENU_STARTY + (menuPos)*MENU_SPACE + 2 + cursorY, "*");
        break;
    case 2 :
        drawString(Engine.Screen, Engine.menufont, 0, 0, "Options:");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 0*MENU_SPACE, "Keys");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 1*MENU_SPACE, "Display");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 2*MENU_SPACE, "Sound");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 3*MENU_SPACE, "Back");
        drawString(Engine.Screen, Engine.menufont, 3, MENU_STARTY + menuPos*MENU_SPACE + 2 + cursorY, "*");
        break;
    case 3 :
        if (!setKeys)
            drawString(Engine.Screen, Engine.menufont, 0, 0, "Keys:");
        else
            drawString(Engine.Screen, Engine.menufont, 0, 0, "Press key...");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 0*MENU_SPACE, "Left");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 1*MENU_SPACE, "Right");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 2*MENU_SPACE, "Jump");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 3*MENU_SPACE, "Duck");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 4*MENU_SPACE, "Umbrella Hit/Open");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 5*MENU_SPACE, "Mini Map");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 6*MENU_SPACE, "Load Defaults");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 7*MENU_SPACE, "Back");
        if (Engine.Config.conf_keyleft == 0)
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 0*MENU_SPACE, "default");
        else
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 0*MENU_SPACE, "custom");
        if (Engine.Config.conf_keyright == 0)
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 1*MENU_SPACE, "default");
        else
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 1*MENU_SPACE, "custom");
        if (Engine.Config.conf_keyjump == 0)
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 2*MENU_SPACE, "default");
        else
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 2*MENU_SPACE, "custom");
        if (Engine.Config.conf_keyduck == 0)
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 3*MENU_SPACE, "default");
        else
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 3*MENU_SPACE, "custom");
        if (Engine.Config.conf_keyfire == 0)
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 4*MENU_SPACE, "default");
        else
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 4*MENU_SPACE, "custom");
        if (Engine.Config.conf_key1 == 0)
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 5*MENU_SPACE, "default");
        else
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 5*MENU_SPACE, "custom");
        drawString(Engine.Screen, Engine.menufont, 3, MENU_STARTY + menuPos*MENU_SPACE + 2 + cursorY, "*");
        break;
    case 4 :
        drawString(Engine.Screen, Engine.menufont, 0, 0, "Display:");
        if (menuPos == 0)
            drawString(Engine.Screen, Engine.menufont, 0, MENU_STARTY + 5*MENU_SPACE, "Setting requires game restart");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 0*MENU_SPACE, "Fullscreen");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 1*MENU_SPACE, "Limit FPS");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 2*MENU_SPACE, "Back");

        if (Engine.Config.fullscreen == 0)
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 0*MENU_SPACE, "no");
        else
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 0*MENU_SPACE, "yes");
        if (Engine.Config.limitfps == 0)
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 1*MENU_SPACE, "no");
        else
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 1*MENU_SPACE, "yes");
        drawString(Engine.Screen, Engine.menufont, 3, MENU_STARTY + menuPos*MENU_SPACE + 2 + cursorY, "*");
        break;
    case 5 :
        drawString(Engine.Screen, Engine.menufont, 0, 0, "Sound:");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 0*MENU_SPACE, "Sound");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 1*MENU_SPACE, "Music");
        drawString(Engine.Screen, Engine.menufont, MENU_STARTX, MENU_STARTY + 2*MENU_SPACE, "Back");
        if (Engine.Config.sound == 0)
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 0*MENU_SPACE, "no");
        else
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 0*MENU_SPACE, "yes");
        if (Engine.Config.music == 0)
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 1*MENU_SPACE, "no");
        else
            drawString(Engine.Screen, Engine.menufont, 13*MENU_STARTX, MENU_STARTY + 1*MENU_SPACE, "yes");
        drawString(Engine.Screen, Engine.menufont, 3, MENU_STARTY + menuPos*MENU_SPACE + 2 + cursorY, "*");
        break;
    case 6 :
        drawString(Engine.Screen, Engine.menufont, 0, 0, "Credits:");

        drawString(Engine.Screen, Engine.menufont, SCREEN_WIDTH/2 - 4, CreditsY[0], "R");
        drawString(Engine.Screen, Engine.menufont, SCREEN_WIDTH/2 - 11, CreditsY[1], "***");
        	drawString(Engine.Screen, Engine.menufont, 3*MENU_STARTX, CreditsY[2], "made by");
			drawString(Engine.Screen, Engine.menufont, 4*MENU_STARTX, CreditsY[3], "programming");
        	drawString(Engine.Screen, Engine.menufont, 5*MENU_STARTX, CreditsY[4], "Michal Marcinkowski");
        	drawString(Engine.Screen, Engine.menufont, 4*MENU_STARTX, CreditsY[5], "graphics");
        	drawString(Engine.Screen, Engine.menufont, 5*MENU_STARTX, CreditsY[6], "Matt Plant & Michal Marcinkowski");
        	drawString(Engine.Screen, Engine.menufont, 4*MENU_STARTX, CreditsY[7], "music and sound");
        	drawString(Engine.Screen, Engine.menufont, 5*MENU_STARTX, CreditsY[8], "Michal Marcinkowski");
        	drawString(Engine.Screen, Engine.menufont, 6*MENU_STARTX, CreditsY[9], "(except 'Yakety Sax' by Boots Randolph, & Vivaldi and Debussy excerpts)");
        	drawString(Engine.Screen, Engine.menufont, 4*MENU_STARTX, CreditsY[10], "story, concepts and creature design");
        	drawString(Engine.Screen, Engine.menufont, 5*MENU_STARTX, CreditsY[11], "Dolny, Michal Marcinkowski & Matt Plant");
        	drawString(Engine.Screen, Engine.menufont, 4*MENU_STARTX, CreditsY[12], "maps and puzzles");
        	drawString(Engine.Screen, Engine.menufont, 5*MENU_STARTX, CreditsY[13], "Michal Marcinkowski");
        	drawString(Engine.Screen, Engine.menufont, 4*MENU_STARTX, CreditsY[14], "books, dialogs and lyrics");
        	drawString(Engine.Screen, Engine.menufont, 5*MENU_STARTX, CreditsY[15], "Michal Marcinkowski");
        	drawString(Engine.Screen, Engine.menufont, 6*MENU_STARTX, CreditsY[16], "");
        drawString(Engine.Screen, Engine.menufont, 1*MENU_STARTX, CreditsY[17], "Check out MM's latest game Crimson Glory:");
        drawString(Engine.Screen, Engine.menufont, 1*MENU_STARTX, CreditsY[18], "http://www.crimsoneengine.com");
		drawString(Engine.Screen, Engine.menufont, 1*MENU_STARTX, CreditsY[19], "Also be sure to check out MM's other game Soldat:");
        drawString(Engine.Screen, Engine.menufont, 1*MENU_STARTX, CreditsY[20], "http://www.soldat.pl");
		drawString(Engine.Screen, Engine.menufont, 1*MENU_STARTX, CreditsY[21], "To contact the team e-mail: michal.marcinkowski@gmail.com");
        break;
    }
    return;
}
void CGame::LoadDefaultConfig(ConfigHeader &cfg)
{
    cfg.conf_key1 = 0;
    cfg.conf_keyfire = 0;
    cfg.conf_keyleft = 0;
    cfg.conf_keyright = 0;
    cfg.conf_keyjump = 0;
    cfg.conf_keyduck = 0;
    cfg.fullscreen = 1;
    cfg.limitfps = 1;
    cfg.music = 1;
    cfg.sound = 1;
    cfg.mapNum = -1;
    cfg.tilesSet = 0;
    Engine.Sound.playMusics = (bool)cfg.music;
    Engine.Sound.playSounds = (bool)cfg.sound;
    mapName = "map";
    mapNum = cfg.mapNum;
    level = cfg.tilesSet;
}

int CGame::DecideMusic()
{
//	return -1;

    if ((mapNum>0)&&(mapNum<4))
	{
		if (Engine.Sound.music[1] == 0)
			Engine.Sound.music[1] = Engine.LoadSound(filePlusDir("s/m/itmust.wav"));
        return 1;
	}
    if (mapNum == 4)
	{
		if (Engine.Sound.music[2] == 0)
			Engine.Sound.music[2] = Engine.LoadSound(filePlusDir("s/m/run.wav"));
        return 2;
	}
    if ((mapNum>4)&&(mapNum<9))
	{
		if (Engine.Sound.music[3] == 0)
			Engine.Sound.music[3] = Engine.LoadSound(filePlusDir("s/m/rot.wav"));
        return 3;
	}
    if ((mapNum>10)&&(mapNum<15))
	{
		if (Engine.Sound.music[4] == 0)
			Engine.Sound.music[4] = Engine.LoadSound(filePlusDir("s/m/ryk.wav"));
        return 4;
	}
    if ((mapNum>17)&&(mapNum<21)) // Mines
	{
		if (Engine.Sound.music[5] == 0)
			Engine.Sound.music[5] = Engine.LoadSound(filePlusDir("s/m/reading.wav"));
        return 5;
	}
    if ((mapNum>20)&&(mapNum<24)) // Hypothesis
	{
		if (Engine.Sound.music[4] == 0)
			Engine.Sound.music[4] = Engine.LoadSound(filePlusDir("s/m/ryk.wav"));
        return 4;
	}
    if ((mapNum>23)&&(mapNum<26)) // Wizard
	{
		if (Engine.Sound.music[7] == 0)
			Engine.Sound.music[7] = Engine.LoadSound(filePlusDir("s/m/reading2.wav"));
        return 7;
	}

    if (mapNum == 9) //hoverboard
	{
		if (Engine.Sound.music[0] == 0)
			Engine.Sound.music[0] = Engine.LoadSound(filePlusDir("s/m/rww1.wav"));
        return 0;
	}
    if (mapNum == 16) //hoverboard2
	{
		if (Engine.Sound.music[8] == 0)
		Engine.Sound.music[8] = Engine.LoadSound(filePlusDir("s/m/relhard.wav"));

		return 8;
	}
    if (mapNum == 26)
	{
		if (Engine.Sound.music[6] == 0)
			Engine.Sound.music[6] = Engine.LoadSound(filePlusDir("s/m/rr.wav"));
        return 6;
	}
    return -1;
}
void CGame::DeleteTile(int tx, int ty)
{
    Map.setCell(tx, ty, -1);
    if (Map.getCell(tx - 1, ty) != 0)
        Map.setCell(tx - 1, ty, -1);
    if (Map.getCell(tx + 1, ty) != 0)
        Map.setCell(tx + 1, ty, -1);
    if (Map.getCell(tx, ty - 1) != 0)
        Map.setCell(tx, ty - 1, -1);
    if (Map.getCell(tx, ty + 1) != 0)
        Map.setCell(tx, ty + 1, -1);

    PlaceModTile(tx, ty);
    PlaceModTile(tx - 1, ty);
    PlaceModTile(tx + 1, ty);
    PlaceModTile(tx, ty - 1);
    PlaceModTile(tx, ty + 1);
}
