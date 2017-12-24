// *********************************************************
//	Name:			Stephen Wong
//	File:			Model.cpp
//	Last Updated:	24/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Model.h"

#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////
// Structure for the constant buffer
//////////////////////////////////////////////////////////////////////////////////////
struct MODEL_CONSTANT_BUFFER
{
	XMMATRIX worldViewProjection; // 64
	XMVECTOR ambientLightColour; // 16
	XMVECTOR directionalLightVector; // 16
	XMVECTOR directionalLightColour; // 16
	XMVECTOR pointLightVector; // 16
	XMVECTOR pointLightColour; // 16

	// TOTAL: 144 bytes
};

//////////////////////////////////////////////////////////////////////////////////////
// Private Methods
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Private Methods

//####################################################################################
// Get the centre point of the model so it can be used for collision
//####################################################################################
void Model::CalculateModelCentrePoint(void)
{
	float minX = 0.0f, maxX = 0.0f;
	float minY = 0.0f, maxY = 0.0f;
	float minZ = 0.0f, maxZ = 0.0f;

	// Go through all the vertices's and get the min and max value for each axis
	for (unsigned int i = 0; i < m_pObject->numverts; i++)
	{
		// X
		if (m_pObject->vertices[i].Pos.x < minX) minX = m_pObject->vertices[i].Pos.x;
		if (m_pObject->vertices[i].Pos.x > maxX) maxX = m_pObject->vertices[i].Pos.x;

		// Y
		if (m_pObject->vertices[i].Pos.y < minY) minY = m_pObject->vertices[i].Pos.y;
		if (m_pObject->vertices[i].Pos.y > maxY) maxY = m_pObject->vertices[i].Pos.y;

		// Z
		if (m_pObject->vertices[i].Pos.z < minZ) minZ = m_pObject->vertices[i].Pos.z;
		if (m_pObject->vertices[i].Pos.z > maxZ) maxZ = m_pObject->vertices[i].Pos.z;
	}

	// Get the midpoints for each axis
	m_boundingSphereCentreX = GetMidPointFromTwoFloats(minX, maxX);
	m_boundingSphereCentreY = GetMidPointFromTwoFloats(minY, maxY);
	m_boundingSphereCentreZ = GetMidPointFromTwoFloats(minZ, maxZ);
}

//####################################################################################
// Get the radius of the model so it can be used for collisions
//####################################################################################
void Model::CalculateBoundingSphereRadius(void)
{
	float distanceSquared;
	float highestDistanceSquared = 0;
	float dx;
	float dy;
	float dz;

	// Go through all vertices's
	for (unsigned int i = 0; i < m_pObject->numverts; i++)
	{
		// Work out the direction of the vertex and the centre
		dx = m_pObject->vertices[i].Pos.x - m_boundingSphereCentreX;
		dy = m_pObject->vertices[i].Pos.y - m_boundingSphereCentreY;
		dz = m_pObject->vertices[i].Pos.z - m_boundingSphereCentreZ;

		// Get the distance from the centre to the vertex
		distanceSquared = pow(dx, 2) + pow(dy, 2) + pow(dz, 2);

		// Store it if its the highest distance so far
		if (distanceSquared > highestDistanceSquared) highestDistanceSquared = distanceSquared;
	}

	// Square root here since its expensive to do so, so only do it once
	m_boundingSphereRadius = sqrt(highestDistanceSquared);
}

//####################################################################################
// Get the mid point of two floats so collision can be worked out
//####################################################################################
float Model::GetMidPointFromTwoFloats(float point1, float point2)
{
	return (point1 + point2) / 2;
}
#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Public Methods
//####################################################################################
// Constructor
//####################################################################################
Model::Model(ID3D11Device* device, ID3D11DeviceContext* immediateContext)
{
	m_pD3DDevice = device;
	m_pImmediateContext = immediateContext;
}

//####################################################################################
// Destructor
//####################################################################################
Model::~Model()
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
// Load up the model from a file and start bounding sphere calculations
//####################################################################################
int Model::LoadObjectModel(char* filename)
{
	// Load up the object
	m_pObject = new ObjectFileModel(filename, m_pD3DDevice, m_pImmediateContext);

	// Check if the model was loaded correctly
	if (m_pObject->filename == "FILE NOT LOADED") return S_FALSE;

	// Set up bounding sphere for collision
	CalculateModelCentrePoint();
	CalculateBoundingSphereRadius();

	return S_OK; // Object was loaded successfully
}

//####################################################################################
// Load up vertex shader
//####################################################################################
HRESULT Model::CreateVertexShader(char* shaderFileName, char* vertexShaderFunctionName)
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
	if(p_vertexShader) p_vertexShader->Release();
	if(p_error) p_error->Release();

	return hr;
}

