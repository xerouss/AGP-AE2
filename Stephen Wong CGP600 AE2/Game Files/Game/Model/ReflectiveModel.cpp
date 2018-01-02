// *********************************************************
//	Name:			Stephen Wong
//	File:			ReflectiveModel.cpp
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "ReflectiveModel.h"

#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////
// Structure for the constant buffer
//////////////////////////////////////////////////////////////////////////////////////
struct REFLECTIVE_MODEL_CONSTANT_BUFFER
{
	XMMATRIX worldViewProjection; // 64
	XMMATRIX worldView; // 64

	// TOTAL: 128 bytes
};

//####################################################################################
// Constructor
//####################################################################################
ReflectiveModel::ReflectiveModel(ID3D11Device* device, ID3D11DeviceContext* immediateContext)
	: Model(device, immediateContext)
{
	// Call model constructor

}

//####################################################################################
// Create constant buffer
//####################################################################################
HRESULT ReflectiveModel::CreateConstantBuffer()
{
	HRESULT hr = S_OK;

	// Create the constant buffer using the buffer structure size
	hr = BasicModel::CreateConstantBuffer(sizeof(REFLECTIVE_MODEL_CONSTANT_BUFFER));

	return hr;
}

//####################################################################################
// Set the constant buffer values
//####################################################################################
void ReflectiveModel::SetConstantBufferValues(XMMATRIX * world, XMMATRIX * view, XMMATRIX * projection)
{
	// Create constant buffer variable
	REFLECTIVE_MODEL_CONSTANT_BUFFER modelConstantBufferValues;

	// Set world view projection
	// Have to put the view and projection in brackets to dereference the pointer
	modelConstantBufferValues.worldViewProjection = (*world) * (*view) * (*projection);

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
