#include <iostream>
#include <queue>
#include <deque>
#include <Windows.h>
#include "MP.h"
#pragma comment(lib, "winmm.lib")
using namespace std;
using namespace System;
using namespace System::Threading;

PLAYERSTATE playerState;
FILE* fp;
DWORD fileSize;
DWORD startOffset;
DWORD endOffset;
deque<WaveFileBlock> bufferQueue;
deque<char*> dumpSoundDataQueue;
HWAVEOUT hWaveOut;
WAVEFORMATEX waveFormat;
HANDLE waitEvent;
int currentPlaybackTime;
char currentFilePath[256];

DWORD t_addBufferId, t_playBufferId, t_dumpBufferId;

int InitMusicPlayer() {
	hWaveOut = NULL;
	waitEvent = CreateEvent(NULL, 0, 0, NULL);
	fp = NULL;
	fileSize = 0;
	playerState = PREPARING;
	currentFilePath[0] = '\0';
	currentPlaybackTime = 0;
	return 0;
}

int GetCurrentPlaybackTime() {
	if (playerState == PLAYING) {
		return currentPlaybackTime + GetCurrentPlaybackTimeFromStartPoint();
	}
	return currentPlaybackTime;
}

int GetCurrentPlaybackTimeFromStartPoint() {
	if (hWaveOut == NULL) {
		return -1;
	}
	MMTIME mmtime;
	mmtime.wType = TIME_SAMPLES;
	MMRESULT ret = waveOutGetPosition(hWaveOut, &mmtime, sizeof(MMTIME));
	int result = (float)mmtime.u.sample / waveFormat.nSamplesPerSec * 1000;
	return result;
}

int GetTotalDuration() {
	if (fp == NULL) {
		return -1;
	}
	int result = round((float)(fileSize - 44) / waveFormat.nAvgBytesPerSec * 1000);
	return result;
}

int SetVolume(WORD leftChannel, WORD rightChannel) {
	if (hWaveOut == NULL) {
		return 1;
	}
	DWORD resultVolume = ((DWORD)rightChannel << 16) + (DWORD)leftChannel;
	waveOutSetVolume(hWaveOut, resultVolume);
	return 0;
}

int SelectMusic(const char* path) {
	if (playerState == PLAYING) {
		PauseMusic();
	}
	if (OpenFile(path) == 0) {
		Playback(0);
		return 0;
	}
	return 1;
}

