#include "Cursor.h"

Cursor::Cursor(Game* gameP, System* systemP) : State(gameP, systemP) {
	cursor = 0;
}

bool Cursor::initialize() {
	cursor = new Sprite(this, new Texture("Resources//Textures//cursor.dds"), new TextureShader(), new Bitmap(20.0f, 20.0f));
	if (!addSprite(cursor))
		return false;
	cursor->setColor(Vector3(0.0f, 1.0f, 0.0f));
	cursor->setAlpha(0.3f);
	return true;
}

bool Cursor::update(long) {
	Vector2 cursorPosition = gameP->getInput()->getMousePosition();
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

Vector2 Cursor::getCursorPosition() {
	return cursor->getPosition();
}
