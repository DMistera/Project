#pragma once

#include "State.h"
#include "Block.h"
#include "Character.h"
#include "Text.h"

class Game;
class System;

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
