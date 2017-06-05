#pragma once

class Renderable;

class Transition {
public:
	enum Easing {
		LINEAR, QUADRATIC_IN, QUADRATIC_OUT
	};
	enum Type {
		MOVE_X, MOVE_Y, SCALE_X, SCALE_Y, FADE, COLOR_RED, COLOR_GREEN, COLOR_BLUE
	};
	Transition(Renderable* sprite, Type type, Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue);
	void update();
	bool isOutdated();
private:
	float getValue();
	Renderable* target;
	Type type;
	Easing easing;
	unsigned long startTime;
	unsigned long endTime;
	float startValue;
	float endValue;
};

#include "Renderable.h"