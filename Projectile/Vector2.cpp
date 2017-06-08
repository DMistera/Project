#include "Vector2.h"

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

float Vector2::getX() {
	return x;
}

float Vector2::getY() {
	return y;
}

void Vector2::setX(float value) {
	x = value;
}

void Vector2::setY(float value) {
	y = value;
}

void Vector2::addX(float value) {
	x += value;
}

void Vector2::addY(float value) {
	y += value;
}

void Vector2::add(Vector2 v) {
	addX(v.getX());
	addY(v.getY());
}

