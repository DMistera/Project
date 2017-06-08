#pragma once

#include "Direct3D.h"
#include <list>
#include "Vector3.h"
#include "Vector2.h"
#include "Camera.h"
#include "Shader.h"
#include "Model.h"
#include "Texture.h"
#include "Transition.h"

class State;

using namespace std;

class Renderable {
public:
	Renderable(State* stateP);
	virtual bool render(Direct3D* direct3D, HWND* hwnd, Camera* camera) = 0;
	bool update(unsigned long deltaTime);
	virtual bool initialize(Direct3D* direct3D, HWND* hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) = 0;
	void shutdown();
	void setPosition(Vector2 v);
	void setX(float v);
	void setY(float v);
	void setWidthScale(float v);
	void setHeightScale(float v);
	void setColor(Vector3 v);
	void setAlpha(float v);
	void setScale(Vector2 v);
	void moveX(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void moveY(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void move(Transition::Easing easing, unsigned long startTime, unsigned long endTime, Vector3 startValue, Vector3 endValue);
	void scaleX(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void scaleY(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void scale(Transition::Easing easing, unsigned long startTime, unsigned long endTime, Vector3 startValue, Vector3 endValue);
	void fade(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void red(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void green(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void blue(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void color(Transition::Easing easing, unsigned long startTime, unsigned long endTime, Vector3 startValue, Vector3 endValue);
	void acquireParameters(Vector2 position, Vector2 scaleVector, Vector3 colorVector, float alpha, float rotation);
	void acquireParameters(Renderable*);
	Vector2 getPosition();
	Vector2 getScale();
	Vector3 getColor();
	float getAlpha();
	float getRotation();
protected:
	State* stateP;
	void updateTransitions();
	virtual bool updateComponent(unsigned long deltaTime) = 0;
	virtual void shutdownComponent() = 0;
	list<Transition*>* transitions;
	Vector2 position;
	Vector2 scaleVector;
	Vector3 colorVector;
	float alpha;
	float rotation;
};

#define H_RENDERABLE

#include "State.h"