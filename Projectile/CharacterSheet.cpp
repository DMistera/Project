#include "CharacterSheet.h"

void CharacterSheet::loadAnimations() {
	walkUp = getAnimation(8, 1, 8);
	walkDown = getAnimation(10, 1, 8);
	walkLeft = getAnimation(9, 1, 8);
	walkRight = getAnimation(11, 1, 8);
}

bool CharacterSheet::initializeAnimations(Direct3D * direct3D, HWND * hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) {
	if (!(walkUp->initialize(direct3D, hwnd, loadedTextures, loadedShaders, loadedModels)))
		return false;
	if (!(walkDown->initialize(direct3D, hwnd, loadedTextures, loadedShaders, loadedModels)))
		return false;
	if (!(walkLeft->initialize(direct3D, hwnd, loadedTextures, loadedShaders, loadedModels)))
		return false;
	if (!(walkRight->initialize(direct3D, hwnd, loadedTextures, loadedShaders, loadedModels)))
		return false;
	return true;
}

CharacterSheet::CharacterSheet(State * stateP, Texture * texture) {
	this->sheet_stateP = stateP;
	this->sheet_texture = texture;
}

Animation * CharacterSheet::getAnimation(int row, int offset, int frameCount, unsigned long delay, bool loop) {
	vector<Sprite*>* frames = new vector<Sprite*>;
	for (Model* &model : (*getModels(row, offset, frameCount))) {
		frames->push_back(new Sprite(sheet_stateP, sheet_texture, new TextureShader(), model));
	}
	return new Animation(sheet_stateP, frames, delay, loop);
}

Animation * CharacterSheet::getAnimation(int row, int offset, int frameCount) {
	vector<Sprite*>* frames = new vector<Sprite*>;
	for (Model* &model : (*getModels(row, offset, frameCount))) {
		frames->push_back(new Sprite(sheet_stateP, sheet_texture, new TextureShader(), model));
	}
	return new Animation(sheet_stateP, frames);
}

//Note: row starts from 0;
vector<Model*>* CharacterSheet::getModels(int row, int offset, int frameCount) {
	vector<Model*>* models = new vector<Model*>;
	float side = 64.0f;
	float startY = side*row;
	float startX = side*offset;
	for (int i = 0; i < frameCount; i++) {
		models->push_back(new Bitmap(size, size, Vector2(startX/width, startY/height), Vector2((startX + side)/width, (startY + side)/height)));
		startX += side;
	}
	return models;
}
