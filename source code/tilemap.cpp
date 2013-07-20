#include "preheader.h"
#include "tilemap.h"
int CTileMap::NewTileMap(int Red, int Green, int Blue)
{
    int i, j;
    for (i=0; i<MAP_WIDTH; i++)
        for (j=0; j<MAP_HEIGHT; j++)
        {
            tiles[j][i] = 0;
        }
    j = MAP_HEIGHT - 3;
    for (i=0; i<MAP_WIDTH; i++)
        tiles[j][i] = 11;
    j = MAP_HEIGHT - 2;
    for (i=0; i<MAP_WIDTH; i++)
        tiles[j][i] = 47;
    j = MAP_HEIGHT - 1;
    for (i=0; i<MAP_WIDTH; i++)
        tiles[j][i] = 46;
    backgroundRed = Red;
    backgroundGreen = Green;
    backgroundBlue = Blue;

    return i;
}
int CTileMap::getCell(int tX, int tY)
{
    return tiles[tY][tX];
}
void CTileMap::setCell(int tX, int tY, int newTile)
{
    tiles[tY][tX] = newTile;
}
void CTileMap::animate()
{
    for (int i=0; i<MAP_WIDTH; i++)
        for (int j=0; j<MAP_HEIGHT; j++)
        {
            if (tiles[j][i] == 47)
                tiles[j][i] = 48 ;
            else
                if (tiles[j][i] == 48)
                    tiles[j][i] = 47;
        }
}
void CTileMap::SetBackground(int Red, int Green, int Blue)
{
    backgroundRed = Red;
    backgroundGreen = Green;
    backgroundBlue = Blue;
}