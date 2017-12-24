// *********************************************************
//	Name:			Stephen Wong
//	File:			PointLight.h
//	Last Updated:	24/12/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include "PositionalLight.h"

#pragma endregion

class PointLight : public PositionalLight
{
private:

public:
	PointLight(float red, float green, float blue,
		float x, float y, float z, int range);
	XMVECTOR GetShineFromVector(XMMATRIX worldMatrix);
};