#include "Direct3D.h"

Direct3D::Direct3D() {
	swapChain = 0;
	device = 0;
	deviceContext = 0;
	renderTargetView = 0;
	depthStencilBuffer = 0;
	depthStencilState = 0;
	depthStencilView = 0;
	rasterizerState = 0;
	alphaEnableBlendingState = 0;
	alphaDisableBlendingState = 0;
}

Direct3D::~Direct3D() {
}

bool Direct3D::initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullScreen, float screenDepth, float screenNear) {
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes, numerator = 0, denominator = 1, stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDescription;
	DXGI_SWAP_CHAIN_DESC swapChainDescription;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Texture2D* backBuffer;
	D3D11_TEXTURE2D_DESC depthBufferDescription;
	D3D11_DEPTH_STENCIL_DESC depthStencilDescription;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDescription;
	D3D11_RASTERIZER_DESC rasterizerDescription;
	D3D11_VIEWPORT viewport;
	float fieldOfView, screenAspect;
	vsyncEnabled = vsync;
	//Creating a factory (dunno why factory)
	if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
		return false;
	//Get adapter (video card)
	if (FAILED(factory->EnumAdapters(0, &adapter)))
		return false;
	//Get primary output (monitor)
	if (FAILED(adapter->EnumOutputs(0, &adapterOutput)))
		return false;
	//Get number of modes
	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8X8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL)))
		return false;
	//Get list of possible modes
	if (!(displayModeList = new DXGI_MODE_DESC[numModes]))
		return false;
	//Filling display mode list
	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8X8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList)))
		return false;
	for (unsigned int i = 0; i < numModes; i++) {
		if (displayModeList[i].Width == (unsigned int)screenWidth) {
			if (displayModeList[i].Height == (unsigned int)screenHeight) {
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}
	if (FAILED(adapter->GetDesc(&adapterDescription)))
		return false;
	videoCardMemory = (int)(adapterDescription.DedicatedVideoMemory / (1024 * 1024));
	if (wcstombs_s(&stringLength, videoCardDescription, 128, adapterDescription.Description, 120) != 0)
		return false;
	delete displayModeList;
	displayModeList = 0;
	adapterOutput->Release();
	adapterOutput = 0;
	adapter->Release();
	adapter = 0;
	factory->Release();
	factory = 0;
	ZeroMemory(&swapChainDescription, sizeof(swapChainDescription));
	swapChainDescription.BufferCount = 1;
	swapChainDescription.BufferDesc.Width = screenWidth;
	swapChainDescription.BufferDesc.Height = screenHeight;
	swapChainDescription.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	if (vsyncEnabled) {
		swapChainDescription.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDescription.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else {
		swapChainDescription.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
	}
	swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescription.OutputWindow = hwnd;
	swapChainDescription.SampleDesc.Count = 1;
	swapChainDescription.SampleDesc.Quality = 0;
	swapChainDescription.Windowed = !fullScreen;
	swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDescription.Flags = 0;
	featureLevel = D3D_FEATURE_LEVEL_11_0;
	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDescription, &swapChain, &device, NULL, &deviceContext)))
		return false;
	if (FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer)))
		return false;
	if (FAILED(device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView)))
		return false;
	backBuffer->Release();
	backBuffer = 0;
	ZeroMemory(&depthBufferDescription, sizeof(depthBufferDescription));
	depthBufferDescription.Height = screenHeight;
	depthBufferDescription.Width = screenWidth;
	depthBufferDescription.MipLevels = 1;
	depthBufferDescription.ArraySize = 1;
	depthBufferDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDescription.SampleDesc.Count = 1;
	depthBufferDescription.SampleDesc.Quality = 0;
	depthBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDescription.CPUAccessFlags = 0;
	depthBufferDescription.MiscFlags = 0;
	if (FAILED(device->CreateTexture2D(&depthBufferDescription, 0, &depthStencilBuffer)))
		return false;
	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDescription, sizeof(depthStencilDescription));

	// Stencil with Z buffer for 3D rendering
	/*depthStencilDescription.DepthEnable = true;
	depthStencilDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDescription.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDescription.StencilEnable = true;
	depthStencilDescription.StencilReadMask = 0xFF;
	depthStencilDescription.StencilWriteMask = 0xFF;
	// Stencil operations if pixel is front-facing.
	depthStencilDescription.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDescription.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDescription.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDescription.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	// Stencil operations if pixel is back-facing.
	depthStencilDescription.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDescription.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDescription.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDescription.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;	 */

	depthStencilDescription.DepthEnable = false;
	depthStencilDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDescription.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDescription.StencilEnable = true;
	depthStencilDescription.StencilReadMask = 0xFF;
	depthStencilDescription.StencilWriteMask = 0xFF;
	depthStencilDescription.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDescription.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDescription.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDescription.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDescription.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDescription.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDescription.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDescription.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	if (FAILED(device->CreateDepthStencilState(&depthStencilDescription, &depthStencilState)))
		return false;
	deviceContext->OMSetDepthStencilState(depthStencilState, 1);
	ZeroMemory(&depthStencilViewDescription, sizeof(depthStencilViewDescription));
	depthStencilViewDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDescription.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDescription.Texture2D.MipSlice = 0;
	if (FAILED(device->CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDescription, &depthStencilView)))
		return false;
	deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
	rasterizerDescription.AntialiasedLineEnable = false;
	rasterizerDescription.CullMode = D3D11_CULL_BACK;
	rasterizerDescription.DepthBias = 0;
	rasterizerDescription.DepthBiasClamp = 0.0f;
	rasterizerDescription.DepthClipEnable = true;
	rasterizerDescription.FillMode = D3D11_FILL_SOLID;
	rasterizerDescription.FrontCounterClockwise = false;
	rasterizerDescription.MultisampleEnable = false;
	rasterizerDescription.ScissorEnable = false;
	rasterizerDescription.SlopeScaledDepthBias = 0.0f;
	if (FAILED(device->CreateRasterizerState(&rasterizerDescription, &rasterizerState)))
		return false;
	deviceContext->RSSetState(rasterizerState);
	viewport.Width = (float)screenWidth;
	viewport.Height = (float)screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	deviceContext->RSSetViewports(1, &viewport);
	fieldOfView = D3DX_PI / 4.0f;
	screenAspect = (float)screenWidth / (float)screenHeight;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);
	D3DXMatrixIdentity(&worldMatrix);
	D3DXMatrixOrthoLH(&orthographicMatrix, (float)screenWidth, (float)screenHeight, screenNear, screenDepth);

	D3D11_BLEND_DESC blendStateDescription;
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));
	// Create an alpha enabled blend state description.
	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	//blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;
	if (FAILED(device->CreateBlendState(&blendStateDescription, &alphaEnableBlendingState)))
		return false;
	// Modify the description to create an alpha disabled blend state description.
	blendStateDescription.RenderTarget[0].BlendEnable = FALSE;
	if (FAILED(device->CreateBlendState(&blendStateDescription, &alphaDisableBlendingState)))
		return false;
	enableAlphaBlending();
	return true;
}

