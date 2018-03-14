#pragma once

#include <Windows.h>
#include <queue>

#define MAX_BUFFER_SIZE (1024 * 16)
#define MAX_BUFFER_COUNT 20

using namespace std;

int InitMusicPlayer();
int SelectMusic(const char* path);
int OpenFile(const char* path);
int PlayMusic(const char* path, int millisecond);
int PauseMusic();
int RestartMusic();
int SkipSecond(int millisecond);
int Playback(int millisecond);
int GetCurrentPlaybackTime();
int GetCurrentPlaybackTimeFromStartPoint();
int GetTotalDuration();
int SetVolume(WORD leftChannel, WORD rightChannel);
int CloseMusicPlayer();
void AddWavToBuffer();
void PlayWavFromBuffer();
void DumpSoundData();

enum PLAYERSTATE { PREPARING, PLAYING, PAUSED, FINISHED };
//extern PLAYERSTATE playerState;

typedef struct {
	WAVEHDR header;
	char* data;
	//bufferState state;
} WaveFileBlock;
