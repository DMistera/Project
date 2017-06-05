#include "Sprite.h"

#include "Game.h"
#include "System.h"

Sprite::Sprite(Texture * texture, Shader * shader, Model * model) {
	position = Vector();
	this->texture = texture;
	this->shader = shader;
	this->model = model;
	colorVector = Vector(1.0f, 1.0f, 1.0f);
	scaleVector = Vector(1.0f, 1.0f);
	alpha = 1.0f;
	transitions = new list<Transition*>;
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

	//Set position
	worldMatrix._41 = position.getX();
	worldMatrix._42 = position.getY();
	worldMatrix._43 = position.getZ();

	//Set scale
	worldMatrix._11 = scaleVector.getX();
	worldMatrix._22 = scaleVector.getY();

	D3DXVECTOR3 d3color = D3DXVECTOR3(colorVector.getX(), colorVector.getY(), colorVector.getZ());

	// Render the model using the color shader.
	if (!(shader->render(*hwnd, direct3D->getDeviceContext(), model->getIndexCount(), worldMatrix, viewMatrix, orthographicMatrix, texture->getResourceView(), d3color, alpha)))
		return false;

	return true;
}

void Sprite::shutdown() {
}

Vector Sprite::getPosition() {
	return position;
}

void Sprite::setPosition(Vector v) {
	position = v;
}

//Setters

void Sprite::setX(float v) {
	position.setX(v);
}

void Sprite::setY(float v) {
	position.setY(v);
}

void Sprite::setWidthScale(float v) {
	scaleVector.setX(v);
}

void Sprite::setHeightScale(float v) {
	scaleVector.setY(v);
}

void Sprite::setColor(Vector v) {
	colorVector = v;
}

void Sprite::setAlpha(float v) {
	alpha = v;
}

void Sprite::setScale(Vector v) {
	scaleVector = v;
}

//Transitions

void Sprite::moveX(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::MOVE_X, easing, startTime, endTime, startValue, endValue));
}

void Sprite::moveY(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::MOVE_Y, easing, startTime, endTime, startValue, endValue));
}

void Sprite::move(Transition::Easing easing, unsigned long startTime, unsigned long endTime, Vector startValue, Vector endValue) {
	moveX(easing, startTime, endTime, startValue.getX(), endValue.getX());
	moveY(easing, startTime, endTime, startValue.getY(), endValue.getY());
}

void Sprite::scaleX(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::SCALE_X, easing, startTime, endTime, startValue, endValue));
}

void Sprite::scaleY(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::SCALE_Y, easing, startTime, endTime, startValue, endValue));
}

void Sprite::scale(Transition::Easing easing, unsigned long startTime, unsigned long endTime, Vector startValue, Vector endValue) {
	scaleX(easing, startTime, endTime, startValue.getX(), endValue.getX());
	scaleY(easing, startTime, endTime, startValue.getY(), endValue.getY());
}

void Sprite::fade(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::FADE, easing, startTime, endTime, startValue, endValue));
}

void Sprite::red(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::COLOR_RED, easing, startTime, endTime, startValue, endValue));
}

void Sprite::green(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::COLOR_GREEN, easing, startTime, endTime, startValue, endValue));
}

void Sprite::blue(Transition::Easing easing, unsigned long startTime, unsigned long endTime, float startValue, float endValue) {
	transitions->push_back(new Transition(this, Transition::Type::COLOR_BLUE, easing, startTime, endTime, startValue, endValue));
}

void Sprite::color(Transition::Easing easing, unsigned long startTime, unsigned long endTime, Vector startValue, Vector endValue) {
	red(easing, startTime, endTime, startValue.getX(), endValue.getX());
	green(easing, startTime, endTime, startValue.getY(), endValue.getY());
	blue(easing, startTime, endTime, startValue.getZ(), endValue.getZ());
}

void Sprite::updateTransitions() {
	list<Transition*>::iterator transition = transitions->begin();
	while (transition != transitions->end()) {
		if ((*transition)->isOutdated()) {
			delete (*transition);
			transitions->erase(transition++);
		}
		else {
			(*transition)->update();
			++transition;
		}
	}
}

//Initialization

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

bool Sprite::update() {
	 updateTransitions();
	 return true;
}
