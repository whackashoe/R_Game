#include "preheader.h"
#include "engine.h"

int CEngine::InitSystem()
{
    int retry = 0;
    int params = SCREEN_PARAMS;

    loadIndex = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 0;

    atexit(SDL_Quit);

    /*if (Config.fullscreen)
    {
    	params = (params | SDL_FULLSCREEN);
    	RealScreen = SDL_SetVideoMode(SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SCREEN_BITS, params);
    	Screen = SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT + 6, SCREEN_BITS, rmask, gmask, bmask, amask);
    	Screen = SDL_DisplayFormat(Screen);
    	FilterScreen = SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SCREEN_BITS, rmask, gmask, bmask, amask);
    	FilterScreen = SDL_DisplayFormat(FilterScreen);
    	Filters.filter_init_2xsai(565);
    	flagFullscreen = true;
    } 
    else*/

    if (Config.fullscreen)
        //if (1==0)
    {
        RealScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITS, params | SDL_FULLSCREEN);
        flagFullscreen = true;
    }
    else
    {
        RealScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITS, params);
        flagFullscreen = false;
        //SDL_WM_IconifyWindow();
    }
    Screen = RealScreen;

    if (!RealScreen)
        return 0;

    SDL_ShowCursor(SDL_DISABLE);

    SDL_WM_SetCaption("R", NULL);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN

    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else

    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    bool sb = Sound.Init(44100, 32, FSOUND_MIXER_AUTODETECT);
    while ((!Sound.Init(44100, 32, FSOUND_MIXER_AUTODETECT))&&(retry<10))
    {
    	Delay(100);
    	retry++;
    }

    Randomize();

    LastVideoError = "version 0.9";

    return 1;
}

