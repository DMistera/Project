#include "Graphics.h"

#include "System.h"

Graphics::Graphics() {
	direct3D = 0;
}

Graphics::~Graphics() {
}

bool Graphics::initialize(System* systemP) {
	HWND* hwnd = systemP->getHWND();
	direct3D = new Direct3D();
	if (!direct3D)
		return false;
	if (!(direct3D->initialize(systemP->getScreenWidth(), systemP->getScreenHeight(), true, *hwnd, systemP->getFullScreen(), 1.0f, -1.0f))) {
		MessageBox(*hwnd, "Could not initialize DirectX", "Error", NULL);
		return false;
	}
	return true;
}

void Graphics::shutdown() {
	if (direct3D) {
		direct3D->shutdown();
		delete direct3D;
		direct3D = 0;
	}
}

Direct3D * Graphics::getDirect3D() {
	return direct3D;
}
