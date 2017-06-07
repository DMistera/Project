#include "Character.h"

Character::Character(State* stateP) : CharacterSheet(stateP, new Texture("Resources//Textures//lpc_body.dds")), Renderable(stateP) {

}

bool Character::render(Direct3D * direct3D, HWND * hwnd, Camera * camera) {
	return currentFrame->render(direct3D, hwnd, camera);
}

bool Character::initialize(Direct3D * direct3D, HWND * hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) {
	loadAnimations();
	if (!(initializeAnimations(direct3D, hwnd, loadedTextures, loadedShaders, loadedModels)))
		return false;
	currentFrame = walkUp;

	return true;
}

void Character::shutdownComponent() {
}

bool Character::updateComponent(unsigned long deltaTime) {
	Input* input = stateP->getGamePointer()->getInput();
	Camera* camera = stateP->getCamera();
	if (input->isKeyDown(DIK_LEFT)) {

	}
	//TODO Movement
	return true;
}
