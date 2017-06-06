#include "Playground.h"

Playground::Playground(Game * gameP, System * systemP) : State (gameP, systemP) {
}

bool Playground::initialize() {
	makeGrass();
	showText();
	if (!(addSprite(new Character())))
		return false;
	return true;
}

bool Playground::showText() {
	text = new Text("Naxess is a viking");
	if (!addSprite(text))
		return false;
	return true;
}

bool Playground::makeGrass() {
	Sprite* grass = new Block();
	addSprite(grass);
	for (int i = 0; i < 100; i++) {
		grass->move(Transition::Easing::LINEAR, i * 1000, (i + 1) * 1000, -50, 50);
	}
	return true;
}

bool Playground::update(long deltaTime) {
	moveCamera(deltaTime);
	text->setText(to_string(sizeof(unsigned int)) + " " + to_string(sizeof(Vector3)));
	return true;
}

void Playground::shutdown() {
}

void Playground::moveCamera(long deltaTime) {
	Input* input = gameP->getInput();
	float shift = 0.04f*deltaTime;
	if (input->isKeyDown(DIK_UP))
		camera->move(Vector3(0.0f, shift, 0.0f));
	if (input->isKeyDown(DIK_DOWN))
		camera->move(Vector3(0.0f, -shift, 0.0f));
	if (input->isKeyDown(DIK_LEFT))
		camera->move(Vector3(-shift, 0.0f, 0.0f));
	if (input->isKeyDown(DIK_RIGHT))
		camera->move(Vector3(shift, 0.0f, 0.0f));
}
