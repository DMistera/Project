#include "Character.h"

Character::Character() : CharacterSheet(new Texture("Resources//Textures//lpc_body.dds")) {

}

bool Character::render(Direct3D * direct3D, HWND * hwnd, Camera * camera) {
	return currentAnimation->render(direct3D, hwnd, camera);
}

bool Character::initialize(Direct3D * direct3D, HWND * hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) {
	loadAnimations();
	if (!(initializeAnimations(direct3D, hwnd, loadedTextures, loadedShaders, loadedModels)))
		return false;
	currentAnimation = walkUp;

	currentAnimation->start();
	return true;
}

void Character::shutdownComponent() {
}

bool Character::updateComponent() {
	//TODO Movement
	return true;
}
