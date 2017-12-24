// *********************************************************
//	Name:			Stephen Wong
//	File:			PositionalLight.h
//	Last Updated:	24/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "Light.h"

#pragma endregion

#pragma region Constants

const int DefaultPositionWValue = 1;

#pragma endregion

class PositionalLight : public Light
{
private:
	float m_lightRange;

protected:
	XMVECTOR m_position;

public:
	PositionalLight(float red, float green, float blue, float x, float y, float z, int range);

	bool IsPositionInLightRange(float xPos, float yPos, float zPos);

	// Get and set positions
	XMVECTOR GetPosition(void);
	void SetPosition(float x, float y, float z);

	// Get and set light range
	float GetLightRange(void);
	void SetLightRange(float range);
};
