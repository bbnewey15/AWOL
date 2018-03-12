#include "SoundLibrary.h"

SoundLibrary::SoundLibrary(){}


bool SoundLibrary::Initialize(IDirectSound8* sDevice){
	
	this->sDevice = sDevice;

	//most sound effects from http://soundbible.com/

	GameSoundBuffer* bulletSound = new GameSoundBuffer();
	if(!bulletSound->Initialize(sDevice,"./Sounds/bulletSound.wav")){
			std::string s = "There was an issue creating the sound. Make sure the requested wav is available.";
			MessageBox(NULL, s.c_str(), NULL, NULL);
			return false;
	}else{
		library["bulletSound"] = bulletSound;
	}

	GameSoundBuffer* infDead = new GameSoundBuffer();
	if(!infDead->Initialize(sDevice,"./Sounds/infDead.wav")){
			std::string s = "There was an issue creating the sound. Make sure the requested wav is available.";
			MessageBox(NULL, s.c_str(), NULL, NULL);
			return false;
	}else{
		library["infDead"] = infDead;
	}
	
	GameSoundBuffer* carrierDead = new GameSoundBuffer();
	if(!carrierDead->Initialize(sDevice,"./Sounds/carrierDead1.wav")){
			std::string s = "There 2was an issue creating the sound. Make sure the requested wav is available.";
			MessageBox(NULL, s.c_str(), NULL, NULL);
			return false;
	}else{
		library["carrierDead"] = carrierDead;
	}

	//my music
	GameSoundBuffer* my10am = new GameSoundBuffer();
	if(!my10am->Initialize(sDevice,"./Sounds/my10am.wav")){
			std::string s = "There 3was an issue creating the sound. Make sure the requested wav is available.";
			MessageBox(NULL, s.c_str(), NULL, NULL);
			return false;
	}else{
		library["my10am"] = my10am;
	}
	



	return(true);
}


GameSoundBuffer* SoundLibrary::Search(std::string query){
	return((*library.find(query)).second);
}

bool SoundLibrary::IsInitialized(){
	return(isInitialized);
}