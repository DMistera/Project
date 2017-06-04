#pragma once

#include "Shader.h"

class TextureShader : public Shader {
protected:
	bool createSamplerState(ID3D11Device* device) override;
	void getInputElements(D3D11_INPUT_ELEMENT_DESC*) override;
	LPCSTR getVertexShaderFilePath() override;
	LPCSTR getPixelShaderFilePath() override;
};