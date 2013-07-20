#pragma once
#include "preheader.h"
#include "game.h"


CGame Game;


int main(int argc, char **argv)
{
    int i, s;
    s = strlen(argv[0]);
    // get root directory
    char *temp;
    temp = new char[s+1];
    strcpy(temp, argv[0]);
    for (i=s-1; i>-1; i--)
    {
        if ((temp[i] == 92)||(temp[i] == 47))
        {
            temp[i+1] = 0;
            break;
        }
    }
    for (i=0; i<s; i++)
    {
        if (temp[i] == 92)
            temp[i] = 47;
    }

    // start the game
    Game.StartGame(temp);

    return 0;
}

