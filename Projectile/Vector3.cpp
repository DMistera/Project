#include "Vector3.h"

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3::getX() {
	return x;
}

float Vector3::getY() {
	return y;
}

float Vector3::getZ() {
	return z;
}

void Vector3::setX(float value) {
	x = value;
}

void Vector3::setY(float value) {
	y = value;
}

void Vector3::setZ(float value) {
	z = value;
}
