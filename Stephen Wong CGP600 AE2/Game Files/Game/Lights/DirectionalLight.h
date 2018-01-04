// *********************************************************
//	Name:			Stephen Wong
//	File:			DirectionalLight.h
//	Last Updated:	03/01/2018
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include "PositionalLight.h"

#pragma endregion

class DirectionalLight : public PositionalLight
{
private:
	// THESE ARE IN RADIANS
	float m_xRotation;
	float m_yRotation;
	float m_zRotation;

public:
	DirectionalLight(float red, float green, float blue, 
		float x, float y, float z, float range,
		float xRotation, float yRotation, float zRotation);

	XMVECTOR GetShineFromVector(XMMATRIX worldMatrix);

	// Set Methods
	void SetRotation(float x, float y, float z);
	void SetXRotation(float x);
	void SetYRotation(float y);
	void SetZRotation(float z);

	// Get Methods
	float GetXRotation(void);
	float GetYRotation(void);
	float GetZRotation(void);
};
