#pragma once

class Matrix {
private:
	float* elements;
	int width;
	int height;
public:
	Matrix(int width, int height);
	~Matrix();
	int getWidth();
	int getHeight();
	static Matrix createIdentityMatrix();
};