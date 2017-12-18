// *********************************************************
//	Name:			Stephen Wong
//	File:			HUD.cpp
//	Last Updated:	18/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region MyRegion

#include "HUD.h"

#pragma endregion

//####################################################################################
// Constructor
//####################################################################################
HUD::HUD(ID3D11Device* device, ID3D11DeviceContext* immediateContext)
{
	// Store these so if any new text is created when the game is running, it will be displayed
	m_pD3DDevice = device;
	m_pImmediateContext = immediateContext;


	m_scoreText = new Text2D("Assets/Font/fontTransparent.png", m_pD3DDevice, m_pImmediateContext);
}

//####################################################################################
// Destructor
//####################################################################################
HUD::~HUD()
{
	if (m_scoreText)
	{
		delete m_scoreText;
		m_scoreText = NULL;
	}
}

//####################################################################################
// Render text
//####################################################################################
void HUD::Render(void)
{
	m_scoreText->RenderText();
}

void HUD::SetScoreText(string score, float x, float y, float size)
{
	m_scoreText->AddText(score, x, y, size);
}




