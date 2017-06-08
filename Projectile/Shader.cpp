#include "Shader.h"

Shader::Shader() {
	vertexShader = 0;
	pixelShader = 0;
	inputLayout = 0;
	matrixBuffer = 0;
	hwnd = 0;
	initialized = false;
}

Shader::~Shader() {
}

bool Shader::initialize(ID3D11Device * device, HWND* hwnd) {
	this->hwnd = hwnd;
	return initializeShaders(device);
}

void Shader::shutdown() {
	shutdownShader();
}

bool Shader::render(HWND hwnd, ID3D11DeviceContext * deviceContent, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* shaderResource, D3DXVECTOR3 color, float alpha) {
	if (!(setShaderParameters(hwnd, deviceContent, worldMatrix, viewMatrix, projectionMatrix, shaderResource, color, alpha)))
		return false;
	renderShader(deviceContent, indexCount);
	return true;
}

bool Shader::isInitialized() {
	return initialized;
}

bool Shader::initializeShaders(ID3D11Device * device) {
	initialized = true;
	ID3D10Blob* errorMessage = 0;
	ID3D10Blob* vertexShaderBuffer = 0;
	ID3D10Blob* pixelShaderBuffer = 0;
	if (FAILED(D3DX11CompileFromFile(getVertexShaderFilePath(), NULL, NULL, "vsMain", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL))) {
		if (errorMessage)
			outputShaderError(errorMessage, getVertexShaderFilePath());
		else
			MessageBox(*hwnd, "Missing shader file", "Error", NULL);
		return false;
	}
	if (FAILED(D3DX11CompileFromFile(getPixelShaderFilePath(), NULL, NULL, "psMain", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL))) {
		if (errorMessage)
			outputShaderError(errorMessage, getPixelShaderFilePath());
		else
			MessageBox(*hwnd, "Missing shader file", "Error", NULL);
		return false;
	}
	if (FAILED(device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader))) {
		MessageBox(*hwnd, "Failed to create vertex shader", "Error", NULL);
		return false;
	}
	if (FAILED(device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader))) {
		MessageBox(*hwnd, "Failed to create pixel shader", "Error", NULL);
		return false;
	}
	const unsigned int numberOfElements = 2;
	D3D11_INPUT_ELEMENT_DESC inputElements[2];
	getInputElements(inputElements);
	if (FAILED(device->CreateInputLayout(inputElements, numberOfElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &inputLayout))) {
		MessageBox(*hwnd, "Failed to create input layout", "Error", NULL);
		return false;
	}
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;
	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;
	D3D11_BUFFER_DESC matrixBufferDescription;
	matrixBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDescription.ByteWidth = sizeof(MatrixBuffer);
	matrixBufferDescription.MiscFlags = 0;
	matrixBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDescription.StructureByteStride = 0;
	if (FAILED(device->CreateBuffer(&matrixBufferDescription, NULL, &matrixBuffer))) {
		MessageBox(*hwnd, "Failed to create matrix buffer", "Error", NULL);
		return false;
	}
	D3D11_BUFFER_DESC channelBufferDescription;
	channelBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	channelBufferDescription.ByteWidth = sizeof(ChannelBuffer);
	channelBufferDescription.MiscFlags = 0;
	channelBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	channelBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	channelBufferDescription.StructureByteStride = 0;
	if (FAILED(device->CreateBuffer(&channelBufferDescription, NULL, &channelBuffer))) {
		MessageBox(*hwnd, "Failed to create matrix buffer", "Error", NULL);
		return false;
	}

	if (!createSamplerState(device)) {
		MessageBox(*hwnd, "Failed to create sampler state", "Error", NULL);
		return false;
	}
	return true;
}

void Shader::outputShaderError(ID3D10Blob * error, LPCSTR shaderFilename) {
	LPCSTR errorMessage = (LPCSTR)error->GetBufferPointer();
	ofstream out;
	out.open("shaderError.txt");
	out << errorMessage;
	out.close();
	MessageBox(*hwnd, "Error compiling shader. Check shaderError.txt for more information", "Error", NULL);
}

bool Shader::setShaderParameters(HWND hwnd, ID3D11DeviceContext * deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* shaderResource, D3DXVECTOR3 color, float alpha) {
	if (!initialized) {
		MessageBox(hwnd, "Trying to access unitialized shader!", "Error", NULL);
		return false;
	}
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBuffer* data;
	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
	D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);
	if (FAILED(deviceContext->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource))) {
		MessageBox(hwnd, "Failed to map resources", "Error", NULL);
		return false;
	}
	data = (MatrixBuffer*)mappedResource.pData;
	data->projection = projectionMatrix;
	data->world = worldMatrix;
	data->view = viewMatrix;
	deviceContext->Unmap(matrixBuffer, 0);
	unsigned int bufferNumber = 0;
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &matrixBuffer);
	deviceContext->PSSetShaderResources(0, 1, &shaderResource);

	if (FAILED(deviceContext->Map(channelBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource))) {
		MessageBox(hwnd, "Failed to map resources", "Error", NULL);
		return false;
	}
	ChannelBuffer* data2 = (ChannelBuffer*)mappedResource.pData;
	data2->color = color;
	data2->alpha = alpha;
	deviceContext->Unmap(channelBuffer, 0);
	bufferNumber = 0;
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &channelBuffer);
	return true;
}

void Shader::shutdownShader() {
	if (matrixBuffer) {
		matrixBuffer->Release();
		matrixBuffer = 0;
	}
	if (vertexShader) {
		vertexShader->Release();
		vertexShader = 0;
	}
	if (pixelShader) {
		pixelShader->Release();
		pixelShader = 0;
	}
	if (inputLayout) {
		inputLayout->Release();
		inputLayout = 0;
	}
}

void Shader::renderShader(ID3D11DeviceContext * deviceContext, int indexCount) {
	// Set the vertex input layout.
	deviceContext->IASetInputLayout(inputLayout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(vertexShader, NULL, 0);
	deviceContext->PSSetShader(pixelShader, NULL, 0);

	// Render the triangle.
	deviceContext->DrawIndexed(indexCount, 0, 0);
}