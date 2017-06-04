#pragma once

#include "Sprite.h"
#include "Bitmap.h"
#include <vector>

class Text : public Renderable {
public:
	Text(string text);
	bool initialize(Direct3D * direct3D, HWND * hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) override;
	bool render(Direct3D* direct3D, HWND* hwnd, Camera* camera) override;
	void getTextureBorders(Vector * topLeft, Vector * bottomRight, int character);
	float getWidth();
	void setText(string text);
private:
	const int rows = 7;
	const int columns = 14;
	const int startCharacter = 32;
	vector<Sprite*>* letters;
	float size;
	string text;
	Vector position;
};