int OpenFile(const char* path) {
	fp = NULL;
	char type[4];
	DWORD chunkSize, subchunk1Size, sampleRate, byteRate, subchunk2Size;
	WORD audioFormat, numChannels, blockAlign, bitsPerSample;

	fp = fopen(path, "rb");
	if (!fp) {
		cout << "Error: Failed to open file" << endl;
		return 1;
	}

	strcpy(currentFilePath, path);

	fseek(fp, 0, SEEK_SET);
	fread(type, sizeof(char), 4, fp);
	if (strncmp(type, "RIFF", 4) != 0) {
		cout << "Error: Not RIFF format" << endl;
		return 1;
	}

	fread(&chunkSize, sizeof(DWORD), 1, fp);
	fread(type, sizeof(char), 4, fp);
	if (strncmp(type, "WAVE", 4) != 0) {
		cout << "Error: Not WAVE format" << endl;
		return 1;
	}

	fread(type, sizeof(char), 4, fp);
	if (strncmp(type, "fmt ", 4) != 0) {
		cout << "Error: Not fmt" << endl;
		return 1;
	}

	fread(&subchunk1Size, sizeof(DWORD), 1, fp);
	fread(&audioFormat, sizeof(WORD), 1, fp);
	fread(&numChannels, sizeof(WORD), 1, fp);
	fread(&sampleRate, sizeof(DWORD), 1, fp);
	fread(&byteRate, sizeof(DWORD), 1, fp);
	fread(&blockAlign, sizeof(WORD), 1, fp);
	fread(&bitsPerSample, sizeof(WORD), 1, fp);

	fread(type, sizeof(char), 4, fp);
	if (strncmp(type, "data", 4) != 0) {
		cout << "Error: Missing data" << endl;
	}

	fread(&subchunk2Size, sizeof(DWORD), 1, fp);

	/*cout << "Chunk Size: " << chunkSize << endl;
	cout << "Subchunk 1 Size: " << subchunk1Size << endl;
	cout << "Audio Format: " << audioFormat << endl;
	cout << "Number of Channels: " << numChannels << endl;
	cout << "Sample Rate: " << sampleRate << endl;
	cout << "Byte Rate: " << byteRate << endl;
	cout << "Block Align (bytes per sample): " << blockAlign << endl;
	cout << "Bits per Sample: " << bitsPerSample << endl;
	cout << "Subchunk 2 Size: " << subchunk2Size << endl;*/
	Console::WriteLine("Chunk Size : %d", chunkSize);
	Console::WriteLine("Subchunk 1 Size : %d", subchunk1Size);
	Console::WriteLine("Audio Format : %d", audioFormat);
	Console::WriteLine("Number of Channels : %d", numChannels);
	Console::WriteLine("Sample Rate : %d", sampleRate);
	Console::WriteLine("Byte Rate : %d", byteRate);
	Console::WriteLine("Block Align (bytes per sample) : %d", blockAlign);
	Console::WriteLine("Bits per Sample : %d", bitsPerSample);
	Console::WriteLine("Subchunk 2 Size : %d", subchunk2Size);

	fileSize = 8 + chunkSize;

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.wBitsPerSample = bitsPerSample;
	waveFormat.nChannels = numChannels;
	waveFormat.nSamplesPerSec = sampleRate;
	waveFormat.nAvgBytesPerSec = byteRate;
	waveFormat.nBlockAlign = blockAlign;
	waveFormat.cbSize = 0;

	/*soundData = new char[fileSize - 44];
	size_t x = fread(soundData, sizeof(char), fileSize - 44, fp);
	if (x != fileSize - 44) {
	cout << "size not match!" << endl;
	}
	cout << x << endl;*/
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, (DWORD_PTR)waitEvent, 0L, CALLBACK_EVENT);
	//fclose(fp);
	return 0;
}

int PlayMusic(const char* path, int millisecond) {
	if (OpenFile(path) != 0) {
		Playback(millisecond);
		return 0;
	}
	return 1;
}

int PauseMusic() {
	if (hWaveOut == NULL) {
		return 1;
	}
	if (playerState != PLAYING) {
		return 1;
	}
	/*int result = waveOutPause(hWaveOut);
	if (result == MMSYSERR_NOERROR) {
	playerState = PAUSED;
	}
	return result;*/
	currentPlaybackTime += GetCurrentPlaybackTimeFromStartPoint();
	playerState = PAUSED;
	HANDLE t1 = OpenThread(THREAD_ALL_ACCESS, false, t_addBufferId);
	HANDLE t2 = OpenThread(THREAD_ALL_ACCESS, false, t_playBufferId);
	HANDLE t3 = OpenThread(THREAD_ALL_ACCESS, false, t_dumpBufferId);
	if (t1 != NULL) {
		WaitForSingleObject(t1, 10000);
	}
	if (t2 != NULL) {
		WaitForSingleObject(t2, 10000);
	}
	if (t3 != NULL) {
		WaitForSingleObject(t3, 10000);
	}
	return 0;
}

int RestartMusic() {
	if (hWaveOut == NULL) {
		return 1;
	}
	if (playerState != PAUSED) {
		return 1;
	}
	/*int result = waveOutRestart(hWaveOut);
	if (result == MMSYSERR_NOERROR) {
	playerState = PLAYING;
	}
	return result;*/
	/*if (OpenFile("test.wav") != 0) {
	return 1;
	}*/
	if (OpenFile(currentFilePath) != 0) {
		return 1;
	}
	Playback(currentPlaybackTime);
	return 0;
}

