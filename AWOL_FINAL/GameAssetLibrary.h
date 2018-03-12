#ifndef GAMEASSETLIBRARY
#define GAMEASSETLIBRARY

#include<map>
#include<string>
#include"ObjectFactory.h"

class GameAssetLibrary{

public:
	GameAssetLibrary();
	bool Initialize();
	bool IsInitialized();
	void GameAssetLibrary::Insert(std::string);
	Object* Search(std::string);

private:
	std::map<std::string,ObjectFactory*> library;

};

#endif