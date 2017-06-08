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
class Renderable;


using namespace std;

class CharacterSheet {
public:
	CharacterSheet(State* stateP, Texture* texture);
	void loadAnimations();
	bool initializeAnimations(Direct3D * direct3D, HWND * hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels);
	void updateAnimations(unsigned long deltaTime, Renderable* parent);
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
	Sprite* getSprite(int row, int offset);
	State* sheet_stateP;
};

#include "State.h"
#include "Animation.h"