int SkipSecond(int millisecond) {
	if (playerState == PLAYING) {
		//PauseMusic();
		int newPlaybackTime = millisecond + currentPlaybackTime + GetCurrentPlaybackTimeFromStartPoint();
		if (newPlaybackTime < 0 || newPlaybackTime >= GetTotalDuration()) {
			return 1;
		}
		PauseMusic();
		currentPlaybackTime = newPlaybackTime;
		if (OpenFile(currentFilePath) == 0) {
			Playback(newPlaybackTime);
			return 0;
		}
	}
	return 1;
}

int CloseMusicPlayer() {
	if (playerState == PLAYING) {
		PauseMusic();
	}
	HANDLE t1 = OpenThread(THREAD_ALL_ACCESS, false, t_addBufferId);
	HANDLE t2 = OpenThread(THREAD_ALL_ACCESS, false, t_playBufferId);
	HANDLE t3 = OpenThread(THREAD_ALL_ACCESS, false, t_dumpBufferId);
	if (t1 != NULL) {
		WaitForSingleObject(t1, 10000);
	}
	if (t2 != NULL) {
		WaitForSingleObject(t2, 10000);
	}
	if (t3 != NULL) {
		WaitForSingleObject(t3, 10000);
	}
	if (fp != NULL) {
		fclose(fp);
	}
	playerState = FINISHED;
	//DumpSoundData();
	if (hWaveOut != NULL) {
		waveOutReset(hWaveOut);
		int result = waveOutClose(hWaveOut);
		hWaveOut = NULL;
	}
	CloseHandle(waitEvent);
	return 0;
}

int Playback(int millisecond) {
	if (fp == NULL) {
		return 1;
	}
	wchar_t buf[100];
	
	currentPlaybackTime = millisecond;
	startOffset = waveFormat.nAvgBytesPerSec * (millisecond / 1000.0) + 44;
	// ensure that the sound starts at even offset
	startOffset = (startOffset % 2 == 0) ? startOffset : startOffset - 1;
	endOffset = fileSize;
	if (startOffset >= endOffset) {
		return 1;
	}
	DWORD curOffset = startOffset;

	DWORD len = endOffset - startOffset;
	DWORD n, r;
	n = len / MAX_BUFFER_SIZE;
	r = len % MAX_BUFFER_SIZE;

	playerState = PREPARING;

	HANDLE t1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AddWavToBuffer, NULL, 0, &t_addBufferId);
	HANDLE t2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PlayWavFromBuffer, NULL, 0, &t_playBufferId);
	HANDLE t3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DumpSoundData, NULL, 0, &t_dumpBufferId);

	return 0;
}

void AddWavToBuffer() {
	if (!fp) {
		cout << "File not exists\n";
		return;
	}
	DWORD curOffset = startOffset;
	DWORD len = endOffset - startOffset;
	DWORD n, r;
	n = len / MAX_BUFFER_SIZE;
	r = len % MAX_BUFFER_SIZE;
	for (DWORD i = 0; i <= n; i++) {
		DWORD bufLen = (i < n) ? MAX_BUFFER_SIZE : r;
		printf("add buffer %d\n", i);
		wchar_t buf[100];
		//swprintf_s(buf, 100, L"add buffer %d\n", i);
		//OutputDebugString(buf);
		//swprintf_s(buf, 100, L"size of queue %d\n", bufferQueue.size());
		//OutputDebugString(buf);
		//unique_lock<mutex> bufLock(bufferMut);
		//bufCond.wait(bufLock, [this] { return bufferQueue.size() < MAX_BUFFER_COUNT; });
		while (bufferQueue.size() >= MAX_BUFFER_COUNT) {
			Thread::Sleep(10);
		}
		WaveFileBlock wfb;
		memset(&wfb.header, 0, sizeof(WAVEHDR));
		char* data = new char[bufLen];
		fseek(fp, curOffset, SEEK_SET);
		fread(data, bufLen, sizeof(char), fp);
		curOffset += MAX_BUFFER_SIZE;
		wfb.header.lpData = data;
		wfb.header.dwBufferLength = bufLen;
		wfb.header.dwFlags = 0L;
		wfb.header.dwLoops = 1L;
		bufferQueue.push_back(wfb);
		if (playerState == PAUSED) {
			break;
		}
	}
	if (playerState == PAUSED) {
		//...
		//wchar_t buf[100];
		//swprintf_s(buf, 100, L"add buf: size of queue %d\n", bufferQueue.size());
		//OutputDebugString(buf);
		return;
	}
	cout << "1::Done all buffer\n";
}

