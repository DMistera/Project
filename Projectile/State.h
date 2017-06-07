#pragma once

#include <list>
#include "Input.h"
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "Renderable.h"

class Camera;
class Game;
class System;

class State {
public:
	State(Game* gameP, System* systemP);
	virtual bool initialize() = 0;
	virtual void shutdown() = 0;
	virtual bool update(long deltaTime) = 0;
	bool render();
	bool updateObjects(unsigned long);
	Game* getGamePointer();
	Camera* getCamera();
protected:
	bool addSprite(Renderable * object);
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

#define H_STATE

#include "Game.h"
#include "System.h"