#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include "Definitions.h"
#include "View.h"



class GameSprite{
public:

	GameSprite();
	~GameSprite();

	GAME_FLT GetHeight();
	GAME_FLT GetWidth();

	bool Initialize(GAME_DEVICE device, GAME_STR, GAME_INT width, GAME_INT height);
	bool IsInitialized();
	virtual void Draw(GAME_FLT GameTime, View* viewer, GAME_VEC ObjectPosition, GAME_FLT ObjectAngle);

private:

	GAME_FLT width;
	GAME_FLT height;

	GAME_COLOR_RGB color;
	bool initialized;

	GAME_TEXTURE tex;
	GAME_SPRITE sprite;

};

#endif