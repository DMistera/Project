#include "TextureShader.h"

bool TextureShader::createSamplerState(ID3D11Device * device) {
	D3D11_SAMPLER_DESC samplerDescription;
	samplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescription.MipLODBias = 0.0f;
	samplerDescription.MaxAnisotropy = 1;
	samplerDescription.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDescription.BorderColor[0] = 0;
	samplerDescription.BorderColor[1] = 0;
	samplerDescription.BorderColor[2] = 0;
	samplerDescription.BorderColor[3] = 0;
	samplerDescription.MinLOD = 0;
	samplerDescription.MaxLOD = D3D11_FLOAT32_MAX;
	return !(FAILED(device->CreateSamplerState(&samplerDescription, &samplerState)));
}

void TextureShader::getInputElements(D3D11_INPUT_ELEMENT_DESC* inputElements) {

	inputElements[0].SemanticName = "POSITION";
	inputElements[0].SemanticIndex = 0;
	inputElements[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputElements[0].InputSlot = 0;
	inputElements[0].AlignedByteOffset = 0;
	inputElements[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	inputElements[0].InstanceDataStepRate = 0;

	inputElements[1].SemanticName = "TEXCOORD";
	inputElements[1].SemanticIndex = 0;
	inputElements[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElements[1].InputSlot = 0;
	inputElements[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	inputElements[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	inputElements[1].InstanceDataStepRate = 0;
}

LPCSTR TextureShader::getVertexShaderFilePath() {
	return "Resources/Shaders/Texture.vs";
}

LPCSTR TextureShader::getPixelShaderFilePath() {
	return "Resources/Shaders/Texture.ps";
}
