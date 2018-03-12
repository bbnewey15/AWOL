#ifndef TREE_H
#define TREE_H

#include "Object.h"
#include "Definitions.h"

class Tree : public Object{
			
public:
	Tree();
	Object* Update(GAME_FLT, View*);
	void Draw(GAME_FLT, View*);

};

#endif