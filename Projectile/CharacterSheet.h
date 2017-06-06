#pragma once

#include <vector>
#include "Vector2.h"

#include "Animation.h"
#include "TextureShader.h"
#include "Bitmap.h"

using namespace std;

class CharacterSheet {
public:
	void loadAnimations();
	bool initializeAnimations(Direct3D * direct3D, HWND * hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels);
	CharacterSheet(Texture* texture);
protected:
	const float width = 832.0f;
	const float height = 1344.0f;
	Animation * walkUp;
	Animation * walkDown;
	Animation * walkLeft;
	Animation * walkRight;
	const float size = 64.0f;
	Texture* texture;
	Animation * getAnimation(float row, float frameCount, unsigned long delay, bool loop);
	Animation * getAnimation(float row, float frameCount);
	vector<Model*>* getModels(float row, float frameCount);
};

#define H_CHARACTERSHEET