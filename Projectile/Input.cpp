#include "Input.h"

#include "System.h"

Input::Input() {
	directInput = 0;
	keyboard = 0;
	mouse = 0;
}

Input::~Input() {
}

bool Input::initialize(System* systemP) {
	this->screenWidth = systemP->getScreenWidth();
	this->screenHeight = systemP->getScreenHeight();
	mouseX = 0;
	mouseY = 0;
	HINSTANCE* instance = systemP->getInstance();
	HWND* hwnd = systemP->getHWND();
	if (FAILED(DirectInput8Create(*instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL)))
		return false;
	if (FAILED(directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL)))
		return false;
	if (FAILED(keyboard->SetDataFormat(&c_dfDIKeyboard)))
		return false;
	if (FAILED(keyboard->SetCooperativeLevel(*hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
		return false;
	if (FAILED(keyboard->Acquire()))
		return false;
	if (FAILED(directInput->CreateDevice(GUID_SysMouse, &mouse, NULL)))
		return false;
	if (FAILED(mouse->SetDataFormat(&c_dfDIMouse)))
		return false;
	if (FAILED(mouse->SetCooperativeLevel(*hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
		return false;
	if (FAILED(mouse->Acquire()))
		return false;
	return true;
}

void Input::shutdown() {

}

bool Input::frame() {
	if (!readKeyboard())
		return false;
	if (!readMouse())
		return false;
	processInput();
	return true;
}

bool Input::readKeyboard() {
	// Read the keyboard device.
	HRESULT result = keyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
	if (FAILED(result)) {
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) {
			keyboard->Acquire();
		}
		else {
			return false;
		}
	}

	return true;
}

bool Input::readMouse() {
	// Read the mouse device.
	HRESULT result = mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);
	if (FAILED(result)) {
		// If the mouse lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) {
			mouse->Acquire();
		}
		else {
			return false;
		}
	}

	return true;

}

void Input::processInput() {
	mouseX += mouseState.lX;
	mouseY += mouseState.lY;
	if (mouseX < 0)
		mouseX = 0;
	if (mouseY < 0)
		mouseY = 0;
	if (mouseX > screenWidth)
		mouseX = screenWidth;
	if (mouseY > screenHeight)
		mouseY = screenHeight;
}

bool Input::isKeyDown(unsigned int key) {
	return (keyboardState[key] & 0x80);
}

bool Input::isKeyUp(unsigned int key) {
	return !(keyboardState[key] & 0x80);
}

Vector Input::getMousePosition() {
	return Vector(mouseX, mouseY);
}