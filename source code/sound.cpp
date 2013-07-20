#include "preheader.h"
#include "sound.h"

unsigned char  CSound::Init(int mixrate, int maxsoftwarechannels, unsigned int flags)
{
    inited = FSOUND_Init(mixrate, maxsoftwarechannels, flags);

    MusicChannel = FSOUND_FREE;
    SpecialChannel = FSOUND_FREE;

    //	MusicChannel = FSOUND_PlaySound(FSOUND_FREE, samples[0]);
    //	DefaultVolume = FSOUND_GetVolume(MusicChannel);
    //	DefaultVolume = -1;

    return inited;
}

void CSound::PlayMOD(char *file)
{
    if (!inited)
        return;
    if ((!inited)||(!playMusics))
        return;

    FMUSIC_StopSong(mod);
    mod = FMUSIC_LoadSong(file);
    if (!mod)
    {
        return;
    }
    FMUSIC_PlaySong(mod);
}

void CSound::StopMOD()
{
    if (!inited)
        return;

    FMUSIC_StopSong(mod);
}


int CSound::PlaySample(int num)
{
    if ((!inited)||(!playSounds))
        return -1;
    int i;

    i = FSOUND_PlaySound(FSOUND_FREE, samples[num]);
    //FSOUND_SetVolume(i, 2*DefaultVolume/3);

    return i;
}

void CSound::FreeAll()
{
    if (!inited)
        return;

    for (int i=0; i<MAX_SOUNDS; i++)
        //if (samples[i])
        FSOUND_Sample_Free(samples[i]);
    for (int i=0; i<MAX_MUSICS; i++)
        //if (music[i])
        FSOUND_Sample_Free(music[i]);

    //FMUSIC_StopSong(mod);
    //FMUSIC_FreeSong(mod);
    FSOUND_Close();
}

void CSound::PlayMusic(int num)
{
    if ((!inited)||(num<0))
        return;

    StopMusic();
    MusicChannel = FSOUND_PlaySound(MusicChannel, music[num]);
    DefaultVolume = FSOUND_GetVolume(MusicChannel);
    //FSOUND_SetVolume(MusicChannel, DefaultVolume);
    //FSOUND_Sample_SetLoopPoints(music[num], 0, FSOUND_Sample_GetLength(music[num]));
    FSOUND_SetLoopMode(MusicChannel, FSOUND_LOOP_NORMAL);

    if (playMusics)
        PauseMusic(false);
    else
        PauseMusic(true);
}

void CSound::StopMusic()
{
    if (!inited)
        return;

    FSOUND_StopSound(FSOUND_ALL);
}

void CSound::PauseMusic(bool set
                           )
{
    if (!inited)
        return;

    FSOUND_SetPaused(MusicChannel, set
                        );
}

void CSound::SetMusicVolume(int vol)
{
    if (!inited)
        return;

    FSOUND_SetVolume(MusicChannel, vol);
}

void CSound::PauseChannel(int ch, bool set
                             )
{
    if (!inited)
        return;

    FSOUND_SetPaused(ch, set
                        );
}
