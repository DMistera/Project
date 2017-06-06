#pragma once

#include "Graphics.h"
#include "Playground.h"
#include "Cursor.h"

class System;

class Game {
public:
	Game(System * systemP);
	bool initialize(int screenWidth, int screenHeight, bool fullScreen);
	bool addState(State * state);
	bool update(long);
	bool render();
	void shutdown();
	Graphics* getGraphics();
	Input* getInput();
private:
	Input* input;
	Graphics* graphics;
	list<State*>* states;
	System* systemP;
	HWND* hwnd;
};

#include "System.h"