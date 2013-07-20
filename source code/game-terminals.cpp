#include "preheader.h"
#include "game.h"

void CGame::LoadTerminalText(char* filename)
{
	int numLines;
	int i;
	numLines = 0;
	FILE *fr;
	char line[TERMINAL_TEXT_LENGTH];

	fr = fopen (filePlusDir(filename), "rt");
    while (fgets(line, TERMINAL_TEXT_LENGTH, fr) != NULL)
    {
		numLines++;
    }
    fclose(fr);


	terminalText = new char* [numLines];

	for (i=0;i<numLines;i++)
		*(terminalText+i)=new char[TERMINAL_TEXT_LENGTH];

	i = 0;
	fr = fopen (filePlusDir(filename), "rt");
    while (fgets(line, TERMINAL_TEXT_LENGTH, fr) != NULL)
    {
		strcpy(terminalText[i], line);
		i++;
    }
    fclose(fr);

	terminalTextLines = numLines;
	terminalTextPos = 0;

	return;
}

void CGame::DrawTerminalText()
{
	int i;

	for (i = terminalTextPos; i<terminalTextPos+TERMINAL_TEXT_LINES; i++)
		if ( (i < terminalTextLines)&&(i > -1) )
			drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX-25,
				TERMINAL_STARTY + (i-terminalTextPos+2)*TERMINAL_TEXT_SPACE, terminalText[i]);

    return;
}

