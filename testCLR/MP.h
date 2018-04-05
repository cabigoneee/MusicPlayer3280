#pragma once

#include <Windows.h>
#include <queue>

#define MAX_BUFFER_SIZE (1024 * 16)
#define MAX_BUFFER_COUNT 20

#define MAX_STREAM_BUFFER_SIZE (1024 * 256)

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

//////////////////streaming////////////////////
typedef struct {
	char* server_ip;
	int port;
	char* path;
} StreamSrcInfo;

typedef struct {
	char* data;
	int length = 0;
} BufElem;

typedef struct {
	BufElem* list;
	int length = 0;
} StreamBuffer;

int SetStreamSrcInfo(char* server1_ip, int port1, char* path1, char* server2_ip, int port2, char* path2);
int s_SetWaveFormat();
int s_AddStreamBufferFromTime(int millisecond);
void s_GetStreamBufferFromSrc(LPVOID args);
void SetStreamBufferListLength(int length);
void InsertStreamBuffer(int index, char* data, int length);
void ClearStreamBuffer();
void s_AddStreamBufferToPlayBuffer();