void PlayWavFromBuffer() {
	if (!fp) {
		cout << "File not exists\n";
		return;
	}
	playerState = PLAYING;
	DWORD len = endOffset - startOffset;
	DWORD n, r;
	n = len / MAX_BUFFER_SIZE;
	r = len % MAX_BUFFER_SIZE;
	for (int i = 0; i <= n; i++) {
		printf("player buffer %d\n", i);
		wchar_t buf[100];
		//swprintf_s(buf, 100, L"play buffer %d\n", i);
		//OutputDebugString(buf);
		//swprintf_s(buf, 100, L"size of queue %d\n", bufferQueue.size());
		//OutputDebugString(buf);
		while (bufferQueue.size() == 0) {
			Thread::Sleep(10);
		}
		WaveFileBlock wfb = bufferQueue.front();
		waveOutPrepareHeader(hWaveOut, &wfb.header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &wfb.header, sizeof(WAVEHDR));

		//swprintf_s(buf, 100, L"1: dwFlags: %d\n", wfb.header.dwFlags);
		//OutputDebugString(buf);

		if (WaitForSingleObject(waitEvent, INFINITE) != WAIT_OBJECT_0) {
			cout << "Error waiting for sound to finish\n";
			//OutputDebugString(L"Error waiting for sound to finish\n");
		}
		else {
			cout << "Sound finished\n";
			//OutputDebugString(L"Sound finished\n");
		}

		//swprintf_s(buf, 100, L"2: dwFlags: %d\n", wfb.header.dwFlags);
		//OutputDebugString(buf);

		if (waveOutUnprepareHeader(hWaveOut, &wfb.header, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
			cout << "Error to unprepare header\n";
			//OutputDebugString(L"Error to unprepare header\n");
		}
		else {
			cout << "Unprepared header\n";
			//OutputDebugString(L"Error to unprepare header\n");
		}

		//swprintf_s(buf, 100, L"3: dwFlags: %d\n", wfb.header.dwFlags);
		//OutputDebugString(buf);
		dumpSoundDataQueue.push_back(wfb.header.lpData);
		bufferQueue.pop_front();
		if (playerState == PAUSED) {
			break;
		}
	}
	if (playerState == PAUSED) {
		int x = waveOutReset(hWaveOut);
		//wchar_t buf[100];
		//swprintf_s(buf, 100, L"play buf: size of queue %d\n", bufferQueue.size());
		//OutputDebugString(buf);
		while (bufferQueue.size() > 0) {
			WaveFileBlock wfb2 = bufferQueue.front();
			dumpSoundDataQueue.push_back(wfb2.header.lpData);
			bufferQueue.pop_front();
		}
		return;
	}
	cout << "2::Done all playing\n";
	playerState = FINISHED;
	waveOutReset(hWaveOut);
	fclose(fp);
	currentFilePath[0] = '\0';
}

void DumpSoundData() {
	while (true) {
		if (playerState == PAUSED || playerState == FINISHED) {
			break;
		}
		if (dumpSoundDataQueue.size() > 0) {
			Thread::Sleep(100);
			char *data = dumpSoundDataQueue.front();
			if (data != NULL) {
				delete data;
			}
			dumpSoundDataQueue.pop_front();
		}
		else {
			Thread::Sleep(100);
		}
	}
	// wait until play buffer end to clear all sound data
	HANDLE t2 = OpenThread(THREAD_ALL_ACCESS, false, t_playBufferId);
	if (t2 != NULL) {
		WaitForSingleObject(t2, 10000);
	}
	while (dumpSoundDataQueue.size() > 0) {
		char *data = dumpSoundDataQueue.front();
		if (data != NULL) {
			delete dumpSoundDataQueue.front();
		}
		dumpSoundDataQueue.pop_front();
	}
}