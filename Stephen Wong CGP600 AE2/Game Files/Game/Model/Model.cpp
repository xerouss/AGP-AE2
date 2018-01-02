// *********************************************************
//	Name:			Stephen Wong
//	File:			Model.cpp
//	Last Updated:	02/01/2018
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
Model::Model(ID3D11Device* device, ID3D11DeviceContext* immediateContext) :
	BasicModel(device, immediateContext)
{
	// Call the basic model constructor
}

//####################################################################################
// Create constant buffer
//####################################################################################
HRESULT Model::CreateConstantBuffer()
{
	HRESULT hr = S_OK;

	// Create the constant buffer using the buffer structure size
	hr = BasicModel::CreateConstantBuffer(sizeof(MODEL_CONSTANT_BUFFER));

	return hr;
}

//####################################################################################
// Set the constant buffer values
//####################################################################################
void Model::SetConstantBufferValues(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection)
{
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
}

//####################################################################################
// Load up the model from a file and start bounding sphere calculations
//####################################################################################
int Model::LoadObjectModel(char* filename)
{
	int check = BasicModel::LoadObjectModel(filename);

	// If object model was loaded
	if (check == S_OK)
	{
		// Set up bounding sphere for collision
		CalculateModelCentrePoint();
		CalculateBoundingSphereRadius();
	}

	return check;
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