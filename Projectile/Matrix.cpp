#include "Matrix.h"

Matrix::Matrix(int width, int height) {
	elements = new float[width*height];
	this->width = width;
	this->height = height;
}

Matrix::~Matrix() {
	delete[] elements;
}

int Matrix::getWidth() {
	return width;
}

int Matrix::getHeight() {
	return height;
}

Matrix Matrix::createIdentityMatrix(int sideLength) {
	Matrix* result = new Matrix(sideLength, sideLength);

}
