#ifndef ARTASSETLIBRARY
#define ARTASSETLIBRARY

#include<map>
#include<string>
#include"GraphicsDevice.h"
#include"GameSprite.h"

class ArtAssetLibrary{

public:
	ArtAssetLibrary();
	bool Insert(std::string name, std::string path, GAME_INT width, GAME_INT height);
	bool Initialize(GraphicsDevice* gDevice);
	bool IsInitialized();
	GameSprite* Search(std::string);

private:
	GraphicsDevice* gDevice;
	std::map<std::string, GameSprite*> library;

};

#endif