//####################################################################################
// Load up pixel shader
//####################################################################################
HRESULT Model::CreatePixelShader(char* shaderFileName, char* pixerlShaderFunctionName)
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
HRESULT Model::CreateInputLayout(ID3DBlob* vertexShader)
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
HRESULT Model::CreateConstantBuffer()
{
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC constantBufferDesc; // Properties for constant buffer
	ZeroMemory(&constantBufferDesc, sizeof(constantBufferDesc));
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT; // Allow updateSubResource() to be used
	constantBufferDesc.ByteWidth = sizeof(MODEL_CONSTANT_BUFFER); // MUST BE MULTIPLE OF 16. Work out amount from the buffer struct
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // Use as a constant buffer

	// Create Buffer
	hr = m_pD3DDevice->CreateBuffer(&constantBufferDesc, NULL, &m_pConstantBuffer);
	return hr; // Will return failed if creation failed
}

//####################################################################################
// Load up the texture to be used on model
//####################################################################################
HRESULT Model::AddTexture(char* textureFileName)
{
	HRESULT hr = S_OK;

	// Load texture from file
	hr = D3DX11CreateShaderResourceViewFromFile(m_pD3DDevice, textureFileName, NULL, NULL, &m_pTexture0, NULL);
	return hr; // Will return failed if loading failed
}

//####################################################################################
// Create the sampler for the texture filter
//####################################################################################
HRESULT Model::CreateSampler(void)
{
	// TODO: Change this to allow different filtering?

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
void Model::Draw(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection)
{
	m_pImmediateContext->VSSetShader(m_pVertexShader, 0, 0); // Set vertex shader
	m_pImmediateContext->PSSetShader(m_pPixelShader, 0, 0); // Set pixel shader
	m_pImmediateContext->IASetInputLayout(m_pInputLayer); // Set input layer

														  // Set the world view projection to the constant buffer
	MODEL_CONSTANT_BUFFER modelConstantBufferValues;
	// Have to put the view and projection in brackets to dereference the pointer
	modelConstantBufferValues.worldViewProjection = (*world) * (*view) * (*projection);

	// Lighting
	modelConstantBufferValues.ambientLightColour = m_ambientLightColour;
	modelConstantBufferValues.directionalLightVector = m_directionalLightShinesFrom;
	modelConstantBufferValues.directionalLightColour = m_directionalLightColour;
	modelConstantBufferValues.pointLightVector = m_pointLightPosition;
	modelConstantBufferValues.pointLightColour = m_pointLightColour;

	// Update constant buffer
	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, 0, &modelConstantBufferValues, 0, 0);

	// Set active constant buffer for the vertex shader
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	// Set active constant buffer for the pixel shader
	m_pImmediateContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	// Set texture and sample state
	// First parameter is index and is set to 0 since we want to start from the start
	// Second parameter is the amount being set, which is 1
	// Third parameter is the address
	m_pImmediateContext->PSSetSamplers(0, 1, &m_pSamplerState0);
	m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTexture0);

	m_pObject->Draw(); // Draw object
}

//////////////////////////////////////////////////////////////////////////////////////
// Set Methods
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Set Methods

void Model::SetAmbientLight(XMVECTOR colour)
{
	m_ambientLightColour = colour;
}

void Model::SetDirectionalLight(XMVECTOR pos, XMVECTOR colour)
{
	m_directionalLightShinesFrom = pos;
	m_directionalLightColour = colour;
}

void Model::SetPointLight(XMVECTOR pos, XMVECTOR colour)
{
	m_pointLightPosition = pos;
	m_pointLightColour = colour;
}

#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////
// Get Methods
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Get Methods

//XMVECTOR Model::GetAmbientLightColour(void)
//{
//	return m_ambientLightColour;
//}
//
//XMVECTOR Model::GetDirectionalLightPos(void)
//{
//	return m_directionalLightShinesFrom;
//}
//
//XMVECTOR Model::GetDirectionalLightColour(void)
//{
//	return m_directionalLightColour;
//}
//
//XMVECTOR Model::GetPointLightPos(void)
//{
//	return m_pointLightPosition;
//}
//
//XMVECTOR Model::GetPointLightColour(void)
//{
//	return m_pointLightColour;
//}

float Model::GetBoundingSphereRadius(void)
{
	return m_boundingSphereRadius; // *m_scale;
}

float Model::GetBoundingSphereX(void)
{
	return m_boundingSphereCentreX;
}


float Model::GetBoundingSphereY(void)
{
	return m_boundingSphereCentreY;
}


float Model::GetBoundingSphereZ(void)
{
	return m_boundingSphereCentreZ;
}
#pragma endregion
#pragma endregion