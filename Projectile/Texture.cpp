#include "Texture.h"

Texture::Texture(LPCSTR fileName) {
	resourceView = 0;
	initialized = false;
	this->fileName = fileName;
}

Texture::~Texture() {
}

bool Texture::initialize(ID3D11Device * device, HWND* hwnd) {
	if (!initialized) {
		if (FAILED(D3DX11CreateShaderResourceViewFromFile(device, fileName, NULL, NULL, &resourceView, NULL))) {
			string message = "Missing texture file: " + string(fileName);
			MessageBox(*hwnd, message.c_str(), "Error", NULL);
			return false;
		}
		initialized = true;
	}
	return true;
}

void Texture::shutdown() {
	if (resourceView) {
		resourceView->Release();
		resourceView = 0;
	}
}

ID3D11ShaderResourceView * Texture::getResourceView() {
	return resourceView;
}

std::string Texture::getFileName() {
	return (char*)fileName;
}

bool Texture::isInitialized() {
	return initialized;
}
