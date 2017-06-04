#pragma once
#include <Windows.h>
#include <list>	
#include "Direct3D.h"
#include "Camera.h"
#include "Sprite.h"

class System;

class Graphics {
public:
	Graphics();
	~Graphics();
	bool initialize(System* systemP);
	void shutdown();
	Direct3D* getDirect3D();
private:
	Direct3D* direct3D;
};
