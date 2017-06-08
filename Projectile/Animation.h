#pragma once

#include <vector>
#include "Renderable.h"

class Sprite;
class Direct3D;
class Camera;

class Animation : public Renderable {
public:
	Animation(State* stateP, vector<Sprite*>* frames);
	Animation(State* stateP, vector<Sprite*>* frames, unsigned long delay, bool loop);
	void start();
	void reset();
	bool hasStarted();
	// Inherited via Renderable
	virtual bool render(Direct3D * direct3D, HWND * hwnd, Camera * camera) override;
	virtual bool initialize(Direct3D * direct3D, HWND * hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) override;
private:
	vector<Sprite*>* frames;
	unsigned long delay;
	bool loop;
	unsigned long startTime;
	// Inherited via Renderable
	virtual void shutdownComponent() override;
	virtual bool updateComponent(unsigned long deltaTime) override;

};

#include "Sprite.h"