bool CGame::TerminalMenu(int map)
{
    int Positions = 0;
    bool Go = false;
    int i, oldTerminalPos;

	oldTerminalPos = terminalPos;

    if ((!Engine.key_up)&&(!Engine.key_down)&&(!Engine.key_action))
        canMenuPos = true;

    if (canMenuPos)
    {
        if (Engine.key_up)
        {
            terminalPos--;
			terminalTextPos--;
            canMenuPos = false;
        }
        if (Engine.key_down)
        {
            terminalPos++;
			terminalTextPos++;
            canMenuPos = false;
        }
        if (Engine.key_action)
        {
            Go = true;
            canMenuPos = false;
        }
    }

	// control of mole
	if TERMINAL_6_2a
	{
		int mole;
		for (int j = 0; j < MAX_LUDENS; j++)
			if (Ludens[j].active)
				if (Ludens[j].style == MOLE)
					mole = j;
		if (myLudens == mole)
		{
			terminalPos = oldTerminalPos;
		}
	}

	// main terminal menu
    switch (terminalLayer)
    {
    case 0 :
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 1;
                terminalPos = 0;
                return false;
            }
            if (terminalPos == 1)
            {
                terminalLayer = 4;
                terminalPos = 0;
                return true;
            }
            if (terminalPos == 2)
            {
                terminalLayer = 5;
                terminalPos = 0;
				LoadTerminalText("d/help.txt");
                return true;
            }
            if (terminalPos == 3)
            {
                terminalLayer = 6;
                terminalPos = 0;
                return true;
            }
        }
        Positions = 4;
        break;
	}

	if TERMINAL_6_1 // Episode V : Mines
    switch (terminalLayer)
    {
    case 1 :
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 0;
                return false;
            }
            if (terminalPos == 1)
            {
                terminalLayer = 2;
                terminalPos = 0;
                return true;
            }
            if (terminalPos == 2)
            {
                terminalLayer = 3;
                terminalPos = 0;
                return true;
            }
        }
        Positions = 3;
        break;
    case 2 : // bridge
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 1;
                terminalPos = 1;
                return false;
            }
            if (terminalPos == 1) //deactivate  bridge
            {  
				for (int j=0; j < MAX_LUDENS; j++)
					if ( (Ludens[j].active)&&(Ludens[j].style == PLATFORM) )
					{
						AddPart(P_PUFF, Ludens[j].posX, Ludens[j].posY);
						Ludens[j].kill();
					}
                return true;
            }
        }
        Positions = 2;
        break;
    case 3 : // door
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 1;
                terminalPos = 2;
                return false;
            }
            if (terminalPos == 1) //open
            {  
				if (Ludens[terminalNum].target > -1)
					Ludens[Ludens[terminalNum].target].setAnimation(ANIM_DOOR_OPEN, 1, LEFT, false, false);
                return true;
            }
            if (terminalPos == 2) //close
            {
				if (Ludens[terminalNum].target > -1)
					Ludens[Ludens[terminalNum].target].setAnimation(ANIM_DOOR_CLOSE, 1, LEFT, false, true);
                return true;
            }
        }
        Positions = 3;
        break;
    case 4 : // files
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 1;
                return false;
            }
            if (terminalPos == 1) //field-manual1.txt
            {  
				LoadTerminalText("d/manual1.txt");
                terminalLayer = 7;
                terminalPos = 0;
                return true;
            }
            if (terminalPos == 2) //primer4.txt
            {
                terminalLayer = 8;
                terminalPos = 0;
				LoadTerminalText("d/p14.txt");
                return true;
            }
        }
        Positions = 3;
        break;
    case 5 : // help
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 2;
                return false;
            }
        }
        Positions = 1;
        break;
    case 6 : // shutdown
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 3;
                return false;
            }
            if (terminalPos == 1)
            {  
				Ludens[terminalNum].setAnimation(ANIM_TERMINAL_DESTROYED, 2, LEFT, false, true);
				usingTerminal = false;
                return false;
            }
        }
        Positions = 2;
        break;
    case 7 : // field-manual1.txt
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 4;
                terminalPos = 1;
                return false;
            }
        }
        Positions = 1;
        break;
    case 8 : // primer4.txt
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 4;
                terminalPos = 2;
                return false;
            }
        }
        Positions = 1;
        break;
	}

	if TERMINAL_6_2a // Episode V : Mines 2 Mole
    switch (terminalLayer)
    {
    case 1 : // Mole
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 0;				
                return false;
            }
            if (terminalPos == 1)
            {
				int mole;
				for (int j = 0; j < MAX_LUDENS; j++)
					if (Ludens[j].active)
						if (Ludens[j].style == MOLE)
							mole = j;
					
				if (myLudens == mole)
					myLudens = sceneLudens[0];
				else
				{
					sceneLudens[0] = myLudens;
					myLudens = mole;
				}
                return false;
            }
        }
        Positions = 2;
        break;
    case 4 : // files
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 1;
                return false;
            }
            if (terminalPos == 1) //field-manual1.txt
            {  
				LoadTerminalText("d/bio23.txt");
                terminalLayer = 7;
                terminalPos = 0;
                return true;
            }
            if (terminalPos == 2) //primer4.txt
            {
                terminalLayer = 8;
                terminalPos = 0;
				LoadTerminalText("d/bio64.txt");
                return true;
            }
        }
        Positions = 3;
        break;
    case 5 : // help
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 2;
                return false;
            }
        }
        Positions = 1;
        break;
    case 6 : // shutdown
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 3;
                return false;
            }
            if (terminalPos == 1)
            {  
				Ludens[terminalNum].setAnimation(ANIM_TERMINAL_DESTROYED, 2, LEFT, false, true);
				usingTerminal = false;
                return false;
            }
        }
        Positions = 2;
        break;
    case 7 : // field-manual1.txt
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 4;
                terminalPos = 1;
                return false;
            }
        }
        Positions = 1;
        break;
    case 8 : // primer4.txt
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 4;
                terminalPos = 2;
                return false;
            }
        }
        Positions = 1;
        break;
	}

	if TERMINAL_6_2b // Episode V : Mines 2 exit
    switch (terminalLayer)
    {
    case 1 :
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 0;
                return false;
            }
            if (terminalPos == 1) //open vault
            {  
				if (Ludens[terminalNum].target > -1)
					Ludens[Ludens[terminalNum].target].kill();
                return true;
            }
        }
        Positions = 2;
        break;
    case 2 : // 
        if (Go)
        {
        }
        Positions = 1;
        break;
    case 3 : // 
        break;
    case 4 : // files
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 1;
                return false;
            }
            if (terminalPos == 1) //field-manual1.txt
            {  
				LoadTerminalText("d/bio11.txt");
                terminalLayer = 7;
                terminalPos = 0;
                return true;
            }
            if (terminalPos == 2) //primer4.txt
            {
                terminalLayer = 8;
                terminalPos = 0;
				LoadTerminalText("d/bio3.txt");
                return true;
            }
        }
        Positions = 3;
        break;
    case 5 : // help
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 2;
                return false;
            }
        }
        Positions = 1;
        break;
    case 6 : // shutdown
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 3;
                return false;
            }
            if (terminalPos == 1)
            {  
				Ludens[terminalNum].setAnimation(ANIM_TERMINAL_DESTROYED, 2, LEFT, false, true);
				usingTerminal = false;
                return false;
            }
        }
        Positions = 2;
        break;
    case 7 : // field-manual1.txt
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 4;
                terminalPos = 1;
                return false;
            }
        }
        Positions = 1;
        break;
    case 8 : // primer6.txt
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 4;
                terminalPos = 2;
                return false;
            }
        }
        Positions = 1;
        break;
	}

	if TERMINAL_6_3a // Episode V : Mines 3 - a
    switch (terminalLayer)
    {
    case 1 :
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 0;
                return false;
            }
            if (terminalPos == 1)
            {
                terminalLayer = 3;
                terminalPos = 0;
                return true;
            }
        }
        Positions = 2;
        break;
    case 2 : // 
        if (Go)
        {
        }
        Positions = 1;
        break;
    case 3 : // doors
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 1;
                terminalPos = 1;
                return false;
            }
            if (terminalPos == 1) //open all doors
            {  
				if (Ludens[terminalNum].target > -1)
				{
					for (int j=0; j < MAX_LUDENS; j++)
						if ( (Ludens[j].active)&&(Ludens[j].style == DOOR)&&(abs(Ludens[j].posX - Ludens[Ludens[terminalNum].target].posX) < (TILE_WIDTH<<FIX)) )
						{
							Ludens[j].setAnimation(ANIM_DOOR_OPEN, 1, LEFT, false, false);
						}
				}
                return true;
            }
            if (terminalPos == 2) //close all doors
            {
					for (int j=0; j < MAX_LUDENS; j++)
						if ( (Ludens[j].active)&&(Ludens[j].style == DOOR)&&(abs(Ludens[j].posX - Ludens[Ludens[terminalNum].target].posX) < (TILE_WIDTH<<FIX)) )
						{
							Ludens[j].setAnimation(ANIM_DOOR_CLOSE, 1, LEFT, false, true);
						}
                return true;
            }
        }
        Positions = 3;
        break;
    case 4 : // files
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 1;
                return false;
            }
            if (terminalPos == 1) //field-manual1.txt
            {  
				LoadTerminalText("d/manual1.txt");
                terminalLayer = 7;
                terminalPos = 0;
                return true;
            }
            if (terminalPos == 2) //primer4.txt
            {
                terminalLayer = 8;
                terminalPos = 0;
				LoadTerminalText("d/p17.txt");
                return true;
            }
        }
        Positions = 3;
        break;
    case 5 : // help
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 2;
                return false;
            }
        }
        Positions = 1;
        break;
    case 6 : // shutdown
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 3;
                return false;
            }
            if (terminalPos == 1)
            {  
				Ludens[terminalNum].setAnimation(ANIM_TERMINAL_DESTROYED, 2, LEFT, false, true);
				usingTerminal = false;
                return false;
            }
        }
        Positions = 2;
        break;
    case 7 : // field-manual1.txt
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 4;
                terminalPos = 1;
                return false;
            }
        }
        Positions = 1;
        break;
    case 8 : // primer6.txt
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 4;
                terminalPos = 2;
                return false;
            }
        }
        Positions = 1;
        break;
	}


	if TERMINAL_6_3b // Episode V : Mines 3 - b
    switch (terminalLayer)
    {
    case 1 :
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 0;
                return false;
            }
            if (terminalPos == 1)
            {
                terminalLayer = 3;
                terminalPos = 0;
                return true;
            }
        }
        Positions = 2;
        break;
    case 2 : // 
        if (Go)
        {
        }
        Positions = 1;
        break;
    case 3 : // main prison door
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 1;
                terminalPos = 1;
                return false;
            }
            if (terminalPos == 1) //open
            {  
				if (Ludens[terminalNum].target > -1)
					Ludens[Ludens[terminalNum].target].setAnimation(ANIM_DOOR_OPEN, 1, LEFT, false, false);
                return true;
            }
            if (terminalPos == 2) //close
            {
				if (Ludens[terminalNum].target > -1)
					Ludens[Ludens[terminalNum].target].setAnimation(ANIM_DOOR_CLOSE, 1, LEFT, false, true);
                return true;
            }
        }
        Positions = 3;
        break;
    case 4 : // files
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 1;
                return false;
            }
            if (terminalPos == 1) //field-manual1.txt
            {  
				LoadTerminalText("d/book1.txt");
                terminalLayer = 7;
                terminalPos = 0;
                return true;
            }
            if (terminalPos == 2) //primer4.txt
            {
                terminalLayer = 8;
                terminalPos = 0;
				LoadTerminalText("d/paper1.txt");
                return true;
            }
        }
        Positions = 3;
        break;
    case 5 : // help
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 2;
                return false;
            }
        }
        Positions = 1;
        break;
    case 6 : // shutdown
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 3;
                return false;
            }
            if (terminalPos == 1)
            {  
				Ludens[terminalNum].setAnimation(ANIM_TERMINAL_DESTROYED, 2, LEFT, false, true);
				usingTerminal = false;
                return false;
            }
        }
        Positions = 2;
        break;
    case 7 : // field-manual1.txt
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 4;
                terminalPos = 1;
                return false;
            }
        }
        Positions = 1;
        break;
    case 8 : // primer6.txt
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 4;
                terminalPos = 2;
                return false;
            }
        }
        Positions = 1;
        break;
	}

	if TERMINAL_6_3c // Episode V : Mines 3 - c
    switch (terminalLayer)
    {
    case 1 :
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 0;
                return false;
            }
            if (terminalPos == 1)
            {
                terminalLayer = 3;
                terminalPos = 0;
                return true;
            }
        }
        Positions = 2;
        break;
    case 2 : // 
        if (Go)
        {
        }
        Positions = 1;
        break;
    case 3 : // exit door
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 1;
                terminalPos = 1;
                return false;
            }
            if (terminalPos == 1) //open
            {  
				if (Ludens[terminalNum].target > -1)
					Ludens[Ludens[terminalNum].target].setAnimation(ANIM_DOOR_OPEN, 1, LEFT, false, false);
                return true;
            }
            if (terminalPos == 2) //close
            {
				if (Ludens[terminalNum].target > -1)
					Ludens[Ludens[terminalNum].target].setAnimation(ANIM_DOOR_CLOSE, 1, LEFT, false, true);
                return true;
            }
        }
        Positions = 3;
        break;
    case 4 : // files
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 1;
                return false;
            }
            if (terminalPos == 1) //field-manual1.txt
            {  
				LoadTerminalText("d/book2.txt");
                terminalLayer = 7;
                terminalPos = 0;
                return true;
            }
            if (terminalPos == 2) //primer4.txt
            {
                terminalLayer = 8;
                terminalPos = 0;
				LoadTerminalText("d/paper3.txt");
                return true;
            }
        }
        Positions = 3;
        break;
    case 5 : // help
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 2;
                return false;
            }
        }
        Positions = 1;
        break;
    case 6 : // shutdown
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 0;
                terminalPos = 3;
                return false;
            }
            if (terminalPos == 1)
            {  
				Ludens[terminalNum].setAnimation(ANIM_TERMINAL_DESTROYED, 2, LEFT, false, true);
				usingTerminal = false;
                return false;
            }
        }
        Positions = 2;
        break;
    case 7 : // field-manual1.txt
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 4;
                terminalPos = 1;
                return false;
            }
        }
        Positions = 1;
        break;
    case 8 : // primer6.txt
        if (Go)
        {
            if (terminalPos == 0)
            {  
                terminalLayer = 4;
                terminalPos = 2;
                return false;
            }
        }
        Positions = 1;
        break;
	}



    if (terminalPos < 0)
        terminalPos = Positions-1;
    if (terminalPos > (Positions-1))
        terminalPos = 0;

    if (terminalTextPos < 0)
        terminalTextPos = 0;
    if (terminalTextPos > (terminalTextLines-TERMINAL_TEXT_LINES))
        terminalTextPos = terminalTextLines-TERMINAL_TEXT_LINES;

	if ((Positions == 1)&&(!Engine.key_action))
		canMenuPos = true;

    return true;
}

