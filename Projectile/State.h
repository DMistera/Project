#pragma once

#include <list>
#include "Sprite.h"
#include "Input.h"

class Game;
class System;

class State {
public:
	State(Game* gameP, System* systemP);
	virtual bool initialize() = 0;
	virtual bool update(long) = 0;
	virtual void shutdown() = 0;
	bool render();
protected:
	bool initializeObject(Renderable * object);
	//Loaded assets
	list<Model*>* loadedModels;
	list<Texture*>* loadedTextures;
	list<Shader*>* loadedShaders;
	list<Renderable*>* objects;
	Camera* camera;
	int screenWidth;
	int screenHeight;
	Game* gameP;
	System* systemP;
};