#ifndef ENGINE_H
#define ENGINE_H

//#pragma comment(lib, "SDL.lib")

#include "preheader.h"
#include "font.h"
#include "sound.h"
#include "filters.h"
#include "platform.h"


typedef struct SBITMAP
{
    SDL_Surface* Surface;
    int frameWidth, frameHeight;
}
SBITMAP;

typedef struct ConfigHeader
{
    int mapNum, tilesSet;
    int conf_keyjump, conf_key1, conf_keyleft, conf_keyright, conf_keyfire, conf_keyduck;
    int fullscreen, limitfps;
    int sound, music;
}
ConfigHeader;


class CEngine
{
    SDL_Event Event;

    Uint32 rmask, gmask, bmask, amask;

private:
    void Randomize();

public:
    SDL_Surface *Screen, *FilterScreen, *RealScreen;

    CSound Sound;

    CFilters Filters;

    int randSeed;

    // keys
    int key_pressed;
    bool key_up, key_down, key_right, key_left;
    bool key_jump, key_fire, key_action, key_duck;
    bool key_e, key_r, key_z, key_x, key_c, key_t,
    key_l, key_q, key_s, key_v, key_b, key_m,
    key_n, key_a, key_d, key_i, key_o, key_p,
    key_k, key_h, key_y, key_u, key_w, key_g,
    key_j, key_f;
    bool key_0, key_1, key_2, key_3, key_4, key_5, key_6, key_7, key_8, key_9;
    bool key_f1, key_f5, key_f6, key_f7, key_f8, key_f9, key_f10;
    bool key_shift, key_ctrl;
    bool key_esc, key_map;

    char *LastVideoError;
    char *RootDirectory;

    // FONTS
    SDLFont *font;
    SDLFont *bigfont;
    SDLFont *blackfont;
    SDLFont *bigblackfont;
    SDLFont *terminalfont;

	SDLFont *menufont;

    ConfigHeader Config;

    bool flagFullscreen;
    int loadIndex;

    ////////////////////////////////////
    int InitSystem();

    void CheckSystemEvents(bool &quit);

    void ShutSystem();

    SDL_Surface* CEngine::LoadImage(const char *File, int Red, int Green, int Blue);

    int LoadImageFrames(const char *TileMap, SBITMAP *Images, int NumFrames, int IWidth, int IHeight, int Red, int Green, int Blue);

    SDL_Rect NewSDLRect(int X, int Y, int Width, int Height);

    bool Blit(SBITMAP Image, int XPos, int YPos);

    bool BlitTo(SBITMAP Image, SBITMAP DestImage, int XPos, int YPos);

    bool BlitFrame(SBITMAP Image, int XPos, int YPos, int frame);

    void FillBackground(int Red, int Green, int Blue);

    void DrawRectangle(int X, int Y, int W, int H, int Red, int Green, int Blue);

    void FlipBuffer();

    void FreeBitmap(SBITMAP bmp);

    void CreateSurface(SBITMAP &bmp, int width, int height);

    int getTicks();

    void Delay(int milis);

    int random(int max);

    void DrawPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);

    void DrawLine(Uint32 x1, Uint32 y1, Uint32 x2, Uint32 y2, Uint8 R, Uint8 G, Uint8 B);

    void DrawLoading();

    FSOUND_SAMPLE* CEngine::LoadSound(const char *File);

	Uint32 GetPixel(int x, int y, SDL_Surface *Surf);

	int GetColor(Uint32 pixel, int rgb);
};


#endif