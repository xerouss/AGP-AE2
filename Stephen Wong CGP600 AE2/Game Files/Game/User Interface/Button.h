// *********************************************************
//	Name:			Stephen Wong
//	File:			Button.h
//	Last Updated:	30/12/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include "Text2D.h"
#include <string.h>

#pragma endregion

#pragma region Constants

const int viewPortLength = 2; // This is 2 because it goes from -1 to 1
const int viewPortMinLength = -1;
const int inverse = -1;

#pragma endregion

class Button
{
private:
	// The text will have a background which will act as the button background
	Text2D* m_pText;
	string m_buttonText;
	float m_xPosition;
	float m_yPosition;

	float m_minXPosition;
	float m_maxXPosition;
	float m_minYPosition;
	float m_maxYPosition;
	float m_size;
public:
	Button(ID3D11Device* device, ID3D11DeviceContext* immediateContext, 
		string buttonText, float x, float y, float size);
	~Button();

	void Render(void);
	bool IsPressed(float mouseXPosition, float mouseYPosition, float screenWidth,
		float screenHeight);
};