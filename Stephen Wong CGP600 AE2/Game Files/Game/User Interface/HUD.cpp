// *********************************************************
//	Name:			Stephen Wong
//	File:			HUD.cpp
//	Last Updated:	29/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "HUD.h"

#pragma endregion

//####################################################################################
// Constructor
//####################################################################################
HUD::HUD(ID3D11Device* device, ID3D11DeviceContext* immediateContext) :
	UserInterface(device, immediateContext)
{
	// Calls user interface's constructor first

	m_pScoreText = new Text2D("Assets/Font/redFontTransparent.png", device, immediateContext);
	m_pHealthText = new Text2D("Assets/Font/redFontTransparent.png", device, immediateContext);
	m_pTimerText = new Text2D("Assets/Font/redFontTransparent.png", device, immediateContext);
}

//####################################################################################
// Destructor
//####################################################################################
HUD::~HUD()
{
	if (m_pTimerText)
	{
		delete m_pTimerText;
		m_pTimerText = NULL;
	}

	if (m_pHealthText)
	{
		delete m_pHealthText;
		m_pHealthText = NULL;
	}

	if (m_pScoreText)
	{
		delete m_pScoreText;
		m_pScoreText = NULL;
	}
}

//####################################################################################
// Render text
//####################################################################################
void HUD::Render(void)
{
	// Enable transparency
	SetTransparencyActive(true);

	// Render the text
	m_pScoreText->RenderText();
	m_pHealthText->RenderText();
	m_pTimerText->RenderText();

	// Disable transparency
	// Need to disable it so it doesn't effect non-text objects
	SetTransparencyActive(false);
}

//####################################################################################
// Set the text for the score
//####################################################################################
void HUD::SetScoreText(string score, float x, float y, float size)
{
	m_pScoreText->AddText(score, x, y, size);
}

//####################################################################################
// Set the text for the health
//####################################################################################
void HUD::SetHealthText(string health, float x, float y, float size)
{
	m_pHealthText->AddText(health, x, y, size);
}

//####################################################################################
// Set the text for the timer
//####################################################################################
void HUD::SetTimerText(string time, float x, float y, float size)
{
	m_pTimerText->AddText(time, x, y, size);
}



