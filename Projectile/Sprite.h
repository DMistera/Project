#pragma once

#include "Renderable.h"
#include <string>

using namespace std;

class Sprite : public Renderable{
public:
	Sprite(State* stateP, Texture* texture, Shader* shader, Model* model);
	bool initialize(Direct3D* direct3D, HWND* hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) override;
	bool render(Direct3D* direct3D, HWND* hwnd, Camera* camera) override;
protected:
	// Inherited via Renderable
	virtual bool updateComponent(unsigned long deltaTime) override;
	virtual void shutdownComponent() override;

	bool initializeTexture(list<Texture*>* loadedTextures, Direct3D * direct3D, HWND * hwnd);
	bool initializeShader(list<Shader*>*, Direct3D* direct3D, HWND* hwnd);
	bool initializeModel(list<Model*>*, Direct3D*, HWND*);
	Texture* texture;
	Shader* shader;
	Model* model;
};

#define H_SPRITE