#include "ArtAssetLibrary.h"

ArtAssetLibrary::ArtAssetLibrary(){}

bool ArtAssetLibrary::Insert(const std::string name, std::string path, GAME_INT width, GAME_INT height){
	
	GameSprite* sprite = new GameSprite();
	if(sprite->Initialize(gDevice->device,path,width,height)){
		library[name] = sprite;
		return true;
	}else{
		return false;
	}

}

bool ArtAssetLibrary::Initialize(GraphicsDevice* gDevice){
	
	this->gDevice = gDevice;


	return(true);
}


GameSprite* ArtAssetLibrary::Search(std::string query){
	return((*library.find(query)).second);
}