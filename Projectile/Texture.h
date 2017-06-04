#pragma once

#include <d3d11.h>
#include "D3DX\d3dx11tex.h"
#include <string>

class Texture {
public:
	Texture(LPCSTR fileName);
	~Texture();
	bool initialize(ID3D11Device* device, HWND*);
	void shutdown();
	ID3D11ShaderResourceView* getResourceView();
	std::string getFileName();
private:
	LPCSTR fileName;
	ID3D11ShaderResourceView* resourceView;
};