#ifndef SOUND_H
#define SOUND_H

#include "preheader.h"
#include "globals.h"

#define MAX_SOUNDS 36
#define MAX_MUSICS 9
//#define MUSICSTEP 130048
#define MUSICSTEP 65024
#define MUSICBOUND 2048
#define MUSICMODSTEP 72

class CSound
{
public:
    unsigned char inited;

    FMUSIC_MODULE *mod;

    FSOUND_SAMPLE *samples[MAX_SOUNDS];

    FSOUND_SAMPLE *music[MAX_MUSICS];

    bool playSounds, playMusics;

    int MusicChannel, SpecialChannel;

    int DefaultVolume;

    ////////////////////

    unsigned char Init(int mixrate, int maxsoftwarechannels, unsigned int flags);

    void PlayMOD(char *file);

    void StopMOD();

    int  PlaySample(int num);

    void FreeAll();

    void PlayMusic(int num);

    void StopMusic();

    void PauseMusic(bool set);

    void SetMusicVolume(int vol);

    void PauseChannel(int ch, bool set);
};

#endif