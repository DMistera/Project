#pragma once

#include "State.h"
#include "Bitmap.h"

class Game;
class System;

class Cursor : public State {
public:
	// Inherited via State
	Cursor(Game* gameP, System* systemP);
	virtual bool initialize() override;
	virtual bool update(long) override;
	virtual void shutdown() override;
	Vector getCursorPosition();
private:
	Sprite* cursor;
};