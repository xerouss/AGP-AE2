// *********************************************************
//	Name:			Stephen Wong
//	File:			Skybox.cpp
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Skybox.h"

#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////
// Structure for the constant buffer
//////////////////////////////////////////////////////////////////////////////////////
struct SKYBOX_CONSTANT_BUFFER
{
	XMMATRIX worldViewProjection; // 64
	// TOTAL: 64 bytes
};

//####################################################################################
// Constructor
//####################################################################################
Skybox::Skybox(float scale, ID3D11Device* device, ID3D11DeviceContext* immediateContext):
	BasicModel(device, immediateContext)
{
	// Call the basic model constructor

	m_scale = scale;
}

//####################################################################################
// Destructor
//####################################################################################
Skybox::~Skybox()
{
	if (m_pRasterSolid != 0)
	{
		m_pRasterSolid->Release();
		m_pRasterSolid = NULL;
	}

	if (m_pRasterSkybox != 0)
	{
		m_pRasterSkybox->Release();
		m_pRasterSkybox = NULL;
	}

	if (m_pDepthWriteSolid != 0)
	{
		m_pDepthWriteSolid->Release();
		m_pDepthWriteSolid = NULL;
	}

	if (m_pDepthWriteSkybox != 0)
	{
		m_pDepthWriteSkybox->Release();
		m_pDepthWriteSkybox = NULL;
	}
}

//####################################################################################
// Set up the skybox
//####################################################################################
HRESULT Skybox::InitialiseSkybox(void)
{
	HRESULT hr = S_OK;

	// Create the default rasterizer
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

	// Set default values
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.FrontCounterClockwise = FALSE;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.DepthClipEnable = true;
	rasterizerDesc.ScissorEnable = false;
	rasterizerDesc.MultisampleEnable = false;
	rasterizerDesc.AntialiasedLineEnable = false;

	// Save the default state
	hr = m_pD3DDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterSolid);
	if (FAILED(hr)) return hr;

	// Set the culling to front since we don't need to render the front of the box just back
	// Save the changed state
	rasterizerDesc.CullMode = D3D11_CULL_FRONT;
	hr = m_pD3DDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterSkybox);
	if (FAILED(hr)) return hr;

	// Create depth stencil
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set default values
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = false;
	depthStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depthStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;

	// Save the default depth stencil
	hr = m_pD3DDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthWriteSolid);
	if (FAILED(hr)) return hr;

	// Change depth write mask to allow depth not to be rendered
	// Save the changed depth stencil
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	hr = m_pD3DDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthWriteSkybox);
	if (FAILED(hr)) return hr;

	return hr;
}

//####################################################################################
// Create constant buffer
//####################################################################################
HRESULT Skybox::CreateConstantBuffer()
{
	HRESULT hr = S_OK;

	// Create the constant buffer using the buffer structure size
	hr = BasicModel::CreateConstantBuffer(sizeof(SKYBOX_CONSTANT_BUFFER));

	return hr;
}

//####################################################################################
// Render the skybox in the game
//####################################################################################
void Skybox::Draw(XMMATRIX * world, XMMATRIX * view, XMMATRIX * projection)
{
	// Enable the front face culling
	m_pImmediateContext->RSSetState(m_pRasterSkybox);
	// Remove the depth rendering
	m_pImmediateContext->OMSetDepthStencilState(m_pDepthWriteSkybox, 1);

	// Draw the sky box
	BasicModel::Draw(world, view, projection);

	// Enable depth rendering
	m_pImmediateContext->OMSetDepthStencilState(m_pDepthWriteSolid, 1);
	// Revert back to the back face culling since the rest of the objects use it
	m_pImmediateContext->RSSetState(m_pRasterSolid);
}

//####################################################################################
// Set the constant buffer values
//####################################################################################
void Skybox::SetConstantBufferValues(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection)
{
	// Set the world view projection to the constant buffer
	SKYBOX_CONSTANT_BUFFER skyboxConstantBufferValues;
	// Have to put the view and projection in brackets to dereference the pointer
	skyboxConstantBufferValues.worldViewProjection = (*world) * (*view) * (*projection);

	// Update constant buffer
	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, 0, &skyboxConstantBufferValues, 0, 0);

	// Set active constant buffer for the vertex shader
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	// Set active constant buffer for the pixel shader
	m_pImmediateContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
}

//####################################################################################
// Get scale
//####################################################################################
float Skybox::GetScale(void)
{
	return m_scale;
}
