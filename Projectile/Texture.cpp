#include "Texture.h"

Texture::Texture(LPCSTR fileName) {
	resourceView = 0;
	this->fileName = fileName;
}

Texture::~Texture() {
}

bool Texture::initialize(ID3D11Device * device, HWND* hwnd) {
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(device, fileName, NULL, NULL, &resourceView, NULL))) {
		MessageBox(*hwnd, "Missing texture file!", "Error", NULL);
		return false;
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
