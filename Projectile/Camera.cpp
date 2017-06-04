#include "Camera.h"

Camera::Camera() {
	position = new Vector();
	rotation = new Vector();
}

Camera::~Camera() {
}

void Camera::setPosition(Vector v) {
	*position = v;
}

void Camera::setRotation(Vector v) {
	*rotation = v;
}

void Camera::move(Vector v) {
	position->setX(position->getX() + v.getX());
	position->setY(position->getY() + v.getY());
	position->setZ(position->getZ() + v.getZ());
}

D3DXVECTOR3 Camera::getPosition() {
	return D3DXVECTOR3(position->getX(), position->getY(), position->getZ());
}

D3DXVECTOR3 Camera::getRotation() {
	return D3DXVECTOR3(rotation->getX(), rotation->getY(), rotation->getZ());
}

void Camera::render() {
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = this->position->getX();
	position.y = this->position->getY();
	position.z = this->position->getZ();

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = rotation->getX() * 0.0174532925f;
	yaw = rotation->getY() * 0.0174532925f;
	roll = rotation->getZ() * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&viewMatrix, &position, &lookAt, &up);

}

D3DXMATRIX& Camera::getViewMatrix() {
	return viewMatrix;
}
