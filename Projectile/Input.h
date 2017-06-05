#pragma once

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>
#include "Vector2.h"

class System;

class Input {
public:
	Input();
	~Input();
	bool initialize(System* systemP);
	void shutdown();
	bool frame();
	bool isKeyDown(unsigned int key);
	bool isKeyUp(unsigned int key);
	Vector2 getMousePosition();
private:
	bool readKeyboard();
	bool readMouse();
	void processInput();
	bool keys[256];
	int screenWidth, screenHeight, mouseX, mouseY;
	IDirectInput8* directInput;
	IDirectInputDevice8* keyboard;
	IDirectInputDevice8* mouse;
	unsigned char keyboardState[256];
	DIMOUSESTATE mouseState;
};