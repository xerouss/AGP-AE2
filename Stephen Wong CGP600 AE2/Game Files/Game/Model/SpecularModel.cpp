// *********************************************************
//	Name:			Stephen Wong
//	File:			SpecularModel.cpp
//	Last Updated:	03/01/2018
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "SpecularModel.h"

#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////
// Structure for the constant buffer
//////////////////////////////////////////////////////////////////////////////////////
struct SPECULAR_MODEL_CONSTANT_BUFFER
{
	XMMATRIX worldViewProjection; // 64
	XMVECTOR ambientLightColour; // 16
	XMVECTOR specularLightVector; // 16
	XMVECTOR specularLightColour; // 16
	float specularIntensity; // 4
	float packingBytes1; // 4
	float packingBytes2; // 4
	float packingBytes3; // 4
	XMVECTOR directionalLightColour; // 16
	XMMATRIX worldView; // 64

	// TOTAL: 224 bytes
};

//####################################################################################
// Constructor
//####################################################################################
SpecularModel::SpecularModel(ID3D11Device* device, ID3D11DeviceContext* immediateContext)
	: Model(device, immediateContext)
{
	// Call model constructor

}

//####################################################################################
// Create constant buffer
//####################################################################################
HRESULT SpecularModel::CreateConstantBuffer()
{
	HRESULT hr = S_OK;

	// Create the constant buffer using the buffer structure size
	hr = BasicModel::CreateConstantBuffer(sizeof(SPECULAR_MODEL_CONSTANT_BUFFER));

	return hr;
}

//####################################################################################
// Set the constant buffer values
//####################################################################################
void SpecularModel::SetConstantBufferValues(XMMATRIX * world, XMMATRIX * view, XMMATRIX * projection)
{
	// Create constant buffer variable
	SPECULAR_MODEL_CONSTANT_BUFFER modelConstantBufferValues;

	// Set world view projection
	// Have to put the view and projection in brackets to dereference the pointer
	modelConstantBufferValues.worldViewProjection = (*world) * (*view) * (*projection);

	modelConstantBufferValues.ambientLightColour = m_ambientLightColour;
	modelConstantBufferValues.specularLightVector= m_specularLightShinesFrom;
	modelConstantBufferValues.specularLightColour = m_specularLightShinesFrom;
	modelConstantBufferValues.specularIntensity = m_specularLightIntestity;
	modelConstantBufferValues.directionalLightColour = m_directionalLightColour;

	// Set world view
	// Have to put the view and projection in brackets to dereference the pointer
	modelConstantBufferValues.worldView = (*world) * (*view);

	// Update constant buffer
	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, 0, &modelConstantBufferValues, 0, 0);

	// Set active constant buffer for the vertex shader
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	// Set active constant buffer for the pixel shader
	m_pImmediateContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
}

//####################################################################################
// Set the specular light attributes
//####################################################################################
void SpecularModel::SetSpecularLight(XMVECTOR pos, XMVECTOR colour, float intesity)
{
	m_specularLightShinesFrom = pos;
	m_specularLightColour = colour;
	m_specularLightIntestity = intesity;
}
