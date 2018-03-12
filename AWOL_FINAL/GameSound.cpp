//Based on http://www.rastertek.com/dx10tut14.html

#include"GameSound.h"


GameSound::GameSound(){ 
	buffer = NULL;
	initialized = false;
}

GameSound::~GameSound(){

}

bool GameSound::Release(){
	buffer = NULL;
	return(true);
}

bool GameSound::Initialize(	IDirectSoundBuffer* primaryBuffer){
	buffer=primaryBuffer;
	return(true);
}

bool GameSound::PlayWaveFile(){

	return true;

}

bool GameSound::IsPlaying(){

	bool playStatus = false;

	DWORD status;
	buffer->GetStatus(&status);
	if(status == DSBSTATUS_PLAYING)
		playStatus = true;

	return(playStatus);		

};
