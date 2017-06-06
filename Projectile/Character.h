#pragma once

#include "CharacterSheet.h"

#ifdef H_CHARACTERSHEET

class Character : public CharacterSheet, public Renderable {
public:
	Character();
	// Inherited via Renderable
	virtual bool render(Direct3D * direct3D, HWND * hwnd, Camera * camera) override;
	virtual bool initialize(Direct3D * direct3D, HWND * hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) override;
private:
	Animation* currentAnimation;
	virtual void shutdownComponent() override;
	virtual bool updateComponent() override;
};

#endif //H_CHARACTERSHEET