#include "Text.h"

Text::Text(State* stateP, string text) : Renderable(stateP) {
	this->text = text;
	letters = new vector<Sprite*>;
	size = 20.0f;
}

bool Text::initialize(Direct3D* direct3D, HWND* hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) {
	for (int i = startCharacter; i < startCharacter + rows*columns; i++) {
		Vector2 topLeft;
		Vector2 bottomRight;
		getTextureBorders(&topLeft, &bottomRight, i);
		Sprite* letter = new Sprite(stateP, 
			new Texture("Resources//Textures//font.dds"),
			new TextureShader(),
			new Bitmap(size, size, topLeft, bottomRight));
		if (!(letter->initialize(direct3D, hwnd, loadedTextures, loadedShaders, loadedModels)))
			return false;
		letters->push_back(letter);
	}
	return true;
}

bool Text::render(Direct3D * direct3D, HWND * hwnd, Camera * camera) {
	float startX = position.getX() - getWidth() / 2;
	for (unsigned int i = 0; i < text.length(); i++) {
		int index = text.at(i) - startCharacter;
		Sprite* letter = letters->at(index);
		letter->setPosition(Vector2(startX, position.getY()));
		if (!(letter->render(direct3D, hwnd, camera)))
			return false;
		startX += size;
	}
	return true;
}

void Text::getTextureBorders(Vector2* topLeft, Vector2* bottomRight, int character) {
	int order = character - startCharacter;
	topLeft->setX((1.0f / columns)*(order % columns));
	topLeft->setY((1.0f / rows)*(order / columns));
	bottomRight->setX(topLeft->getX() + (1.0f / columns));
	bottomRight->setY(topLeft->getY() + (1.0f / rows));
}

float Text::getWidth() {
	return text.length()*size;
}

void Text::setText(string text) {
	this->text = text;
}

void Text::shutdownComponent() {
}

bool Text::updateComponent(unsigned long deltaTime) {
	return true;
}
