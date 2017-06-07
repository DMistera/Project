#include "Game.h"


Game::Game(System * systemP) {
	states = new list<State*>;
	this->systemP = systemP;
	this->hwnd = systemP->getHWND();
}

bool Game::initialize(int screenWidth, int screenHeight, bool fullScreen) {
	graphics = new Graphics();
	if (!graphics) {
		MessageBox(*hwnd, "Failed to create graphics object", "Error", NULL);
		return false;
	}
	if (!(graphics->initialize(systemP))) {
		MessageBox(*hwnd, "Failed to initialize graphics object", "Error", NULL);
		return false;
	}
	input = new Input();
	if (!input) {
		MessageBox(*hwnd, "Failed to create input object", "Error", NULL);
		return false;
	}
	if (!(input->initialize(systemP))) {
		MessageBox(*hwnd, "Failed to initialize direct input", "Error", NULL);
		return false;
	}
	Playground* playground = new Playground(this, systemP);	
	addState(playground);
	Cursor* cursor = new Cursor(this, systemP);	   
	addState(cursor);
	return true;
}

bool Game::addState(State* state) {
	if (!state->initialize())
		return false;
	states->push_back(state);
	return true;
}

bool Game::update(long deltaTime) {
	if (!input->frame())
		return false;
	if (input->isKeyDown(DIK_ESCAPE))
		return false;
	for (State* &state : *states) {
		if (!state->updateObjects(deltaTime))
			return false;
		if (!(state->update(deltaTime)))
			return false;
	}
	return true;
}

bool Game::render() {
	graphics->getDirect3D()->beginScene(0.8f, 0.4f, 0.3f, 1.0f);
	for (State* &state : *states) {
		if (!(state->render()))
			return false;
	}
	graphics->getDirect3D()->endScene();
	return true;
}

void Game::shutdown() {
}

Graphics * Game::getGraphics() {
	return graphics;
}

Input * Game::getInput() {
	return input;
}
