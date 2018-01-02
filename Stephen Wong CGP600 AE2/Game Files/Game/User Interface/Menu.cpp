// *********************************************************
//	Name:			Stephen Wong
//	File:			Nenu.cpp
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Menu.h"

#pragma endregion

//####################################################################################
// Constructor
//####################################################################################
Menu::Menu(ID3D11Device* device, ID3D11DeviceContext* immediateContext, string titleText)
	:UserInterface(device, immediateContext)
{
	// Calls user interface's constructor first

	// Create the title and exit button
	m_pTextTitleString = titleText;
	m_pTextTitle = new Text2D("Assets/Font/redFontTransparent.png", device, immediateContext);
	m_pExitButton = new Button(device, immediateContext, "EXIT", exitButtonX, exitButtonY, exitButtonSize);
}

//####################################################################################
// Destructor
//####################################################################################
Menu::~Menu()
{
	if (m_pTextTitle)
	{
		delete m_pTextTitle;
		m_pTextTitle = NULL;
	}

	if (m_pExitButton)
	{
		delete m_pExitButton;
		m_pExitButton = NULL;
	}
}

//####################################################################################
// Render the menu
//####################################################################################
void Menu::Render(void)
{
	// Enable transparency
	SetTransparencyActive(true);

	// Set and render Text
	m_pTextTitle->AddText(m_pTextTitleString, titleTextTitleX,
		titleTextTitleY, titleTextTitleSize);
	m_pTextTitle->RenderText();

	// Disable transparency
	SetTransparencyActive(false);

	// Render buttons after transparency since we don't want them to have it
	m_pExitButton->Render();
}

//####################################################################################
// Check if the exit button has been pressed
//####################################################################################
bool Menu::CheckExitButtonIsPressed(float mouseXPosition, float mouseYPosition,
	float screenWidth, float screenHeight)
{
	return m_pExitButton->IsPressed(mouseXPosition, mouseYPosition, screenWidth, screenHeight);
}
