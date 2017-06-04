#pragma once

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include "D3DX\d3dx10math.h"

class Direct3D {
public:
	Direct3D();
	~Direct3D();
	bool initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullScreen, float screenDepth, float screenNear);
	void shutdown();
	void beginScene(float red, float green, float blue, float alpha);
	void endScene();
	void enableAlphaBlending();
	void disableAlphaBlending();
	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	void getProjectionMatrix(D3DXMATRIX&);
	void getWorldMatrix(D3DXMATRIX&);
	void getOrthographicMatrix(D3DXMATRIX&);
	void getVideoCardInfo(char* cardName, int& memory);
private:
	bool vsyncEnabled;
	int videoCardMemory;
	char videoCardDescription[128];
	IDXGISwapChain* swapChain;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11RasterizerState* rasterizerState;
	D3DXMATRIX projectionMatrix;
	D3DXMATRIX worldMatrix;
	D3DXMATRIX orthographicMatrix;
	ID3D11BlendState* alphaEnableBlendingState;
	ID3D11BlendState* alphaDisableBlendingState;
};