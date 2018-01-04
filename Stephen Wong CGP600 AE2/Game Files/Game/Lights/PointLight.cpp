// *********************************************************
//	Name:			Stephen Wong
//	File:			PointLight.cpp
//	Last Updated:	03401/2018
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "PointLight.h"

#pragma endregion

//####################################################################################
// Constructor
//####################################################################################
PointLight::PointLight(float red, float green, float blue, 
	float x, float y, float z, float range) :
	PositionalLight(red, green, blue, x, y, z, range)
{
	// Carry out positional light constructor
}

//####################################################################################
// Get where the point light is shining from
//####################################################################################
XMVECTOR PointLight::GetShineFromVector(XMMATRIX worldMatrix)
{
	XMVECTOR determinant; // Inverse function returns this but is not needed
	// Use inverse because it the correct position and rotation
	// While transpose only returns the correct rotation
	XMMATRIX inverse = XMMatrixInverse(&determinant, worldMatrix);
	XMVECTOR pointLightPos = XMVector3Transform(m_position, inverse);

	return pointLightPos;
}
