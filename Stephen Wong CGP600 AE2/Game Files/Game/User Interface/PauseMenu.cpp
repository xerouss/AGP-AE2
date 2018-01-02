// *********************************************************
//	Name:			Stephen Wong
//	File:			PauseMenu.cpp
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "PauseMenu.h"

#pragma endregion

//####################################################################################
// Constructor
//####################################################################################
PauseMenu::PauseMenu(ID3D11Device* device, ID3D11DeviceContext* immediateContext) :
	Menu(device, immediateContext, pauseMenuTitle)
{
	// Call menu's constructor first

	// Create the resume button
	m_pResumeButton = new Button(device, immediateContext, "RESUME", resumeButtonX, resumeButtonY, resumeButtonSize);
}

//####################################################################################
// Destructor
//####################################################################################
PauseMenu::~PauseMenu()
{
	if (m_pResumeButton)
	{
		delete m_pResumeButton;
		m_pResumeButton = NULL;
	}
}

//####################################################################################
// Check if the resume button has been pressed
//####################################################################################
bool PauseMenu::CheckResumeButtonIsPressed(float mouseXPosition, float mouseYPosition,
	float screenWidth, float screenHeight)
{
	return m_pResumeButton->IsPressed(mouseXPosition, mouseYPosition, screenWidth, screenHeight);
}

//####################################################################################
// Render the pause menu
//####################################################################################
void PauseMenu::Render(void)
{
	// Do the menu render first
	Menu::Render();

	m_pResumeButton->Render();
}

