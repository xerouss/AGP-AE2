// *********************************************************
//	Name:			Stephen Wong
//	File:			Button.cpp
//	Last Updated:	30/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Button.h"

#pragma endregion

//####################################################################################
// Constructor
//####################################################################################
Button::Button(ID3D11Device* device, ID3D11DeviceContext* immediateContext,
	string buttonText, float x, float y, float size)
{
	m_buttonText = buttonText;
	m_xPosition = x;
	m_yPosition = y;
	m_size = size;

	// Create the text for the button
	m_pText = new Text2D("Assets/Font/whiteFont.bmp", device, immediateContext);

	m_minXPosition = x; // This is min x because it starts from left
	m_maxYPosition = y; // This is max y since the text start from the top

	// To get the max x position we use the starting x position
	// Then add on the amount of characters there are in the text * by the size
	// This will give us the total width of all the characters which will give us the max x position
	m_maxXPosition = x + (buttonText.length() * size);

	// Same principle as x but since its on the y we only need to check one character
	// So we just - size. It - because the verticies in the check go downwards
	m_minYPosition = y - size;
}

//####################################################################################
// Destructor
//####################################################################################
Button::~Button()
{
	if (m_pText)
	{
		delete m_pText;
		m_pText = NULL;
	}
}

//####################################################################################
// Render button
//####################################################################################
void Button::Render(void)
{
	// Have to add text every frame since it deletes it after rendering it
	// TODO: CHECK THIS
	m_pText->AddText(m_buttonText, m_xPosition, m_yPosition, m_size);
	m_pText->RenderText();
}

//####################################################################################
// Check if the button has been pressed
//####################################################################################
bool Button::IsPressed(float mouseXPosition, float mouseYPosition, float screenWidth,
	float screenHeight)
{
	// Got the equation to convert from screen to viewport:
	// https://gamedev.stackexchange.com/questions/32555/how-do-i-convert-between-two-different-2d-coordinate-systems (Kravemir, 2012) Last viewed: 30/12/2017
	// The equation is = (Value - s.Min) / (s.Max - s.Min) * (v.Max - v.Min) + v.Min
	// Value = the x or y value being inputted
	// s = screen
	// v = viewport

	// Filling the equation in with my value we get:
	// X or Y = (XPos or Y - 0) / (screen height or width - 0) * (1 - -1) - 1
	// Which = XPos or Y / screen height or width * 2 - 1

	// The y had a * -1 at the end because to inverse the viewport since
	// Without it top would be -1 while bot would be 1
	mouseXPosition = mouseXPosition / screenWidth * viewPortLength + viewPortMinLength;
	mouseYPosition = (mouseYPosition / screenHeight * viewPortLength + viewPortMinLength) * inverse;

	if (mouseXPosition < m_maxXPosition && mouseXPosition > m_minXPosition &&
		mouseYPosition < m_maxYPosition && mouseYPosition > m_minYPosition)
	{
		// Mouse is in the button so it has been clicked
		return true;
	}

	return false;
}






