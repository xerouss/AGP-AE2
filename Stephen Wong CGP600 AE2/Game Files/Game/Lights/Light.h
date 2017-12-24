// *********************************************************
//	Name:			Stephen Wong
//	File:			Light.h
//	Last Updated:	24/12/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT

#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma endregion

#pragma region Constants

const int DefaultColourWValue = 1;

#pragma endregion

class Light
{
private:
	XMVECTOR m_colour;

public:
	Light(float red, float green, float blue);

	XMVECTOR GetLightColour(void);
	void SetLightColour(float red, float green, float blue);
};