#include "MusicManager.h"

MusicManager::MusicManager(){
	sLibrary = NULL;
	currentSong = NULL;
	soundPlaying = false;
}


bool MusicManager::Initialize(SoundLibrary* sLibrary){
	this->sLibrary = sLibrary;

	return(true);
}




void MusicManager::Update(){
	/*
	currentSong = (sLibrary->Search("my10am"));
	soundPlaying = currentSong->IsPlaying();
	//should repeat
	if(!soundPlaying){
		currentSong->PlaySound();
	}
	*/
	


}

