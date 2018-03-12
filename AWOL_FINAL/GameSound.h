//Based on http://www.rastertek.com/dx10tut14.html

#ifndef GAMESOUND_H
#define GAMESOUND_H

#include<string>
#include<dsound.h>
#include<stdio.h>

class GameSound{

public:

	GameSound();
	~GameSound();

	bool Initialize(IDirectSoundBuffer* buffer);
	bool Release();
 	bool PlayWaveFile();
	bool IsPlaying();


private:

	IDirectSoundBuffer* buffer;
	bool initialized;
};
 

#endif