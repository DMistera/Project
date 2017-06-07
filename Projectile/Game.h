#pragma once

#include "State.h"

class System;
class Playground;
class Cursor;
class Graphics;
class Input;

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
#include "Graphics.h"
#include "Playground.h"
#include "Cursor.h"