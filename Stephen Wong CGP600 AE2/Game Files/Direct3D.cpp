// *********************************************************
//	Name:			Stephen Wong
//	File:			Direct3D.cpp
//	Last Updated:	30/11/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Direct3D.h"

#pragma endregion

//####################################################################################
// Destructor
//####################################################################################
Direct3D::~Direct3D()
{
	if (m_pBackBufferRenderTargetView) m_pBackBufferRenderTargetView->Release();
	if (m_pSwapChain) m_pSwapChain->Release();
	if (m_pImmediateContext) m_pImmediateContext->Release();
	if (m_pD3DDevice) m_pD3DDevice->Release();
}

//####################################################################################
// Create D3D device and swap chain
//####################################################################################
HRESULT Direct3D::InitialiseD3D(HWND hWindow)
{
	HRESULT hr = S_OK;

	// Get window dimensions
	RECT rc;
	GetClientRect(hWindow, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	// Create flag for debugging
	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// List of all driver types
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, // Comment out this line if you need to test D3D 11.0 functionality on hardware that doesn't support it
		D3D_DRIVER_TYPE_WARP, // Comment this out also to use reference device
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	// Get the device features
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0, // Direct 11 compatible hardware
		D3D_FEATURE_LEVEL_10_1, // Direct 10.1 " "
		D3D_FEATURE_LEVEL_10_0, // Direct 10.0 " "
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	// Create swap chain to render to
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWindow;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	// Go through driver types and try to create the swap chain on that device
	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, m_driverType, NULL,
			createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &m_pSwapChain,
			&m_pD3DDevice, &m_featureLevel, &m_pImmediateContext);

		if (SUCCEEDED(hr)) break;
	}

	if (FAILED(hr)) return hr;

	// Get pointer to back buffer texture
	ID3D11Texture2D *pBackBufferTexture;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(LPVOID*)&pBackBufferTexture);

	if (FAILED(hr)) return hr;


	// Use the back buffer texture pointer to create the render target view
	hr = m_pD3DDevice->CreateRenderTargetView(pBackBufferTexture, NULL,
		&m_pBackBufferRenderTargetView);
	pBackBufferTexture->Release();

	if (FAILED(hr)) return hr;

	// ZBUFFER
	/*
	g_descCount = sd.SampleDesc.Count;
	hr = CreateZBuffer(g_descCount, (UINT)width, (UINT)height, hr);*/

	if (FAILED(hr)) return hr;

	// Set the render target view
	// ADD ZBUFFER THING TO LAST PARAMATER
	m_pImmediateContext->OMSetRenderTargets(1, &m_pBackBufferRenderTargetView, NULL); //g_pZBuffer);

	// Set the viewport
	D3D11_VIEWPORT viewport;

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	// Cast these as floats to prevent type difference warnings
	viewport.Width = (FLOAT)width;
	viewport.Height = (FLOAT)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_pImmediateContext->RSSetViewports(1, &viewport);

	// FOR TEXT
	/*
	// Set up blend for transparency
	D3D11_BLEND_DESC blendDesc;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.AlphaToCoverageEnable = false;

	g_pD3DDevice->CreateBlendState(&blendDesc, &g_pAlphaBlendEnable);

	// Create the 2D text
	g_pText2D0 = new Text2D("Assets/font1.bmp", g_pD3DDevice, g_pImmediateContext);
	g_pText2D1 = new Text2D("Assets/fontTrans.png", g_pD3DDevice, g_pImmediateContext);*/

	return S_OK;
}

//####################################################################################
// Methods to get private variables
//####################################################################################
#pragma region Get Methods

ID3D11Device* Direct3D::GetD3DDevice(void)
{
	return m_pD3DDevice;
}

ID3D11RenderTargetView* Direct3D::GetBackBuffer(void)
{
	return m_pBackBufferRenderTargetView;
}

IDXGISwapChain* Direct3D::GetSwapChain(void)
{
	return m_pSwapChain;
}

ID3D11DeviceContext* Direct3D::GetImmediateContext(void)
{
	return m_pImmediateContext;
}

#pragma endregion