void Direct3D::shutdown() {
	if (swapChain)
		swapChain->SetFullscreenState(false, NULL);
	if (rasterizerState) {
		rasterizerState->Release();
		rasterizerState = 0;
	}
	if (depthStencilView) {
		depthStencilView->Release();
		depthStencilView = 0;
	}
	if (depthStencilState) {
		depthStencilState->Release();
		depthStencilState = 0;
	}
	if (depthStencilBuffer) {
		depthStencilBuffer->Release();
		depthStencilBuffer = 0;
	}
	if (renderTargetView) {
		renderTargetView->Release();
		renderTargetView = 0;
	}
	if (deviceContext) {
		deviceContext->Release();
		deviceContext = 0;
	}
	if (device) {
		device->Release();
		device = 0;
	}
	if (swapChain) {
		swapChain->Release();
		swapChain = 0;
	}
	if (alphaEnableBlendingState) {
		alphaEnableBlendingState->Release();
		alphaEnableBlendingState = 0;
	}
	if (alphaDisableBlendingState) {
		alphaDisableBlendingState->Release();
		alphaDisableBlendingState = 0;
	}
}

void Direct3D::beginScene(float red, float green, float blue, float alpha) {
	float color[] = { red, green, blue, alpha };
	deviceContext->ClearRenderTargetView(renderTargetView, color);
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Direct3D::endScene() {
	if (vsyncEnabled)
		swapChain->Present(1, 0);
	else
		swapChain->Present(0, 0);
}

void Direct3D::enableAlphaBlending() {
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	deviceContext->OMSetBlendState(alphaEnableBlendingState, blendFactor, 0xffffffff);
}

void Direct3D::disableAlphaBlending() {
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	deviceContext->OMSetBlendState(alphaDisableBlendingState, blendFactor, 0xffffffff);
}

ID3D11Device * Direct3D::getDevice() {
	return device;
}

ID3D11DeviceContext * Direct3D::getDeviceContext() {
	return deviceContext;
}

void Direct3D::getProjectionMatrix(D3DXMATRIX& matrix) {
	matrix = projectionMatrix;
}

void Direct3D::getWorldMatrix(D3DXMATRIX& matrix) {
	matrix = worldMatrix;
}

void Direct3D::getOrthographicMatrix(D3DXMATRIX& matrix) {
	matrix = orthographicMatrix;
}

void Direct3D::getVideoCardInfo(char * cardName, int & memory) {
	strcpy_s(cardName, 128, videoCardDescription);
	memory = videoCardMemory;
}
