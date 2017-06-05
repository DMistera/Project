#include "Animation.h"

Animation::Animation(vector<Sprite*>* frames, unsigned long delay, bool loop) {
}

void Animation::start() {
}

void Animation::reset() {
}

bool Animation::render(Direct3D * direct3D, HWND * hwnd, Camera * camera) {
	return false;
}


bool Animation::initialize(Direct3D * direct3D, HWND * hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) {
	return false;
}
