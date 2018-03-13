#pragma once

#include <Windows.h>
#include <queue>

#define MAX_BUFFER_SIZE (1024 * 16)
#define MAX_BUFFER_COUNT 20

using namespace std;

extern int InitMusicPlayer();
extern int SelectMusic(const char* path);
extern int OpenFile(const char* path);
extern int PlayMusic(const char* path, int millisecond);
extern int PauseMusic();
extern int RestartMusic();
extern int SkipSecond(int millisecond);
extern int Playback(int millisecond);
extern int GetCurrentPlaybackTime();
extern int GetTotalDuration();
extern int SetVolume(WORD leftChannel, WORD rightChannel);
extern int CloseMusicPlayer();
extern void AddWavToBuffer();
extern void PlayWavFromBuffer();
extern void DumpSoundData();

enum PLAYERSTATE { PREPARING, PLAYING, PAUSED, FINISHED };
//extern PLAYERSTATE playerState;

typedef struct {
	WAVEHDR header;
	char* data;
	//bufferState state;
} WaveFileBlock;

/*extern FILE* fp;
//char* soundData;
extern DWORD fileSize;
extern DWORD startOffset;
extern DWORD endOffset;

//WaveFileBlock *myWaveFileBlock;
extern deque<WaveFileBlock> bufferQueue;
//mutex bufferMut, playMut;
//condition_variable bufCond, playCond;
//deque<WAVEHDR> headerToUnprepareQueue;
extern deque<char*> dumpSoundDataQueue;

extern HWAVEOUT hWaveOut;
extern WAVEFORMATEX waveFormat;
extern HANDLE waitEvent;*/