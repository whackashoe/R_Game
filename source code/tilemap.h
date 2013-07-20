#ifndef TILEMAP_H
#define TILEMAP_H
#include "engine.h"
#define MAP_WIDTH 100
#define MAP_HEIGHT 85
#define TILE_WIDTH 32
#define TILE_HEIGHT 32
struct MapHeader
{
    int tilesSet;
    int backgroundRed, backgroundGreen, backgroundBlue;
};

struct MapSprite
{
    int style;
    int x, y;
    int direction;
    int attitude;
    int target, id, dummy3, dummy4, dummy5, dummy6, dummy7, dummy8;
};
static int tilesMatrix[15][5] =
    {
        {
            1, 1, 1, 1, 1
        },
        {
            1, 0, 0, 0, 2
        },
        {
            0, 1, 0, 0, 3
        },
        {
            0, 0, 1, 0, 4
        },
        {
            0, 0, 0, 1, 5
        },
        {
            1, 1, 0, 0, 6
        },
        {
            0, 1, 1, 0, 7
        },
        {
            0, 0, 1, 1, 8
        },
        {
            1, 0, 0, 1, 9
        },
        {
            1, 1, 0, 1, 10
        },
        {
            0, 1, 1, 1, 11
        },
        {
            1, 0, 1, 1, 12
        },
        {
            1, 1, 1, 0, 13
        },
        {
            1, 0, 1, 0, 14
        },
        {
            0, 1, 0, 1, 15
        }
    };
static int tilesMatrixR[15] =
    {
        1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1
    };
static int tilesMatrixU[15] =
    {
        1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0
    };
static int tilesMatrixL[15] =
    {
        1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1
    };

static int tilesMatrixD[15] =
    {
        1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0
    };

class CTileMap
{
public:
    SBITMAP *TilesBitmap;

    int tiles[MAP_HEIGHT][MAP_WIDTH];

    int numFrames;

    int tileSet;

    int backgroundRed, backgroundGreen, backgroundBlue;

	int foregroundRed, foregroundGreen, foregroundBlue;

	///////////////////////////////////////////////////////

    int NewTileMap(int Red, int Green, int Blue);
    int getCell(int tX, int tY);
    void setCell(int tX, int tY, int newTile);
    void animate();
    void SetBackground(int Red, int Green, int Blue);
};
#endif