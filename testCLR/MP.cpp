#include <iostream>
#include <queue>
#include <deque>
#include <Windows.h>
#include "MP.h"
#include "httpclient.h"
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

///////////// audio streaming part /////////////
//char **streamBuf = NULL;
StreamBuffer streamBuf;
StreamSrcInfo streamSrcInfo[2];

DWORD t_getStreamData1Id, t_getStreamData2Id;

// arguments pass to get streaming buffer thread
typedef struct {
	int remote_no;
	DWORD n;
	DWORD r;
} ThreadArgs;

// set streaming source info for a remote wave file, limited to exactly 2 sources
int SetStreamSrcInfo(char* server1_ip, int port1, char* path1, char* server2_ip, int port2, char* path2) {
	streamSrcInfo[0].server_ip = server1_ip;
	streamSrcInfo[0].port = port1;
	streamSrcInfo[0].path = path1;
	streamSrcInfo[1].server_ip = server2_ip;
	streamSrcInfo[1].port = port2;
	streamSrcInfo[1].path = path2;
	if (streamSrcInfo[0].server_ip == NULL || streamSrcInfo[0].path == NULL
		|| streamSrcInfo[1].server_ip == NULL || streamSrcInfo[1].path == NULL) {
		return 1;
	}
	return 0;
}

// get wave format from one of the remote source
int s_SetWaveFormat() {
	FILE* log = fopen("log.txt", "a");
	char data[44];
	// get data from remote source
	fprintf(log, "%s:%d %s\n", streamSrcInfo[0].server_ip, streamSrcInfo[0].port, streamSrcInfo[0].path);
	if (get_data(streamSrcInfo[0].server_ip, streamSrcInfo[0].port, streamSrcInfo[0].path, 0, 44, data) != 0) {
		// encounter some errors
		fprintf(log, "cannot get data\n");
		fclose(log);
		return 404;
	}
	char type[4];
	DWORD chunkSize, subchunk1Size, sampleRate, byteRate, subchunk2Size;
	WORD audioFormat, numChannels, blockAlign, bitsPerSample;

	memcpy(type, data, sizeof(char) * 4);

	if (strncmp(type, "RIFF", 4) != 0) {
		cout << "Error: Not RIFF format" << endl;
		fprintf(log, "Error: Not RIFF format\n");
		fclose(log);
		return 1;
	}

	memcpy(&chunkSize, data + 4, sizeof(DWORD));
	memcpy(type, data + 8, sizeof(char) * 4);

	if (strncmp(type, "WAVE", 4) != 0) {
		cout << "Error: Not WAVE format" << endl;
		fprintf(log, "Error: Not WAVE format");
		fclose(log);
		return 1;
	}

	memcpy(type, data + 12, sizeof(char) * 4);
	if (strncmp(type, "fmt ", 4) != 0) {
		cout << "Error: Not fmt" << endl;
		fprintf(log, "Error: Not fmt");
		fclose(log);
		return 1;
	}

	memcpy(&subchunk1Size, data + 16, sizeof(DWORD));
	memcpy(&audioFormat, data + 20, sizeof(WORD));
	memcpy(&numChannels, data + 22, sizeof(WORD));
	memcpy(&sampleRate, data + 24, sizeof(DWORD));
	memcpy(&byteRate, data + 28, sizeof(DWORD));
	memcpy(&blockAlign, data + 32, sizeof(WORD));
	memcpy(&bitsPerSample, data + 34, sizeof(WORD));

	memcpy(type, data + 36, sizeof(char) * 4);
	if (strncmp(type, "data", 4) != 0) {
		cout << "Error: Missing data" << endl;
		fprintf(log, "Error: Missing data");
		fclose(log);
		return 1;
	}

	memcpy(&subchunk2Size, data + 40, sizeof(DWORD));

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

	fprintf(log, "Chunk Size : %d\n", chunkSize);
	fprintf(log, "Subchunk 1 Size : %d\n", subchunk1Size);
	fprintf(log, "Audio Format : %d\n", audioFormat);
	fprintf(log, "Number of Channels : %d\n", numChannels);
	fprintf(log, "Sample Rate : %d\n", sampleRate);
	fprintf(log, "Byte Rate : %d\n", byteRate);
	fprintf(log, "Block Align (bytes per sample) : %d\n", blockAlign);
	fprintf(log, "Bits per Sample : %d\n", bitsPerSample);
	fprintf(log, "Subchunk 2 Size : %d\n", subchunk2Size);
	fclose(log);

	return 0;
}

