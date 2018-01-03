// *********************************************************
//	Name:			Stephen Wong
//	File:			SpecularLight.h
//	Last Updated:	03/01/2018
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include "DirectionalLight.h"

#pragma endregion


class SpecularLight : public DirectionalLight
{
private:
	float m_intensity;

public:
	SpecularLight(float intensitye,
		float red, float green, float blue,
		float x, float y, float z, float range,
		float xRotation, float yRotation, float zRotation);

	float GetIntensity(void);
	void SetIntensity(float intensity);
};