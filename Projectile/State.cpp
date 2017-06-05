#include "State.h"

#include "Game.h"
#include "System.h"

State::State(Game* gameP, System* systemP) {
	this->gameP = gameP;
	this->systemP = systemP;
	loadedTextures = new list<Texture*>;
	loadedShaders = new list<Shader*>;
	loadedModels = new list<Model*>;
	objects = new list<Renderable*>;
	camera = new Camera();
	camera->setPosition(Vector(0.0f, 0.0f, -1.0f));
}

bool State::render() {
	camera->render();
	for (Renderable* &sprite : *objects) {
		if (!(sprite->render(gameP->getGraphics()->getDirect3D(), systemP->getHWND(), camera)))
			return false;
	}
	return true;
}

void State::updateObjects() {
	for (Renderable* &object : *objects) {
		object->update();
	}
}

bool State::addSprite(Renderable* object) {
	if (!object->initialize(gameP->getGraphics()->getDirect3D(), systemP->getHWND(), loadedTextures, loadedShaders, loadedModels))
		return false;
	objects->push_back(object);
	return true;
}