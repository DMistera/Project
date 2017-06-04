#include "Sprite.h"

#include "Game.h"
#include "System.h"

Sprite::Sprite(Texture * texture, Shader * shader, Model * model) {
	position = Vector();
	this->texture = texture;
	this->shader = shader;
	this->model = model;
	color = Vector(1.0f, 1.0f, 1.0f);
	alpha = 1.0f;
}

bool Sprite::initialize(Direct3D* direct3D, HWND* hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) {
	if (!initializeShader(loadedShaders, direct3D, hwnd))
		return false;
	if (!initializeModel(loadedModels, direct3D, hwnd))
		return false;
	if (!initializeTexture(loadedTextures, direct3D, hwnd))
		return false;
	return true;
}

bool Sprite::render(Direct3D* direct3D, HWND* hwnd, Camera* camera) {
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	model->render(direct3D->getDeviceContext());

	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix = camera->getViewMatrix();
	D3DXMATRIX orthographicMatrix;
	direct3D->getWorldMatrix(worldMatrix);
	direct3D->getOrthographicMatrix(orthographicMatrix);

	worldMatrix._41 = position.getX();
	worldMatrix._42 = position.getY();
	worldMatrix._43 = position.getZ();

	D3DXVECTOR3 d3color = D3DXVECTOR3(color.getX(), color.getY(), color.getZ());

	// Render the model using the color shader.
	if (!(shader->render(*hwnd, direct3D->getDeviceContext(), model->getIndexCount(), worldMatrix, viewMatrix, orthographicMatrix, texture->getResourceView(), d3color, alpha)))
		return false;

	return true;
}

void Sprite::shutdown() {
}

Vector Sprite::getPosiiton() {
	return position;
}

void Sprite::setPosition(Vector v) {
	position = v;
}

void Sprite::setColor(Vector v) {
	color = v;
}

void Sprite::setAlpha(float v) {
	alpha = v;
}

bool Sprite::initializeTexture(list<Texture*>* loadedTextures, Direct3D* direct3D, HWND* hwnd) {
	bool unique = true;
	for (Texture* &t : *loadedTextures) {
		if (t->getFileName() == texture->getFileName()) {
			texture->shutdown();
			delete texture;
			texture = t;
			unique = false;
		}
	}
	if (unique)
		loadedTextures->push_back(texture);
	if (!(texture->initialize(direct3D->getDevice(), hwnd))) {
		MessageBox(*hwnd, "Could not initialize texture", "Error", NULL);
		return false;
	}
	return true;
}

bool Sprite::initializeShader(list<Shader*>* loadedShaders, Direct3D* direct3D, HWND* hwnd) {
	bool unique = true;
	for (Shader* &s : *loadedShaders) {
		if (typeid(s) == typeid(shader)) {
			shader->shutdown();
			delete shader;
			shader = s;
			unique = false;
		}
	}
	if(unique)
		loadedShaders->push_back(shader);
	if (!(shader->initialize(direct3D->getDevice(), hwnd))) {
		MessageBox(*hwnd, "Could not initialize shader", "Error", NULL);
		return false;
	}
	return true;
}

bool Sprite::initializeModel(list<Model*>*, Direct3D* direct3D, HWND* hwnd) {
	if (!(model->initialize(direct3D->getDevice(), hwnd))) {
		MessageBox(*hwnd, "Could not initialize model", "Error", NULL);
		return false;
	}
	return true;
}
