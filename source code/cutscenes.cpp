#include "preheader.h"
#include "cutscenes.h"

void CDialogText::SetDialog(char *newText, int newX, int newY, int newTime, int newLastTime, int newFont)
{
    text = newText;
    x = newX;
    y = newY;
    duration = time = newTime;
    allTime += newTime;
    lastTime = newLastTime;
    font = newFont;
    count++;
}

void CDialogText::RestartDialog()
{
    allTime = count = 0;
}