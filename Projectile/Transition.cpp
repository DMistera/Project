#include "Transition.h"

Transition::Transition(Renderable* sprite, Type type, Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	target = sprite;
	this->type = type;
	this->easing = easing;
	this->startTime = startTime + (unsigned long)GetTickCount64();
	this->endTime = endTime + (unsigned long)GetTickCount64();
	this->startValue = startValue;
	this->endValue = endValue;
}

void Transition::update() {
	if (GetTickCount64() > startTime) {
		float value = getValue();
		switch (type) {
		case MOVE_X:
			target->setX(value);
			break;
		case MOVE_Y:
			target->setY(value);
			break;
		case SCALE_X:
			target->setWidthScale(value);
			break;
		case SCALE_Y:
			target->setHeightScale(value);
			break;
		}
	}
}


float Transition::getValue() {
	float t = (float)(GetTickCount64() - startTime);
	float b = startValue;
	float c = endValue - startValue;
	float d = (float)(endTime - startTime);
	switch (easing) {
	case LINEAR:
		return c*t / d + b;
	case QUADRATIC_IN:
		t /= d;
		return c*t*t + b;
	case QUADRATIC_OUT:
		t /= d;
		return -c * t*(t - 2) + b;
	default:
		return 0;
	}
}

bool Transition::isOutdated() {
	return GetTickCount64() > endTime;
}