void CEngine::CheckSystemEvents(bool &run)
{
    int i;

    SDL_PollEvent(&Event);

    if (Event.type == SDL_QUIT)
        run = false;
    else
        run = true;

    if (Event.type == SDL_SYSWMEVENT)
        run = false;
    else
        run = true;

    //update keylist
    static Uint8 *keylist = SDL_GetKeyState(NULL);
    SDL_PumpEvents();
    //key_up, key_down, key_right, key_left;

    key_pressed = 0;
    for (i=0; i<SDLK_LAST; i++)
        if (keylist[i])
        {
            key_pressed = i;
            break;
        }

    if (keylist[SDLK_ESCAPE])
        key_esc=true;
    else
        key_esc=false;
    if (keylist[SDLK_e])
        key_e=true;
    else
        key_e=false;
    if (keylist[SDLK_r])
        key_r=true;
    else
        key_r=false;
    if (keylist[SDLK_z])
        key_z=true;
    else
        key_z=false;
    if (keylist[SDLK_x])
        key_x=true;
    else
        key_x=false;
    if (keylist[SDLK_c])
        key_c=true;
    else
        key_c=false;
    if (keylist[SDLK_t])
        key_t=true;
    else
        key_t=false;
    if (keylist[SDLK_l])
        key_l=true;
    else
        key_l=false;
    if (keylist[SDLK_q])
        key_q=true;
    else
        key_q=false;
    if (keylist[SDLK_s])
        key_s=true;
    else
        key_s=false;
    if (keylist[SDLK_v])
        key_v=true;
    else
        key_v=false;
    if (keylist[SDLK_b])
        key_b=true;
    else
        key_b=false;
    if (keylist[SDLK_m])
        key_m=true;
    else
        key_m=false;
    if (keylist[SDLK_n])
        key_n=true;
    else
        key_n=false;
    if (keylist[SDLK_a])
        key_a=true;
    else
        key_a=false;
    if (keylist[SDLK_d])
        key_d=true;
    else
        key_d=false;
    if (keylist[SDLK_i])
        key_i=true;
    else
        key_i=false;
    if (keylist[SDLK_o])
        key_o=true;
    else
        key_o=false;
    if (keylist[SDLK_p])
        key_p=true;
    else
        key_p=false;
    if (keylist[SDLK_k])
        key_k=true;
    else
        key_k=false;
    if (keylist[SDLK_h])
        key_h=true;
    else
        key_h=false;
    if (keylist[SDLK_y])
        key_y=true;
    else
        key_y=false;
    if (keylist[SDLK_u])
        key_u=true;
    else
        key_u=false;
    if (keylist[SDLK_w])
        key_w=true;
    else
        key_w=false;
    if (keylist[SDLK_g])
        key_g=true;
    else
        key_g=false;
    if (keylist[SDLK_r])
        key_r=true;
    else
        key_r=false;
    if (keylist[SDLK_j])
        key_j=true;
    else
        key_j=false;
    if (keylist[SDLK_f])
        key_f=true;
    else
        key_f=false;

    if (keylist[SDLK_F1])
        key_f1=true;
    else
        key_f1=false;
    if (keylist[SDLK_F5])
        key_f5=true;
    else
        key_f5=false;
    if (keylist[SDLK_F6])
        key_f6=true;
    else
        key_f6=false;
    if (keylist[SDLK_F7])
        key_f7=true;
    else
        key_f7=false;
    if (keylist[SDLK_F8])
        key_f8=true;
    else
        key_f8=false;
    if (keylist[SDLK_F9])
        key_f9=true;
    else
        key_f9=false;
    if (keylist[SDLK_F10])
        key_f10=true;
    else
        key_f10=false;

    if (keylist[SDLK_1])
        key_1=true;
    else
        key_1=false;
    if (keylist[SDLK_2])
        key_2=true;
    else
        key_2=false;
    if (keylist[SDLK_3])
        key_3=true;
    else
        key_3=false;
    if (keylist[SDLK_4])
        key_4=true;
    else
        key_4=false;
    if (keylist[SDLK_5])
        key_5=true;
    else
        key_5=false;
    if (keylist[SDLK_6])
        key_6=true;
    else
        key_6=false;
    if (keylist[SDLK_7])
        key_7=true;
    else
        key_7=false;
    if (keylist[SDLK_8])
        key_8=true;
    else
        key_8=false;
    if (keylist[SDLK_9])
        key_9=true;
    else
        key_9=false;
    if (keylist[SDLK_0])
        key_0=true;
    else
        key_0=false;

    if ((keylist[SDLK_LSHIFT])||(keylist[SDLK_RSHIFT]))
        key_shift=true;
    else
        key_shift=false;
    if ((keylist[SDLK_LCTRL])||(keylist[SDLK_RCTRL]))
        key_ctrl=true;
    else
        key_ctrl=false;
    if (keylist[SDLK_UP]||keylist[SDLK_8]||keylist[SDLK_KP2])
        key_up=true;
    else
        key_up=false;
    if (keylist[SDLK_DOWN]||keylist[SDLK_8]||keylist[SDLK_KP2])
        key_down=true;
    else
        key_down=false;
    if (keylist[SDLK_RETURN]||keylist[SDLK_F2]||keylist[SDLK_KP5])
        key_action=true;
    else
        key_action=false;


    if (Config.conf_keyduck == 0)
        if (keylist[SDLK_DOWN])
            key_duck=true;
        else
            key_duck=false;
    else
        if (keylist[Config.conf_keyduck])
            key_duck=true;
        else
            key_duck=false;

    if (Config.conf_keyjump == 0)
        if (keylist[SDLK_SPACE])
            key_jump=true;
        else
            key_jump=false;
    else
        if (keylist[Config.conf_keyjump])
            key_jump=true;
        else
            key_jump=false;

    if (Config.conf_keyleft == 0)
        if (keylist[SDLK_LEFT])
            key_left=true;
        else
            key_left=false;
    else
        if (keylist[Config.conf_keyleft])
            key_left=true;
        else
            key_left=false;

    if (Config.conf_keyright == 0)
        if (keylist[SDLK_RIGHT])
            key_right=true;
        else
            key_right=false;
    else
        if (keylist[Config.conf_keyright])
            key_right=true;
        else
            key_right=false;

    if (Config.conf_keyfire == 0)
        if (keylist[SDLK_LCTRL])
            key_fire=true;
        else
            key_fire=false;
    else
        if (keylist[Config.conf_keyfire])
            key_fire=true;
        else
            key_fire=false;

    if (Config.conf_key1 == 0)
        if (keylist[SDLK_z])
            key_map=true;
        else
            key_map=false;
    else
        if (keylist[Config.conf_key1])
            key_map=true;
        else
            key_map=false;


}

