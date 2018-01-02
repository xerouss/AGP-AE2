// *********************************************************
//	Name:			Stephen Wong
//	File:			GameOverMenu.cpp
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "GameOverMenu.h"

#pragma endregion

//####################################################################################
// Constructor
//####################################################################################
GameOverMenu::GameOverMenu(ID3D11Device* device, ID3D11DeviceContext* immediateContext)
	: Menu(device, immediateContext, gameOverMenuTitle)
{
	// Call menu's constructor first

	// Create the resume button
	m_pRetryButton = new Button(device, immediateContext, "RETRY", retryButtonX, retryButtonY, retryButtonSize);
}

//####################################################################################
// Destructor
//####################################################################################
GameOverMenu::~GameOverMenu()
{
	if (m_pRetryButton)
	{
		delete m_pRetryButton;
		m_pRetryButton = NULL;
	}
}

//####################################################################################
// Check if the retry button has been pressed
//####################################################################################
bool GameOverMenu::CheckRetryButtonIsPressed(float mouseXPosition, float mouseYPosition, float screenWidth, float screenHeight)
{
	return m_pRetryButton->IsPressed(mouseXPosition, mouseYPosition, screenWidth, screenHeight);
}

//####################################################################################
// Render the pause menu
//####################################################################################
void GameOverMenu::Render(void)
{
	// Do the menu render first
	Menu::Render();

	m_pRetryButton->Render();
}
