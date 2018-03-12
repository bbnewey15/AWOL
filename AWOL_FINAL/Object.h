#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "Definitions.h"
#include "GameSprite.h"
#include "View.h"
#include "InputDevice.h"
#include "GamePhysics.h"
#include <Box2D/Box2D.h>
#include "GameSoundBuffer.h"
#include "SoundLibrary.h"


//Forward declare for pointers

class View;
class GameAssetLibrary;
class ArtAssetLibrary;
class PhysicsAssetLibrary;
//class SoundLibrary;


class Object{
			
public:

	//Basic Methods
	Object();
	~Object();

	b2Body* GetBody();
	GamePhysics* GetPhysics();

	bool GetIsDead();
	std::string GetId();
	void SetIsDead(bool);
	void SetSprite(std::string);
	bool GetAddScore();
	GAME_INT GetHealth();
	void SetHealth(GAME_INT);


	bool Initialize(std::string key, InputDevice* iDevice, std::vector<Object*>* objects, 
					GameAssetLibrary* gLibrary, ArtAssetLibrary* aLibrary, PhysicsAssetLibrary* pLibrary,
					SoundLibrary* sLibrary, b2World* world, GAME_FLT x, GAME_FLT y, GAME_FLT angle);

	virtual bool PostInitialize();

	bool IsInitialized();

	//Game world methods
	virtual Object* Update(GAME_FLT GameTime, View* view)=0;
	virtual void Draw(GAME_FLT, View* view)=0;

protected:

	//Resources
	InputDevice* iDevice;
	GameAssetLibrary* gLibrary;
	ArtAssetLibrary* aLibrary;
	PhysicsAssetLibrary* pLibrary;
	SoundLibrary* sLibrary;
	std::vector<Object*>* objects;
	GamePhysics* physics;
	bool initialized;

	//Game World
	std::string id;
	bool isDead;
	GAME_INT health;
	bool didScore;

	//Render World
	GameSprite* sprite;

	//Physics World
	b2World* world;
	b2Body* body;
	
};

#endif