void CGame::DrawTerminalMenu(int map)
{
    Engine.DrawRectangle(100, 20, 500, 221, 0, 60, 40);

	for (int i=0; i < 23; i++)
	{
	//	Engine.DrawLine(100, 20 + i*10, 599, 20 + i*10, 0, 70, 50);
	}
	drawString(Engine.Screen, Engine.terminalfont, 104, 24, "ANAZOS (ANAZOS Not Another Zorth OS) : Build 1200 Version 25006001.1b");

	if TERMINAL_6_1 // Episode V : Mines (1)
    switch (terminalLayer)
    {
    case 0 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Setup");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, "Files");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, "Help");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 3*MENU_SPACE, "Shutdown");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 1 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Bridge");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, " Door");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 2 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Bridge - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Deactivate");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 4*MENU_SPACE, "Proceed with extreme caution!");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 5*MENU_SPACE, "Unauthorized deactivation will be punished.");
        break;
    case 3 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Door - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Open");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, " Close");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 4 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "...");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " field-manual1.txt");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, " primer14.txt");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 5 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Help - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    case 6 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY - 1*MENU_SPACE, "Shutdown may crash system. Are you sure?");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, " No");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Yes");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 7 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "field-manual1.txt - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    case 8 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "primer4.txt - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    }

	if TERMINAL_6_2a // Episode V : Mines (2) Mole
    switch (terminalLayer)
    {
    case 0 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Mole");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, "Files");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, "Help");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 3*MENU_SPACE, "Shutdown");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 1 :
		int mole;
		for (int j = 0; j < MAX_LUDENS; j++)
			if (Ludens[j].active)
				if (Ludens[j].style == MOLE)
					mole = j;

        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Mole - Return");
		if (myLudens == mole)
			drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Stop");
		else
			drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Control");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 4 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "...");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " casestudy23.txt");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, " casestudy64.txt");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 5 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Help - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    case 6 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY - 1*MENU_SPACE, "Shutdown may crash system. Are you sure?");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, " No");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Yes");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 7 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "casestudy23.txt - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    case 8 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "casestudy64.txt - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    }

	if TERMINAL_6_2b // Episode V : Mines - exit
    switch (terminalLayer)
    {
    case 0 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Vault");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, "Files");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, "Help");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 3*MENU_SPACE, "Shutdown");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 1 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Open Vault");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 2 :
        break;
    case 3 :
        break;
    case 4 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "...");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " casestudy11.txt");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, " casestudy03.txt");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 5 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Help - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    case 6 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY - 1*MENU_SPACE, "Shutdown may crash system. Are you sure?");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, " No");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Yes");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 7 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "casestudy11.txt - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    case 8 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "casestudy03.txt - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    }

	if TERMINAL_6_3a // Episode V : Mines (3) - a
    switch (terminalLayer)
    {
    case 0 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Blocks");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, "Files");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, "Help");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 3*MENU_SPACE, "Shutdown");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 1 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Doors");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 4*MENU_SPACE, "Block doors opening is eligible only in the following circumstances:");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 5*MENU_SPACE, "- new stock arrival (remove previous first)");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 6*MENU_SPACE, "- stock retransfer to work facilities");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 7*MENU_SPACE, "- post-extermination body removal (make sure gas is not present)");
        break;
    case 2 :
        break;
    case 3 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Doors - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Open");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, " Close");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 6*MENU_SPACE, "Reminder: Block doors can be open only");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 7*MENU_SPACE, "with the assistance of two or more gaurds.");
        break;
    case 4 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "...");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " field-manual6.txt");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, " primer17.txt");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 5 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Help - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    case 6 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY - 1*MENU_SPACE, "Shutdown may crash system. Are you sure?");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, " No");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Yes");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 7 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "field-manual6.txt - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    case 8 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "primer17.txt - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    }

	if TERMINAL_6_3b // Episode V : Mines (3) - b
    switch (terminalLayer)
    {
    case 0 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Prison");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, "Files");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, "Help");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 3*MENU_SPACE, "Shutdown");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 1 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Main Door");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 5*MENU_SPACE, "Only commanding officer has the rights to maintain");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 6*MENU_SPACE, "the main prison door. If you are not the commanding");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 7*MENU_SPACE, "officer please log off.");
        break;
    case 2 :
        break;
    case 3 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Main Door - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Open");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, " Close");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 4 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "...");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " book1.txt");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, " paper1.txt");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 5 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Help - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    case 6 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY - 1*MENU_SPACE, "Shutdown may crash system. Are you sure?");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, " No");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Yes");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 7 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "book1.txt - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    case 8 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "paper1.txt - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    }

	if TERMINAL_6_3c // Episode V : Mines (3) - c
    switch (terminalLayer)
    {
    case 0 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Doors");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, "Files");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, "Help");
		drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 3*MENU_SPACE, "Shutdown");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 1 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Exit Door");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 2 :
        break;
    case 3 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Exit Door - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Open");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, " Close");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 4 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "...");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " field-manual6_FIXED_WITH_PATCH.txt");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 2*MENU_SPACE, " paper3.txt");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 5 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "Help - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    case 6 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY - 1*MENU_SPACE, "Shutdown may crash system. Are you sure?");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, " No");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 1*MENU_SPACE, " Yes");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");
        break;
    case 7 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "field-manual6_FIXED_WITH_PATCH.txt - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    case 8 :
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX, TERMINAL_STARTY + 0*MENU_SPACE, "paper3.txt - Return");
        drawString(Engine.Screen, Engine.terminalfont, TERMINAL_STARTX - 30, TERMINAL_STARTY + terminalPos*MENU_SPACE + 2, ">>");

		DrawTerminalText();
        break;
    }

    return;
}