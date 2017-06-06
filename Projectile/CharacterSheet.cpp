#include "CharacterSheet.h"

void CharacterSheet::loadAnimations() {
	walkUp = getAnimation(8, 9);
	walkDown = getAnimation(10, 9);
	walkLeft = getAnimation(9, 9);
	walkRight = getAnimation(11, 9);
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

CharacterSheet::CharacterSheet(Texture * texture) {
	this->texture = texture;
}

Animation * CharacterSheet::getAnimation(float row, float frameCount, unsigned long delay, bool loop) {
	vector<Sprite*>* frames = new vector<Sprite*>;
	for (Model* &model : (*getModels(row, frameCount))) {
		frames->push_back(new Sprite(texture, new TextureShader(), model));
	}
	return new Animation(frames, delay, loop);
}

Animation * CharacterSheet::getAnimation(float row, float frameCount) {
	vector<Sprite*>* frames = new vector<Sprite*>;
	for (Model* &model : (*getModels(row, frameCount))) {
		frames->push_back(new Sprite(texture, new TextureShader(), model));
	}
	return new Animation(frames);
}

//Note: row starts from 0;
vector<Model*>* CharacterSheet::getModels(float row, float frameCount) {
	vector<Model*>* models = new vector<Model*>;
	float side = 64.0f;
	float startY = side*row;
	float startX = 0;
	for (int i = 0; i < frameCount; i++) {
		models->push_back(new Bitmap(size, size, Vector2(startX/width, startY/height), Vector2((startX + side)/width, (startY + side)/height)));
		startX += side;
	}
	return models;
}
