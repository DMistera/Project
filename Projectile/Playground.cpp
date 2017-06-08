#include "Playground.h"

Playground::Playground(Game * gameP, System * systemP) : State (gameP, systemP) {
}

bool Playground::initialize() {
	makeGrass();
	showText();
	if (!(addSprite(new Character(this))))
		return false;
	return true;
}

bool Playground::showText() {
	text = new Text(this, "Naxess is a viking");
	if (!addSprite(text))
		return false;
	return true;
}

bool Playground::makeGrass() {
	Sprite* grass = new Block(this);
	addSprite(grass);
	for (int i = 0; i < 100; i++) {
		grass->move(Transition::Easing::LINEAR, i * 1000, (i + 1) * 1000, -50, 50);
	}
	return true;
}

bool Playground::update(long deltaTime) {
	float x = gameP->getInput()->getMousePosition().getX();
	text->setText(to_string(x));
	return true;
}

void Playground::shutdown() {
}