void CEngine::ShutSystem()
{
    // free surfaces
    SDL_FreeSurface(Screen);
    //SDL_FreeSurface(FilterScreen);

    // free fonts
    freeFont(font);
    freeFont(bigfont);
    freeFont(blackfont);
    freeFont(bigblackfont);
    freeFont(terminalfont);

    // free sound
    Sound.FreeAll();
}


SDL_Surface* CEngine::LoadImage(const char *File, int Red, int Green, int Blue)
{
    //verify filename
    if(File == NULL)
    {
        LastVideoError = "Invalid Parameters To LoadImage()";
        return NULL;
    }

    //temp image surface
    SDL_Surface *Temp;

    //load the image and set colourkey
    Temp = SDL_LoadBMP(File);

    if(Temp == NULL)
    {
        LastVideoError = "Unable To Load Image File";
        return NULL;
    }

    //set colourkey
    SDL_SetColorKey(Temp, (SDL_SRCCOLORKEY|SDL_RLEACCEL),
                    SDL_MapRGB(Temp->format, (Uint8)Red, (Uint8)Green, (Uint8)Blue));

    //convert to screen format and return the new surface
    SDL_Surface *Disp = SDL_DisplayFormat(Temp);
    SDL_FreeSurface(Temp);

    DrawLoading();

    return Disp;
}


int CEngine::LoadImageFrames(const char *TileMap, SBITMAP *Images, int NumFrames, int IWidth, int IHeight, int Red, int Green, int Blue)
{
    //check file name
    if(!TileMap)
    {
        LastVideoError = "Invalid Parameters To LoadImageFrames()";
        return 0;
    }

    //temp surface to hold the tilemap image
    SDL_Surface *TileMapImg = SDL_LoadBMP(TileMap);

    if(TileMapImg == NULL)
    {
        LastVideoError = "Unable To LoadImageFrames()";
        //		return 0;
    }
    else
        SDL_SetColorKey(TileMapImg, (SDL_SRCCOLORKEY|SDL_RLEACCEL),
                        SDL_MapRGB(TileMapImg->format, (Uint8)Red, (Uint8)Green, (Uint8)Blue));

    //source rectangle
    SDL_Rect SrcRect;

    SrcRect.x = 0;
    SrcRect.w = static_cast<Uint16>(IWidth);
    SrcRect.h = static_cast<Uint16>(IHeight);

    //loop through and blit each frame from the tilemap to the frames buffer
    for(int i = 0; i < NumFrames; i++)
    {
        SrcRect.y = static_cast<Sint16>(i * IHeight);
        CreateSurface(Images[i], IWidth, IHeight);
        Images[i].frameWidth = IWidth;
        Images[i].frameHeight = IHeight;
        if (TileMapImg)
            SDL_BlitSurface(TileMapImg, &SrcRect, Images[i].Surface, NULL);
        SDL_SetColorKey(Images[i].Surface, (SDL_SRCCOLORKEY|SDL_RLEACCEL),
                        SDL_MapRGB(Images[i].Surface->format, 0, 0, 0));
    }

    SDL_FreeSurface(TileMapImg);

    DrawLoading();

    return 1;
}


SDL_Rect CEngine::NewSDLRect(int X, int Y, int Width, int Height)
{
    SDL_Rect Rect;
    Rect.x = static_cast<Sint16>(X);
    Rect.y = static_cast<Sint16>(Y);
    Rect.w = static_cast<Uint16>(Width);
    Rect.h = static_cast<Uint16>(Height);

    return Rect;
}

bool CEngine::Blit(SBITMAP Image, int XPos, int YPos)
{
    //verify surfaces
    if (Image.Surface == NULL)
    {
        LastVideoError = "Invalid Parameters To Blit()";
        return false;
    }

    SDL_Rect DestRect = NewSDLRect(XPos, YPos, Image.Surface->w, Image.Surface->h);
    SDL_BlitSurface(Image.Surface, NULL, Screen, &DestRect);

    return true;
}

bool CEngine::BlitTo(SBITMAP Image, SBITMAP DestImage, int XPos, int YPos)
{
    //verify surfaces
    if (Image.Surface == NULL)
    {
        LastVideoError = "Invalid Parameters To Blit()";
        return false;
    }

    SDL_Rect DestRect = NewSDLRect(XPos, YPos, Image.Surface->w, Image.Surface->h);
    SDL_BlitSurface(Image.Surface, NULL, DestImage.Surface, &DestRect);

    return true;
}

