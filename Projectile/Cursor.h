#pragma once

#include "Bitmap.h"
#include "State.h"
#include "Sprite.h"

class Game;
class System;

class Cursor : public State {
public:
	// Inherited via State
	Cursor(Game* gameP, System* systemP);
	virtual bool initialize() override;
	virtual bool update(long) override;
	virtual void shutdown() override;
	Vector2 getCursorPosition();
private:
	Sprite* cursor;
};

#include "Game.h"
#include "System.h"