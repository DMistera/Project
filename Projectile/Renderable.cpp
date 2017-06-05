#include "Renderable.h"

Vector2 Renderable::getPosition() {
	return position;
}

//Setters


Renderable::Renderable() {
	position = Vector2();
	colorVector = Vector3(1.0f, 1.0f, 1.0f);
	scaleVector = Vector2(1.0f, 1.0f);
	alpha = 1.0f;
	rotation = 0.0f;
	transitions = new list<Transition*>;
}

bool Renderable::update() {
	updateTransitions();
	return updateComponent();
}

void Renderable::shutdown() {
	shutdownComponent();
	list<Transition*>::iterator transition = transitions->begin();
	while (transition != transitions->end()) {
		delete (*transition);
		transitions->erase(transition++);
	}
	delete transitions;
	transitions = 0;
}

void Renderable::setPosition(Vector2 v) {
	position = v;
}

void Renderable::setX(float v) {
	position.setX(v);
}

void Renderable::setY(float v) {
	position.setY(v);
}

void Renderable::setWidthScale(float v) {
	scaleVector.setX(v);
}

void Renderable::setHeightScale(float v) {
	scaleVector.setY(v);
}

void Renderable::setColor(Vector3 v) {
	colorVector = v;
}

void Renderable::setAlpha(float v) {
	alpha = v;
}

void Renderable::setScale(Vector2 v) {
	scaleVector = v;
}

//Transitions

void Renderable::moveX(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::MOVE_X, easing, startTime, endTime, startValue, endValue));
}

void Renderable::moveY(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::MOVE_Y, easing, startTime, endTime, startValue, endValue));
}

void Renderable::move(Transition::Easing easing, unsigned long startTime, unsigned long endTime, Vector3 startValue, Vector3 endValue) {
	moveX(easing, startTime, endTime, startValue.getX(), endValue.getX());
	moveY(easing, startTime, endTime, startValue.getY(), endValue.getY());
}

void Renderable::scaleX(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::SCALE_X, easing, startTime, endTime, startValue, endValue));
}

void Renderable::scaleY(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::SCALE_Y, easing, startTime, endTime, startValue, endValue));
}

void Renderable::scale(Transition::Easing easing, unsigned long startTime, unsigned long endTime, Vector3 startValue, Vector3 endValue) {
	scaleX(easing, startTime, endTime, startValue.getX(), endValue.getX());
	scaleY(easing, startTime, endTime, startValue.getY(), endValue.getY());
}

void Renderable::fade(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::FADE, easing, startTime, endTime, startValue, endValue));
}

void Renderable::red(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::COLOR_RED, easing, startTime, endTime, startValue, endValue));
}

void Renderable::green(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::COLOR_GREEN, easing, startTime, endTime, startValue, endValue));
}

void Renderable::blue(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::COLOR_BLUE, easing, startTime, endTime, startValue, endValue));
}

void Renderable::color(Transition::Easing easing, unsigned long startTime, unsigned long endTime, Vector3 startValue, Vector3 endValue) {
	red(easing, startTime, endTime, startValue.getX(), endValue.getX());
	green(easing, startTime, endTime, startValue.getY(), endValue.getY());
	blue(easing, startTime, endTime, startValue.getZ(), endValue.getZ());
}

void Renderable::updateTransitions() {
	list<Transition*>::iterator transition = transitions->begin();
	while (transition != transitions->end()) {
		if ((*transition)->isOutdated()) {
			delete (*transition);
			transitions->erase(transition++);
		}
		else {
			(*transition)->update();
			++transition;
		}
	}
}

void Renderable::acquireParameters(Vector2 position, Vector2 scaleVector, Vector3 colorVector, float alpha, float rotation) {
	this->position = position;
	this->scaleVector = scaleVector;
	this->colorVector = colorVector;
	this->alpha = alpha;
	this->rotation = rotation;
}
