// *********************************************************
//	Name:			Stephen Wong
//	File:			DirectionalLight.h
//	Last Updated:	03/01/2018
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "DirectionalLight.h"

#pragma endregion

//####################################################################################
// Constructor
//####################################################################################
DirectionalLight::DirectionalLight(float red, float green, float blue, float x, float y, float z, float range, float xRotation, float yRotation, float zRotation) :
	PositionalLight(red, green, blue, x, y, z, range)
{
	SetRotation(xRotation, yRotation, zRotation);
}

//####################################################################################
// Get where the directional Light is shining from
//####################################################################################
XMVECTOR DirectionalLight::GetShineFromVector(void)
{
	// Apply rotations
	XMMATRIX transformMatrix = XMMatrixRotationRollPitchYaw(m_xRotation, m_yRotation, m_zRotation);
	transformMatrix = XMMatrixTranspose(transformMatrix); // Transpose so it rotates the correct way

	// Get the vector for the matrix for the shine direction
	XMVECTOR shineFrom = XMVector3Transform(m_position, transformMatrix);
	shineFrom = XMVector3Normalize(shineFrom);

	return shineFrom;
}

//////////////////////////////////////////////////////////////////////////////////////
// Set Methods
//////////////////////////////////////////////////////////////////////////////////////
void DirectionalLight::SetRotation(float x, float y, float z)
{
	SetXRotation(x);
	SetYRotation(y);
	SetZRotation(z);
}

void DirectionalLight::SetXRotation(float x)
{
	m_xRotation = x;
}

void DirectionalLight::SetYRotation(float y)
{
	m_yRotation = y;
}

void DirectionalLight::SetZRotation(float z)
{
	m_zRotation = z;
}

//////////////////////////////////////////////////////////////////////////////////////
// Get Methods
//////////////////////////////////////////////////////////////////////////////////////
float DirectionalLight::GetXRotation(void)
{
	return m_xRotation;
}

float DirectionalLight::GetYRotation(void)
{
	return m_yRotation;
}

float DirectionalLight::GetZRotation(void)
{
	return m_zRotation;
}