bool CEngine::BlitFrame(SBITMAP Image, int XPos, int YPos, int frame)
{
    //verify surfaces
    if (Image.Surface == NULL)
    {
        LastVideoError = "Invalid Parameters To BlitFrame()";
        return false;
    }

    SDL_Rect SrcRect = NewSDLRect(0, frame * Image.frameHeight, Image.Surface->w, Image.Surface->h);
    SDL_Rect DestRect = NewSDLRect(XPos, YPos, Image.Surface->w, Image.Surface->h);
    SDL_BlitSurface(Image.Surface, &SrcRect, Screen, &DestRect);

    return true;
}

void CEngine::FillBackground(int Red, int Green, int Blue)
{
    SDL_Rect Rect;
    Rect.x = static_cast<Sint16>(0);
    Rect.y = static_cast<Sint16>(0);
    Rect.w = static_cast<Uint16>(Screen->w);
    Rect.h = static_cast<Uint16>(Screen->h);

    SDL_FillRect(Screen, &Rect, SDL_MapRGB(Screen->format, Red, Green, Blue));
}

void CEngine::DrawRectangle(int X, int Y, int W, int H, int Red, int Green, int Blue)
{
    SDL_Rect Rect;
    Rect.x = static_cast<Sint16>(X);
    Rect.y = static_cast<Sint16>(Y);
    Rect.w = static_cast<Uint16>(W);
    Rect.h = static_cast<Uint16>(H);

    SDL_FillRect(Screen, &Rect, SDL_MapRGB(Screen->format, Red, Green, Blue));
}

void CEngine::FlipBuffer()
{

    //////////////// SMOOTH ////////////////////
    /*if (flagFullscreen)
    {
    	SDL_Rect Rect = NewSDLRect(0, 0, Screen->w, Screen->h);

    	SDL_LockSurface(Screen);
    	SDL_LockSurface(FilterScreen);

    	Filters.filter_advmame2x(
    	(Uint8*)Screen->pixels + (Screen->pitch * 3),
    	Screen->pitch, 
    	(Uint8*)FilterScreen->pixels,
    	FilterScreen->pitch,
    	Screen->w, 
    	Screen->h - 6 //2 * 3
    	);

    	SDL_UnlockSurface(FilterScreen);
    	SDL_UnlockSurface(Screen);

    	SDL_BlitSurface(FilterScreen, NULL, RealScreen, &Rect);
    }*/

    SDL_Flip(RealScreen);
}

void CEngine::FreeBitmap(SBITMAP bmp)
{
    SDL_FreeSurface(bmp.Surface);
}

void CEngine::CreateSurface(SBITMAP &bmp, int width, int height)
{
    bmp.Surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, SCREEN_BITS, rmask, gmask, bmask, amask);
    bmp.Surface = SDL_DisplayFormat(bmp.Surface);
}

int CEngine::getTicks()
{
    int i = SDL_GetTicks();
    return i;
}

void CEngine::Delay(int milis)
{
    SDL_Delay(milis);
}

void CEngine::Randomize()
{
    srand(SDL_GetTicks());
    for (int j = 0; j < 25; j++)
        rand();
}
int CEngine::random(int max)
{
    /*	randSeed = 0xDEADBF03 * (randSeed + 1);
    	randSeed = (randSeed >> 13) | (randSeed << 19);
    	return randSeed % (max + 1);*/
    return rand() % max;
}

void CEngine::DrawPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
    if ((x < 0)||(x > Screen->w - 1)||(y < 0)||(y > Screen->h - 1))
        return;

    Uint32 color = SDL_MapRGB(Screen->format, R, G, B);

    if ( SDL_MUSTLOCK(Screen) )
    {
        if ( SDL_LockSurface(Screen) < 0 )
        {
            return;
        }
    }
    switch (Screen->format->BytesPerPixel)
    {
    case 2:
        { // 16
            Uint16 *bufp;

            bufp = (Uint16 *)Screen->pixels + y*Screen->pitch/2 + x;
            *bufp = color;

        }
        break;

    case 4:
        { //32
            Uint32 *bufp;

            bufp = (Uint32 *)Screen->pixels + y*Screen->pitch/4 + x;
            *bufp = color;
        }
        break;
    }

    if ( SDL_MUSTLOCK(Screen) )
    {
        SDL_UnlockSurface(Screen);
    }
    //SDL_UpdateRect(Screen, x, y, 1, 1);
}

