#pragma once

class Vector2 {
public:
	Vector2(float x = 0.0f, float y = 0.0f);
	float getX();
	float getY();
	void setX(float value);
	void setY(float value);
private:
	float x;
	float y;
};