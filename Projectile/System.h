#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Game.h"

class System {
public:
	System();
	~System();
	bool initialize();
	void shutdown();
	void run();
	LRESULT CALLBACK messageHandler(HWND, UINT, WPARAM, LPARAM);
	 HWND* getHWND();
	 HINSTANCE* getInstance();
	 int getScreenWidth();
	 int getScreenHeight();
	 bool getFullScreen();
private:
	 HWND hwnd;
	bool frame(long);
	void initializeWindows();
	void shutdownWindows();
	LPCSTR applicationName;
	HINSTANCE instance;
	Game* game;
	bool fullScreen;
	int screenWidth;
	int screenHeight;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static System* ApplicationHandle = 0;