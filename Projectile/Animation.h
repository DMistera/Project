#pragma once

#include "Renderable.h"
#include "Sprite.h"
#include <vector>

class Animation : public Renderable {
public:
	Animation(vector<Sprite*>* frames, unsigned long delay, bool loop);
	void start();
	void reset();
	// Inherited via Renderable
	virtual bool render(Direct3D * direct3D, HWND * hwnd, Camera * camera) override;
	virtual bool initialize(Direct3D * direct3D, HWND * hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) override;
private:
	vector<Sprite*>* frames;
	unsigned long delay;
	bool loop;

	//TODO finish this class
};