#pragma once

#include "CharacterSheet.h"

class Character : public CharacterSheet, public Renderable {
public:
	Character(State* state);
	// Inherited via Renderable
	virtual bool render(Direct3D * direct3D, HWND * hwnd, Camera * camera) override;
	virtual bool initialize(Direct3D * direct3D, HWND * hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) override;
private:
	enum Direction {
		UP, DOWN, LEFT, RIGHT
	};
	Renderable* currentFrame;
	virtual void shutdownComponent() override;
	virtual bool updateComponent(unsigned long deltaTime) override;
	Direction direction;
};
