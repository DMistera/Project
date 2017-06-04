#include "Vector.h"

Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector::getX() {
	return x;
}

float Vector::getY() {
	return y;
}

float Vector::getZ() {
	return z;
}

void Vector::setX(float value) {
	x = value;
}

void Vector::setY(float value) {
	y = value;
}

void Vector::setZ(float value) {
	z = value;
}
