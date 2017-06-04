#pragma once

#include <d3d11.h>
#include "D3DX\d3dx10math.h"
#include "D3DX\d3dx11async.h"
#include <fstream>

using namespace std;

class Shader {
public:
	Shader();
	~Shader();
	bool initialize(ID3D11Device* device, HWND* hwnd);
	void shutdown();
	bool render(HWND, ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, D3DXVECTOR3 color, float alpha);
protected:
	struct MatrixBuffer {
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};
	struct ChannelBuffer {
		D3DXVECTOR3 color;
		float alpha;
	}; //TODO Implement this to sprite
	bool initializeShaders(ID3D11Device* device);
	void outputShaderError(ID3D10Blob* error, LPCSTR shaderFilename);
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* inputLayout;
	ID3D11Buffer* matrixBuffer;
	ID3D11Buffer* channelBuffer;
	bool setShaderParameters(HWND, ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* shaderResource, D3DXVECTOR3 color, float alpha);
	void shutdownShader();
	void renderShader(ID3D11DeviceContext*, int);
	virtual bool createSamplerState(ID3D11Device* device) = 0;
	virtual void getInputElements(D3D11_INPUT_ELEMENT_DESC*) = 0;
	virtual LPCSTR getVertexShaderFilePath() = 0;
	virtual LPCSTR getPixelShaderFilePath() = 0;
	HWND* hwnd;
	ID3D11SamplerState* samplerState;
};