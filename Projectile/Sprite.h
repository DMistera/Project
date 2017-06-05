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
	bool update() override;
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
	void moveX(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void moveY(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void move(Transition::Easing easing, unsigned long startTime, unsigned long endTime, Vector startValue, Vector endValue);
	void scaleX(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void scaleY(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void scale(Transition::Easing easing, unsigned long startTime, unsigned long endTime, Vector startValue, Vector endValue);
	void fade(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void red(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void green(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void blue(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void color(Transition::Easing easing, unsigned long startTime, unsigned long endTime, Vector startValue, Vector endValue);
	void updateTransitions();
protected:
	bool initializeTexture(list<Texture*>* loadedTextures, Direct3D * direct3D, HWND * hwnd);
	bool initializeShader(list<Shader*>*, Direct3D* direct3D, HWND* hwnd);
	bool initializeModel(list<Model*>*, Direct3D*, HWND*);
	list<Transition*>* transitions;
	Vector position;
	Vector scaleVector;	   //TODO Change to Vector2 and Vector3
	Texture* texture;
	Shader* shader;
	Model* model;
	Vector colorVector;
	float alpha;
};