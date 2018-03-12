#ifndef SOUNDLIBRARY
#define SOUNDLIBRARY

#include<map>
#include<string>
#include "GameSoundBuffer.h"
#include "SoundDevice.h"
//#include"GraphicsDevice.h"
//include"GameSprite.h"

class SoundLibrary{

public:
	SoundLibrary();
	bool Initialize(IDirectSound8* sDevice);
	bool IsInitialized();
	GameSoundBuffer* Search(std::string);

private:
	IDirectSound8* sDevice;
	std::map<std::string, GameSoundBuffer*> library;
	bool isInitialized;

};

#endif