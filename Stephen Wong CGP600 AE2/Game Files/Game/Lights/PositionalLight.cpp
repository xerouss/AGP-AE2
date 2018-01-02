// *********************************************************
//	Name:			Stephen Wong
//	File:			Light.h
//	Last Updated:	24/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "PositionalLight.h"

#pragma endregion

//####################################################################################
// Constructor
//####################################################################################
PositionalLight::PositionalLight(float red, float green, float blue, 
	float x, float y, float z, float range):
	Light(red, green, blue)
{
	SetPosition(x, y, z);
	SetLightRange(range);
}

//####################################################################################
// Check to see if the passed position is in the range of the light
//####################################################################################
bool PositionalLight::IsPositionInLightRange(float xPos, float yPos, float zPos)
{
	float x = m_position.vector4_f32[0];
	float y = m_position.vector4_f32[1];
	float z = m_position.vector4_f32[2];

	// The if statement check if all the axis are in the range of the light
	// By see if its bigger than the lower bounds and smaller than the upper bounds
	if (xPos < x + m_lightRange && xPos > x - m_lightRange &&
		yPos < y + m_lightRange && yPos > y - m_lightRange &&
		zPos < z + m_lightRange && zPos > z - m_lightRange)
		return true;

	return false;
}

//####################################################################################
// Get light position
//####################################################################################
XMVECTOR PositionalLight::GetPosition(void)
{
	return m_position;
}

//####################################################################################
// Set light position
//####################################################################################
void PositionalLight::SetPosition(float x, float y, float z)
{
	m_position = XMVectorSet(x, y, z, DefaultPositionWValue);
}

//####################################################################################
// Get light range
//####################################################################################
float PositionalLight::GetLightRange(void)
{
	return m_lightRange;
}

//####################################################################################
// Set light range
//####################################################################################
void PositionalLight::SetLightRange(float range)
{
	// Divide light range by 2 since half of it will be used in one direction
	// While the other half of the value will be used for the other
	// E.g.  if the range is 10, 5 of it will be used for the positive direction
	// While the other half will be used in the negative direction
	m_lightRange = range / 2;
}
