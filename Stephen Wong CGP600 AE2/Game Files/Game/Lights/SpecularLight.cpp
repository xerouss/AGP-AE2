// *********************************************************
//	Name:			Stephen Wong
//	File:			SpecularLight.cpp
//	Last Updated:	03/01/2018
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "SpecularLight.h"

#pragma endregion

//####################################################################################
// Constructor
//####################################################################################
SpecularLight::SpecularLight(float intensity,
	float red, float green, float blue,
	float x, float y, float z, float range,
	float xRotation, float yRotation, float zRotation) :
	DirectionalLight(red, green, blue, x, y, z, range, xRotation, yRotation, zRotation)
{
	// Call the directional light constructor

	m_intensity = intensity;
}

//####################################################################################
// Get Intensity
//####################################################################################
float SpecularLight::GetIntensity(void)
{
	return m_intensity;
}

//####################################################################################
// Set Intensity
//####################################################################################
void SpecularLight::SetIntensity(float intensity)
{
	m_intensity = intensity;
}