// *********************************************************
//	Name:			Stephen Wong
//	File:			BasicModel.cpp
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "BasicModel.h"

#pragma endregion

//####################################################################################
// Constructor
//####################################################################################
BasicModel::BasicModel(ID3D11Device* device, ID3D11DeviceContext* immediateContext)
{
	m_pD3DDevice = device;
	m_pImmediateContext = immediateContext;
}

//####################################################################################
// Destructor
//####################################################################################
BasicModel::~BasicModel()
{
	// Don't delete m_pD3DDevice and m_pImmediateContext because
	// They are created else where

	if (m_pTexture0) m_pTexture0->Release();
	if (m_pSamplerState0) m_pSamplerState0->Release();
	if (m_pConstantBuffer) m_pConstantBuffer->Release();
	if (m_pInputLayer) m_pInputLayer->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
	if (m_pVertexShader) m_pVertexShader->Release();

	if (m_pObject)
	{
		delete m_pObject;
		m_pObject = NULL;
	}
}

//####################################################################################
// Load up the model from a file
//####################################################################################
int BasicModel::LoadObjectModel(char* filename)
{
	// Load up the object
	m_pObject = new ObjectFileModel(filename, m_pD3DDevice, m_pImmediateContext);

	// Check if the model was loaded correctly
	if (m_pObject->filename == "FILE NOT LOADED") return S_FALSE;

	return S_OK; // Object was loaded successfully
}

//####################################################################################
// Load up vertex shader
//####################################################################################
HRESULT BasicModel::CreateVertexShader(char* shaderFileName, char* vertexShaderFunctionName)
{
	ID3DBlob *p_vertexShader;
	ID3DBlob *p_error;
	HRESULT hr = S_OK;

	// Load up shader from the shader file
	hr = D3DX11CompileFromFile(shaderFileName, 0, 0, vertexShaderFunctionName, "vs_4_0", 0, 0, 0, &p_vertexShader, &p_error, 0);

	// Check for errors when loading the shader
	if (p_error != 0)
	{
		OutputDebugStringA((char*)p_error->GetBufferPointer());
		p_error->Release();

		if (FAILED(hr)) return hr;
	}

	// Create the vertex shader
	hr = m_pD3DDevice->CreateVertexShader(p_vertexShader->GetBufferPointer(), p_vertexShader->GetBufferSize(), NULL, &m_pVertexShader);
	if (FAILED(hr)) return hr;

	// Create the input layout for the shader
	hr = CreateInputLayout(p_vertexShader);
	if (FAILED(hr)) return hr;

	// Release the memory for the pointers
	if (p_vertexShader) p_vertexShader->Release();
	if (p_error) p_error->Release();

	return hr;
}

//####################################################################################
// Load up pixel shader
//####################################################################################
HRESULT BasicModel::CreatePixelShader(char* shaderFileName, char* pixerlShaderFunctionName)
{
	ID3DBlob *p_pixelShader;
	ID3DBlob *p_error;
	HRESULT hr = S_OK;

	// Load up shader from the shader file
	hr = D3DX11CompileFromFile(shaderFileName, 0, 0, pixerlShaderFunctionName, "ps_4_0", 0, 0, 0, &p_pixelShader, &p_error, 0);

	// Check for errors when loading the shader
	if (p_error != 0)
	{
		OutputDebugStringA((char*)p_error->GetBufferPointer());
		p_error->Release();

		if (FAILED(hr)) return hr;
	}

	// Create the pixel shader
	hr = m_pD3DDevice->CreatePixelShader(p_pixelShader->GetBufferPointer(), p_pixelShader->GetBufferSize(), NULL, &m_pPixelShader);
	if (FAILED(hr)) return hr;

	// Release the memory for the pointers
	if (p_pixelShader) p_pixelShader->Release();
	if (p_error) p_error->Release();

	return hr;
}

//####################################################################################
// Create input layout for the shaders
//####################################################################################
HRESULT BasicModel::CreateInputLayout(ID3DBlob* vertexShader)
{
	HRESULT hr = S_OK;

	// The format of the shader
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// Create the input layer
	hr = m_pD3DDevice->CreateInputLayout(inputElementDesc, ARRAYSIZE(inputElementDesc),
		vertexShader->GetBufferPointer(), vertexShader->GetBufferSize(), &m_pInputLayer);

	return hr; // Will return failed if creation failed
}

//####################################################################################
// Create the constant buffer
//####################################################################################
HRESULT BasicModel::CreateConstantBuffer(UINT bufferBytes)
{
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC constantBufferDesc; // Properties for constant buffer
	ZeroMemory(&constantBufferDesc, sizeof(constantBufferDesc));
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT; // Allow updateSubResource() to be used
	constantBufferDesc.ByteWidth = bufferBytes; // MUST BE MULTIPLE OF 16. Work out amount from the buffer struct
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // Use as a constant buffer

	// Create Buffer
	hr = m_pD3DDevice->CreateBuffer(&constantBufferDesc, NULL, &m_pConstantBuffer);
	return hr; // Will return failed if creation failed
}

//####################################################################################
// Load up the texture to be used on model
//####################################################################################
HRESULT BasicModel::AddTexture(char* textureFileName)
{
	HRESULT hr = S_OK;

	// Load texture from file
	hr = D3DX11CreateShaderResourceViewFromFile(m_pD3DDevice, textureFileName, NULL, NULL, &m_pTexture0, NULL);
	return hr; // Will return failed if loading failed
}

//####################################################################################
// Create the sampler for the texture filter
//####################################################################################
HRESULT BasicModel::CreateSampler(void)
{
	HRESULT hr = S_OK;

	// Set Filter using sample states
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // Set linear filtering
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the sample state
	hr = m_pD3DDevice->CreateSamplerState(&samplerDesc, &m_pSamplerState0);
	return hr; // Will return failed if creation failed
}

//####################################################################################
// Render the model in the game
//####################################################################################
void BasicModel::Draw(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection)
{
	m_pImmediateContext->VSSetShader(m_pVertexShader, 0, 0); // Set vertex shader
	m_pImmediateContext->PSSetShader(m_pPixelShader, 0, 0); // Set pixel shader
	m_pImmediateContext->IASetInputLayout(m_pInputLayer); // Set input layer

	// Set up the constant buffer
	SetConstantBufferValues(world, view, projection);

	// Set texture and sample state
	// First parameter is index and is set to 0 since we want to start from the start
	// Second parameter is the amount being set, which is 1
	// Third parameter is the address
	m_pImmediateContext->PSSetSamplers(0, 1, &m_pSamplerState0);
	m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTexture0);

	m_pObject->Draw(); // Draw object
}

//####################################################################################
// set up the constant buffer
//####################################################################################
void BasicModel::SetConstantBufferValues(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection)
{
	// Empty because the basic model won't use a constant buffer
}
