#pragma once

#include "D3DX\d3dx10math.h"
#include "Vector3.h"

class Camera {
public:
	Camera();
	~Camera();
	void setPosition(Vector3 v);
	void setRotation(Vector3 v);
	void move(Vector3 v);
	D3DXVECTOR3 getPosition();
	D3DXVECTOR3 getRotation();	
	void render();
	D3DXMATRIX& getViewMatrix();
private:
	Vector3* position;
	Vector3* rotation;
	D3DXMATRIX viewMatrix;
};