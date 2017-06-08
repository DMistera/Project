#include "Character.h"

Character::Character(State* stateP) : CharacterSheet(stateP, new Texture("Resources//Textures//lpc_body.dds")), Renderable(stateP) {
	direction = UP;
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
	float shift = 1.0f*deltaTime;
	Vector2 vector;

	if (input->isKeyDown(DIK_LEFT)) {
		vector.addX(-shift);
	}
	if (input->isKeyDown(DIK_RIGHT)) {
		vector.addX(shift);
	}
	if (input->isKeyDown(DIK_UP)) {
		vector.addY(shift);
	}
	if (input->isKeyDown(DIK_DOWN)) {
		vector.addY(-shift);
	}

	if (input->isKeyDown(DIK_LEFT) && vector.getY() == 0) {
		direction = LEFT;
		if(!(currentFrame == walkLeft)) { 
			currentFrame = walkLeft;
			walkLeft->start();
		}
	}
	if (input->isKeyDown(DIK_RIGHT) && vector.getY() == 0) {
		direction = RIGHT;
		if (!(currentFrame == walkRight)) {
			currentFrame = walkRight;
			walkRight->start();
		}
	}
	if (input->isKeyDown(DIK_UP) && vector.getX() == 0) {
		direction = UP;
		if (!(currentFrame == walkUp)) {
			currentFrame = walkUp;
			walkUp->start();
		}
	}
	if (input->isKeyDown(DIK_DOWN) && vector.getX() == 0) {
		direction = DOWN;
		if (!(currentFrame == walkDown)) {
			currentFrame = walkDown;
			walkDown->start();
		}
	}

	if (vector.getX() == 0 && vector.getY() == 0) {
		switch (direction) {
		case UP:
			currentFrame = standUp;
			break;
		case DOWN:
			currentFrame = standDown;
			break;
		case LEFT:
			currentFrame = standLeft;
			break;
		case RIGHT:
			currentFrame = standRight;
			break;
		}
	}
	position.add(vector);
	camera->move(Vector3(vector.getX(), vector.getY(), 0.0f));
	updateAnimations(deltaTime, this);
	return true;
}
