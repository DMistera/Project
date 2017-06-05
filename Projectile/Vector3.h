#pragma once

class Vector3 {
public:
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	float getX();
	float getY();
	float getZ();
	void setX(float value);
	void setY(float value);
	void setZ(float value);
private:
	float x;
	float y;
	float z;
};