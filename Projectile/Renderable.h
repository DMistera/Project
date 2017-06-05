#pragma once

class Renderable {
public:
	virtual bool render(Direct3D* direct3D, HWND* hwnd, Camera* camera) = 0;
	virtual bool update() = 0;
	virtual bool initialize(Direct3D* direct3D, HWND* hwnd, list<Texture*>* loadedTextures, list<Shader*>* loadedShaders, list<Model*>* loadedModels) = 0;
};