// load the buffer from the starting time, leaving the buffers of the skipped sections empty
int s_AddStreamBufferFromTime(int millisecond) {
	DWORD loadStartOffset = 44;
	startOffset = waveFormat.nAvgBytesPerSec * (millisecond / 1000.0) + 44;
	endOffset = fileSize;
	if (startOffset >= endOffset) {
		return 1;
	}
	DWORD curOffset = startOffset;
	DWORD len = endOffset - loadStartOffset;
	DWORD n, r;
	n = len / MAX_STREAM_BUFFER_SIZE;
	r = len % MAX_STREAM_BUFFER_SIZE;

	SetStreamBufferListLength(n + 1);
	//FILE* log = fopen("buflog.txt", "w");
	/*for (int i = (startOffset - 44) / n; i <= n; i++) {
	DWORD bufLen = (i < n) ? MAX_STREAM_BUFFER_SIZE : r;
	char* data = new char[bufLen];
	if (get_data(streamSrcInfo[0].server_ip, streamSrcInfo[0].port, streamSrcInfo[0].path, curOffset, bufLen, data) != 0) {
	int t = 10;
	//i++;
	//return 1;
	break;
	}
	//fwrite(data, sizeof(char), bufLen, log);
	//fclose(log);
	InsertStreamBuffer(i, data, bufLen);
	delete data;
	curOffset += bufLen;
	}*/
	ThreadArgs *t1Args = new ThreadArgs;
	t1Args->remote_no = 0;
	t1Args->n = n;
	t1Args->r = r;
	ThreadArgs *t2Args = new ThreadArgs;
	t2Args->remote_no = 1;
	t2Args->n = n;
	t2Args->r = r;
	HANDLE t1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)s_GetStreamBufferFromSrc, t1Args, 0, &t_getStreamData1Id);
	HANDLE t2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)s_GetStreamBufferFromSrc, t2Args, 0, &t_getStreamData2Id);
	//fclose(log);
	return 0;
}

// get data from one server, called by a thread
void s_GetStreamBufferFromSrc(LPVOID args) {
	ThreadArgs *tArgs = (ThreadArgs*)args;
	DWORD n = tArgs->n;
	DWORD r = tArgs->r;
	int remoteNo = tArgs->remote_no;
	DWORD curOffset = startOffset;
	for (DWORD i = (startOffset - 44) / n; i <= n; i++) {
		DWORD bufLen = (i < n) ? MAX_STREAM_BUFFER_SIZE : r;
		if (i % 2 == remoteNo) {			// 2 is the number of remote PCs
			char* data = new char[bufLen];
			if (get_data(streamSrcInfo[remoteNo].server_ip, streamSrcInfo[remoteNo].port,
				streamSrcInfo[remoteNo].path, curOffset, bufLen, data) != 0) {
				int t = 10;
				//i++;
				//return 1;
				break;
			}
			//fwrite(data, sizeof(char), bufLen, log);
			//fclose(log);
			InsertStreamBuffer(i, data, bufLen);
			delete data;
		}
		curOffset += bufLen;
	}
	delete tArgs;		// free memory after use
}

// initialize buffer list with length specified for new wav to read
void SetStreamBufferListLength(int length) {
	ClearStreamBuffer();
	streamBuf.length = length;
	streamBuf.list = new BufElem[length];
}

void InsertStreamBuffer(int index, char* data, int length) {
	if (index >= streamBuf.length) {
		return;
	}
	if (streamBuf.list[index].length != 0) {
		delete streamBuf.list[index].data;
	}
	streamBuf.list[index].data = new char[length];
	memcpy(streamBuf.list[index].data, data, sizeof(char) * length);
	streamBuf.list[index].length = length;
	//FILE* log = fopen("buflog.txt", "ab");
	//fprintf(log, "%s", streamBuf.list[index].data);
	//fwrite(streamBuf.list[index].data, sizeof(char), length, log);
	//fclose(log);
	return;
}

void ClearStreamBuffer() {
	if (streamBuf.length == 0) {
		return;
	}
	for (int i = 0; i < streamBuf.length; i++) {
		if (streamBuf.list[i].length > 0) {
			delete streamBuf.list[i].data;
		}
	}
	delete streamBuf.list;
	streamBuf.length = 0;
	return;
}

void s_AddStreamBufferToPlayBuffer() {
	DWORD loadStartOffset = 44;
	if (startOffset >= endOffset) {
		return;
	}
	DWORD curOffset = startOffset;
	/*DWORD len = endOffset - loadStartOffset;
	DWORD n, r;
	n = len / MAX_STREAM_BUFFER_SIZE;
	r = len % MAX_STREAM_BUFFER_SIZE;*/
	// add play buffer from each stream buffer
	DWORD n = streamBuf.length;
	for (DWORD i = (startOffset - 44) / n; i <= n; i++) {
		while (streamBuf.list[i].length == 0) {
			// data not yet arrive stream buffer, sleep for a while
			Thread::Sleep(10);
		}
		DWORD totalBlock = streamBuf.list[i].length / MAX_BUFFER_SIZE;
		DWORD remainSize = streamBuf.list[i].length % MAX_BUFFER_SIZE;
		// loop through one stream buffer to put data into play buffers
		for (DWORD j = 0; j <= totalBlock; j++) {
			DWORD bufLen = (j < totalBlock) ? MAX_BUFFER_SIZE : remainSize;
			if (remainSize <= 0) { continue; }
			printf("add buffer %d %d\n", i, j);
			while (bufferQueue.size() >= MAX_BUFFER_COUNT) {
				Thread::Sleep(10);
			}
			WaveFileBlock wfb;
			memset(&wfb.header, 0, sizeof(WAVEHDR));
			//char* data = new char[bufLen];
			char* data = streamBuf.list[i].data + j * MAX_BUFFER_SIZE;		// get the offset of data ptr
			wfb.header.lpData = data;
			wfb.header.dwBufferLength = bufLen;
			wfb.header.dwFlags = 0L;
			wfb.header.dwLoops = 1L;
			bufferQueue.push_back(wfb);
			if (playerState == PAUSED) {
				break;
			}
		}
	}
	if (playerState == PAUSED) {
		//...
		wchar_t buf[100];
		//swprintf_s(buf, 100, L"add buf: size of queue %d\n", bufferQueue.size());
		//OutputDebugString(buf);
		return;
	}
	cout << "1::Done all buffer\n";
}