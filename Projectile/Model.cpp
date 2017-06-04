#include "Model.h"

Model::Model() {
	vertexBuffer = 0;
	indexBuffer = 0;
	verticesT = 0;
	verticesC = 0;
	indices = 0;
	hwnd = 0;
}

Model::Model(D3DXVECTOR3 positions[], unsigned long indices[], D3DXVECTOR2 textureCoordinates[], int vertexCount, int indexCount) : Model() {
	hasTexture = true;
	this->vertexCount = vertexCount;
	verticesT = new VertexT[vertexCount];
	for (int i = 0; i < vertexCount; i++) {
		verticesT[i].position = positions[i];
		verticesT[i].texture = textureCoordinates[i];
	}
	this->indexCount = indexCount;
	this->indices = new unsigned long[indexCount];
	for (int i = 0; i < indexCount; i++) {
		this->indices[i] = indices[i];	
	}
}

Model::Model(D3DXVECTOR3 positions[], unsigned long indices[], D3DXVECTOR4 color[], int vertexCount, int indexCount) : Model() {
	hasTexture = false;
	this->vertexCount = vertexCount;
	verticesC = new VertexC[vertexCount];
	for (int i = 0; i < vertexCount; i++) {
		verticesC[i].position = positions[i];
		verticesC[i].color = color[i];
	}
	this->indexCount = indexCount;
	this->indices = new unsigned long[indexCount];
	for (int i = 0; i < indexCount; i++) {
		this->indices[i] = indices[i];
	}
}

Model::~Model() {
}

bool Model::initialize(ID3D11Device* device, HWND* hwnd) {
	this->hwnd = hwnd;
	if (!(initializeBuffers(device)))
		return false;
	return true;
}

void Model::render(ID3D11DeviceContext * deviceContext) {
	renderBuffers(deviceContext);
}

bool Model::initializeBuffers(ID3D11Device* device) {

	D3D11_BUFFER_DESC vertexBufferDescription;
	vertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	if(hasTexture)
		vertexBufferDescription.ByteWidth = sizeof(VertexT) * vertexCount;
	else
		vertexBufferDescription.ByteWidth = sizeof(VertexC) * vertexCount;
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescription.CPUAccessFlags = 0;
	vertexBufferDescription.MiscFlags = 0;
	vertexBufferDescription.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	if(hasTexture)
		vertexData.pSysMem = verticesT;
	else
		vertexData.pSysMem = verticesC;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	if (FAILED(device->CreateBuffer(&vertexBufferDescription, &vertexData, &vertexBuffer))) {
		MessageBox(*hwnd, "Failed to create vertex buffer", "Error", NULL);
		return false;
	}
	D3D11_BUFFER_DESC indexBufferDescription;
	indexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDescription.ByteWidth = sizeof(unsigned long) * indexCount;
	indexBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDescription.CPUAccessFlags = 0;
	indexBufferDescription.MiscFlags = 0;
	indexBufferDescription.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	if (FAILED(device->CreateBuffer(&indexBufferDescription, &indexData, &indexBuffer))) {
		MessageBox(*hwnd, "Failed to create index buffer", "Error", NULL);
		return false;
	}
	return true;
}

void Model::shutdown() {
	shutdownBuffers();
}

int Model::getIndexCount() {
	return indexCount;
}

void Model::shutdownBuffers() {
	if (vertexBuffer) {
		vertexBuffer->Release();
		vertexBuffer = 0;
	}
	if (indexBuffer) {
		indexBuffer->Release();
		indexBuffer = 0;
	}
}

void Model::renderBuffers(ID3D11DeviceContext* deviceContext) {
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	if(hasTexture)
		stride = sizeof(VertexT);
	else
		stride = sizeof(VertexC);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}