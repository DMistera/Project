#pragma once

#include <vector>
#include "Vector2.h"

#include "TextureShader.h"
#include "Bitmap.h"
#include <list>

class Animation;
class Direct3D;
class Texture;
class State;
class Sprite;


using namespace std;

class CharacterSheet {
public:
	CharacterSheet(State* stateP, Texture* texture);
	void loadAnimations();
	bool initializeAnimations(Direct3D * direct3D, HWND * hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels);
protected:
	const float width = 832.0f;
	const float height = 1344.0f;
	Sprite* standUp;
	Sprite* standDown;
	Sprite* standLeft;
	Sprite* standRight;
	Animation * walkUp;
	Animation * walkDown;
	Animation * walkLeft;
	Animation * walkRight;
	const float size = 64.0f;
private:
	Texture* sheet_texture;
	Animation * getAnimation(int row, int offset, int frameCount, unsigned long delay, bool loop);
	Animation * getAnimation(int row, int offset, int frameCount);
	vector<Model*>* getModels(int row, int offset, int frameCount);
	State* sheet_stateP;
};

#include "State.h"
#include "Animation.h"