#include "ColorShader.h"

bool ColorShader::createSamplerState(ID3D11Device * device) {
	return true;
}

void ColorShader::getInputElements(D3D11_INPUT_ELEMENT_DESC* inputElements) {
	inputElements[0].SemanticName = "POSITION";
	inputElements[0].SemanticIndex = 0;
	inputElements[0].InstanceDataStepRate = 0;
	inputElements[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	inputElements[0].InputSlot = 0;
	inputElements[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElements[0].AlignedByteOffset = 0;

	inputElements[1].SemanticName = "COLOR";
	inputElements[1].SemanticIndex = 0;
	inputElements[1].InstanceDataStepRate = 0;
	inputElements[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	inputElements[1].InputSlot = 0;
	inputElements[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElements[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
}

LPCSTR ColorShader::getVertexShaderFilePath() {
	return "Resources/Shaders/Color.vs";
}

LPCSTR ColorShader::getPixelShaderFilePath() {
	return "Resources/Shaders/Color.ps";
}
