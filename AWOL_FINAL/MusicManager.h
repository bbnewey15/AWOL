#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include "GameSoundBuffer.h"
#include "SoundLibrary.h"
#include "Definitions.h"

class MusicManager {
			
public:
	MusicManager();
	
	bool Initialize(SoundLibrary*);
	void Update();
	
private:
	

	bool soundPlaying;
	SoundLibrary* sLibrary;
	GameSoundBuffer* currentSong;
};

#endif