// *********************************************************
//	Name:			Stephen Wong
//	File:			PauseMenu.cpp
//	Last Updated:	30/12/2017
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
	UserInterface(device, immediateContext)
{
	// Calls user interface's constructor first

	// Create the text title for the pause menu
	m_pPauseTextTitle = new Text2D("Assets/Font/redFontTransparent.png", device, immediateContext);

	m_pResumeButton = new Button(device, immediateContext, "RESUME", resumeButtonX, resumeButtonY, resumeButtonSize);
	m_pExitButton	= new Button(device, immediateContext, "EXIT", exitButtonX, exitButtonY, exitButtonSize);
}

//####################################################################################
// Destructor
//####################################################################################
PauseMenu::~PauseMenu()
{

	if (m_pExitButton)
	{
		delete m_pExitButton;
		m_pExitButton = NULL;
	}

	if (m_pResumeButton)
	{
		delete m_pResumeButton;
		m_pResumeButton = NULL;
	}

	if (m_pPauseTextTitle)
	{
		delete m_pPauseTextTitle;
		m_pPauseTextTitle = NULL;
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
// Check if the exit button has been pressed
//####################################################################################
bool PauseMenu::CheckExitButtonIsPressed(float mouseXPosition, float mouseYPosition, 
	float screenWidth, float screenHeight)
{
	return m_pExitButton->IsPressed(mouseXPosition, mouseYPosition, screenWidth, screenHeight);
}


//####################################################################################
// Render the pause menu
//####################################################################################
void PauseMenu::Render(void)
{
	// Enable transparency
	SetTransparencyActive(true);

	// Set and render Text
	m_pPauseTextTitle->AddText(pauseTextTitleString, pauseTextTitleX,
		pauseTextTitleY, pauseTextTitleSize);
	m_pPauseTextTitle->RenderText();

	// Disable transparency
	SetTransparencyActive(false);

	// Render buttons after transparency since we don't want them to have it
	m_pResumeButton->Render();
	m_pExitButton->Render();
}

