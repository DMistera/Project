#pragma once

#include "D3DX\d3dx10math.h"
#include "Vector.h"

class Camera {
public:
	Camera();
	~Camera();
	void setPosition(Vector v);
	void setRotation(Vector v);
	void move(Vector v);
	D3DXVECTOR3 getPosition();
	D3DXVECTOR3 getRotation();	
	void render();
	D3DXMATRIX& getViewMatrix();
private:
	Vector* position;
	Vector* rotation;
	D3DXMATRIX viewMatrix;
};