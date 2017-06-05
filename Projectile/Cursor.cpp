#include "Cursor.h"

#include "Game.h"
#include "System.h"

Cursor::Cursor(Game* gameP, System* systemP) : State(gameP, systemP) {
	cursor = 0;
}

bool Cursor::initialize() {
	cursor = new Sprite(new Texture("Resources//Textures//cursor.dds"), new TextureShader(), new Bitmap(20.0f, 20.0f));
	if (!addSprite(cursor))
		return false;
	cursor->setColor(Vector(0.0f, 1.0f, 0.0f));
	cursor->setAlpha(0.3f);
	return true;
}

bool Cursor::update(long) {
	Vector cursorPosition = gameP->getInput()->getMousePosition();
	cursorPosition.setX(cursorPosition.getX() - (systemP->getScreenWidth()/2));
	cursorPosition.setY(-cursorPosition.getY() + (systemP->getScreenHeight() / 2));
	cursor->setPosition(cursorPosition);
	return true;
}

void Cursor::shutdown() {
	cursor->shutdown();
	delete cursor;
	cursor = 0;
}

Vector Cursor::getCursorPosition() {
	return cursor->getPosition();
}
