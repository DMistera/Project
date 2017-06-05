#pragma once

#include <d3d11.h>
#include "D3DX\d3dx10math.h"
#include "Texture.h"

class Model {
public:
	Model(D3DXVECTOR3 positions[], unsigned long indices[], D3DXVECTOR2 textureCoordinates[], int vertexCount, int indexCount);
	Model(D3DXVECTOR3 positions[], unsigned long indices[], D3DXVECTOR4 color[], int vertexCount, int indexCount);
	~Model();
	bool initialize(ID3D11Device * device, HWND* hwnd);
	void render(ID3D11DeviceContext* deviceContext);
	void shutdown();
	int getIndexCount();
protected:
	Model();
	bool initializeBuffers(ID3D11Device * device);
	void shutdownBuffers();
	void renderBuffers(ID3D11DeviceContext* deviceContext);
	struct VertexT {
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};
	struct VertexC {
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};
	int vertexCount;
	int indexCount;
	VertexT* verticesT;
	VertexC* verticesC;
	unsigned long* indices;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* vertexBuffer;
	HWND* hwnd;
	bool hasTexture;
};