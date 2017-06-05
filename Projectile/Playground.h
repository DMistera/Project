#pragma once

#include "State.h"
#include "Block.h"

class Game;
class System;

//I don't know why but including it first doesn't work
class Text;

class Playground : public State {
public:
	Playground(Game* gameP, System* systemP);
	 bool initialize() override;
	 bool showText();
	 bool update(long) override;
	 void shutdown() override;
private:
	void moveCamera(long);
	bool makeGrass();
	Text* text;
};

#include "Game.h"
#include "System.h"
#include "Text.h"
