#pragma once
#include <Windows.h>
#include <queue>
#include <mutex>
#include <condition_variable>

#define MAX_BUFFER_SIZE (1024 * 16)
#define MAX_BUFFER_COUNT 20

using namespace std;

class MusicPlayer {
public:
	MusicPlayer();
	~MusicPlayer();

	int OpenFile(const char* path);
	int PlayMusic();
	int PauseMusic();
	int Playback(int second);
	int SetVolume(WORD leftChannel, WORD rightChannel);
	int ClosePlayer();

private:
	enum bufferState { WAITING, PLAYING, DONE };

	typedef struct {
		WAVEHDR header;
		char* data;
		bufferState state;
	} WaveFileBlock;

	FILE* fp;
	char* soundData;
	DWORD fileSize;
	
	WaveFileBlock *myWaveFileBlock;
	deque<WaveFileBlock> bufferQueue;
	mutex bufferMut, playMut;
	condition_variable bufCond, playCond;
	deque<WAVEHDR> headerToUnprepareQueue;

	bufferState playerState;

	// Deprecated
	static void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

	HWAVEOUT hWaveOut;
	WAVEFORMATEX waveFormat;
	HANDLE waitEvent;

	// Deprecated
	int WaitForPlay(char* data, DWORD len);
	// Deprecated
	int WriteToWave(char* data, DWORD len);

	void AddWavToBuffer(DWORD startOffset, DWORD endOffset);
	void PlayWavFromBuffer(DWORD startOffset, DWORD endOffset);
	void UnprepareHeader();
};