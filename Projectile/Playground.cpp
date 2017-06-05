#include "Playground.h"

#include "Game.h"
#include "System.h"

Playground::Playground(Game * gameP, System * systemP) : State (gameP, systemP) {
}

bool Playground::initialize() {
	makeGrass();
	showText();
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
	grass->setScale(Vector(2.0f, 0.5f));
	return true;
}

bool Playground::update(long deltaTime) {
	moveCamera(deltaTime);
	Vector mousePosition = gameP->getInput()->getMousePosition();
	text->setText("x: " + to_string(mousePosition.getX()));
	return true;
}

void Playground::shutdown() {
}

void Playground::moveCamera(long deltaTime) {
	Input* input = gameP->getInput();
	float shift = 0.04f*deltaTime;
	if (input->isKeyDown(DIK_UP))
		camera->move(Vector(0.0f, shift, 0.0f));
	if (input->isKeyDown(DIK_DOWN))
		camera->move(Vector(0.0f, -shift, 0.0f));
	if (input->isKeyDown(DIK_LEFT))
		camera->move(Vector(-shift, 0.0f, 0.0f));
	if (input->isKeyDown(DIK_RIGHT))
		camera->move(Vector(shift, 0.0f, 0.0f));
}
