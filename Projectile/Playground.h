#pragma once

#include "State.h"

class Game;
class System;
class Text;
class Block;
class Character;

class Playground : public State {
public:
	Playground(Game* gameP, System* systemP);
	 bool initialize() override;
	 bool showText();
	 bool update(long) override;
	 void shutdown() override;
private:
	bool makeGrass();
	Text* text;
};

#include "Game.h"
#include "System.h"
#include "Text.h"
#include "Block.h"
#include "Character.h"