/* Basic unantialiased Bresenham line algorithm */
void CEngine::DrawLine(Uint32 x1, Uint32 y1, Uint32 x2, Uint32 y2, Uint8 R, Uint8 G, Uint8 B)
{
    int lg_delta, sh_delta, cycle, lg_step, sh_step;

    lg_delta = x2 - x1;
    sh_delta = y2 - y1;

    lg_step = 0;
    if (lg_delta > 0)
        lg_step = 1;
    if (lg_delta < 0)
        lg_step = -1;

    lg_delta = abs(lg_delta);

    sh_step = 0;
    if (sh_delta > 0)
        sh_step = 1;
    if (sh_delta < 0)
        sh_step = -1;

    sh_delta = abs(sh_delta);
    if (sh_delta < lg_delta)
    {
        cycle = lg_delta >> 1;
        while (x1 != x2)
        {
            DrawPixel(x1, y1, R, G, B);
            cycle += sh_delta;
            if (cycle > lg_delta)
            {
                cycle -= lg_delta;
                y1 += sh_step;
            }
            x1 += lg_step;
        }
        DrawPixel(x1, y1, R, G, B);
    }
    cycle = sh_delta >> 1;
    while (y1 != y2)
    {
        DrawPixel(x1, y1, R, G, B);
        cycle += lg_delta;
        if (cycle > sh_delta)
        {
            cycle -= sh_delta;
            x1 += lg_step;
        }
        y1 += sh_step;
    }
    DrawPixel(x1, y1, R, G, B);
}

void CEngine::DrawLoading()
{
    if ((!Screen)||(!font))
        return;

    FillBackground(0,0,0);

    switch (loadIndex%3)
    {
    case 0 :
        drawString(Screen, font, SCREEN_WIDTH/2 - 32 , SCREEN_HEIGHT/2 + 12, "Loading.");
        break;
    case 1 :
        drawString(Screen, font, SCREEN_WIDTH/2 - 32 , SCREEN_HEIGHT/2 + 12, "Loading..");
        break;
    case 2 :
        drawString(Screen, font, SCREEN_WIDTH/2 - 32 , SCREEN_HEIGHT/2 + 12, "Loading...");
        break;
    }

    drawString(Screen, font, 30 , SCREEN_HEIGHT - 42, LastVideoError);
    drawString(Screen, font, 30 , SCREEN_HEIGHT - 22, "this game is not complete, however it is fully playable from beginning to end");

    FlipBuffer();

    loadIndex++;
}


FSOUND_SAMPLE* CEngine::LoadSound(const char *File)
{
    DrawLoading();

    return FSOUND_Sample_Load(FSOUND_FREE, File, FSOUND_2D, 0, 0);
}

Uint32 CEngine::GetPixel(int x, int y, SDL_Surface *Surf)
{
	Uint32 *bufp;

	if ((x < 0)||(x > Surf->w - 1)||(y < 0)||(y > Surf->h - 1))
        return 0;

    if ( SDL_MUSTLOCK(Surf) )
    {
        if ( SDL_LockSurface(Surf) < 0 )
        {
            return 0;
        }
    }
    switch (Surf->format->BytesPerPixel)
    {
    case 2:
        { // 16
            bufp = (Uint32 *) Surf->pixels + y*Surf->pitch/2 + x;
        }
        break;

    case 4:
        { //32
            bufp = (Uint32 *) Surf->pixels + y*Surf->pitch/4 + x;
        }
        break;
    }

    if ( SDL_MUSTLOCK(Surf) )
    {
        SDL_UnlockSurface(Surf);
    }

	return *bufp;  
}

int CEngine::GetColor(Uint32 pixel, int rgb)
{
	Uint8 r;
	Uint8 g;
	Uint8 b;

	SDL_GetRGB(pixel, Screen->format, &r, &g, &b);

	switch (rgb)
	{
	case 0:
		return (int)r;
		break;
	case 1:
		return (int)g;
		break;
	case 2:
		return (int)b;
		break;
	}

	return (int)r;
}