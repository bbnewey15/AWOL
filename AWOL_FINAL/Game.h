#ifndef GAME_H
#define GAME_H

#include <Box2D/Box2D.h>
#include <vector>
#include "Definitions.h"
#include "Object.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "View.h"
#include "GameAssetLibrary.h"
#include "ArtAssetLibrary.h"
#include "PhysicsAssetLibrary.h"
#include "GameContactListener.h"
#include "SoundDevice.h"
#include "GameSound.h"
#include "SoundLibrary.h"
#include "MusicManager.h"


class Game{

public:

	//Constructor/Destructor
	Game();
	~Game();

	//Game Functions
	bool Initialize(HWND hWnd, HINSTANCE hInstance);
	bool LoadLevelFromXML(const char* path);
	bool Run();
	void Update(float gameTime);
	void Draw(float gameTime);

	int GetScore();
	void SetScore(int);

private:
	GraphicsDevice* gDevice;
	InputDevice* iDevice;
	SoundDevice* sDevice;
	GameAssetLibrary* gLibrary;
	ArtAssetLibrary* aLibrary;
	PhysicsAssetLibrary* pLibrary;
	SoundLibrary* sLibrary;
	MusicManager* mManager;

	const b2Vec2 gravity;
	b2World* world;
	GameContactListener gcl;

	View* view;
	std::vector<Object*> objects;
	GAME_FLT gameTime;
	GAME_FLT stepTime;

	Object* playerObject;
	GAME_INT score;
	GAME_INT playerHealth;

	b2Timer t;
	GAME_INT timeleft;
};

#endif