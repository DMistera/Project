#include "Animation.h"

Animation::Animation(State* stateP, vector<Sprite*>* frames) : Animation(stateP, frames, 100, true) {
}

Animation::Animation(State* stateP, vector<Sprite*>* frames, unsigned long delay, bool loop) : Renderable(stateP) {
	this->frames = frames;
	this->delay = delay;
	this->loop = loop;
}

void Animation::start() {
	startTime = (unsigned long)GetTickCount64();
}

void Animation::reset() {
	start();
}

bool Animation::render(Direct3D * direct3D, HWND * hwnd, Camera * camera) {
	unsigned long currentTime = (unsigned long)GetTickCount64();
	unsigned int frameCount = frames->size();
	unsigned int i = 0;
	for (unsigned long time = startTime - delay; time < currentTime; time += delay)
		i++;
	i %= frameCount;
	return frames->at(i)->render(direct3D, hwnd, camera);
}


bool Animation::initialize(Direct3D * direct3D, HWND * hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) {
	for (Sprite* &sprite : *frames)
		if (!(sprite->initialize(direct3D, hwnd, loadedTextures, loadedShaders, loadedModels)))
			return false;
	return true;
}

void Animation::shutdownComponent() {
	for (Sprite* &sprite : *frames)
		sprite->shutdown();
}

bool Animation::updateComponent(unsigned long deltaTime) {
	for (Sprite* &sprite : *frames)
		sprite->acquireParameters(position, scaleVector, colorVector, alpha, rotation);
	return true;
}
