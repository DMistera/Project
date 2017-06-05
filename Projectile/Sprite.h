#pragma once

#include "TextureShader.h"
#include "Vector.h"
#include "Shader.h"
#include "Model.h"
#include "Direct3D.h"
#include "Camera.h"
#include <string>
#include <list>
#include "Renderable.h"
#include "Transition.h"

using namespace std;

class Sprite : public Renderable{
public:
	Sprite(Texture* texture, Shader* shader, Model* model);
	bool initialize(Direct3D* direct3D, HWND* hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) override;
	bool render(Direct3D* direct3D, HWND* hwnd, Camera* camera) override;
	void shutdown();
	Vector getPosition();
	void setPosition(Vector);
	void setX(float v);
	void setY(float v);
	void setWidthScale(float v);
	void setHeightScale(float v);
	void setColor(Vector v);
	void setAlpha(float v);
	void setScale(Vector v);
	void updateTransitions();
protected:
	bool initializeTexture(list<Texture*>* loadedTextures, Direct3D * direct3D, HWND * hwnd);
	bool initializeShader(list<Shader*>*, Direct3D* direct3D, HWND* hwnd);
	bool initializeModel(list<Model*>*, Direct3D*, HWND*);
	list<Transition*>* transitions;
	Vector position;
	Vector scale;
	Texture* texture;
	Shader* shader;
	Model* model;
	Vector color;
	float alpha;
};