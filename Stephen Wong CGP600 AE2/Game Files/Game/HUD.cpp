// *********************************************************
//	Name:			Stephen Wong
//	File:			HUD.cpp
//	Last Updated:	27/12/2017
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
HUD::HUD(ID3D11Device* device, ID3D11DeviceContext* immediateContext)
{
	// Store these so if any new text is created when the game is running, it will be displayed
	m_pD3DDevice = device;
	m_pImmediateContext = immediateContext;

	InitialiseTransparency();

	m_scoreText = new Text2D("Assets/Font/fontTransparent.png", m_pD3DDevice, m_pImmediateContext);
	m_healthText = new Text2D("Assets/Font/fontTransparent.png", m_pD3DDevice, m_pImmediateContext);
	m_timerText = new Text2D("Assets/Font/fontTransparent.png", m_pD3DDevice, m_pImmediateContext);
}

//####################################################################################
// Destructor
//####################################################################################
HUD::~HUD()
{
	if (m_timerText)
	{
		delete m_timerText;
		m_timerText = NULL;
	}

	if (m_healthText)
	{
		delete m_healthText;
		m_healthText = NULL;
	}

	if (m_scoreText)
	{
		delete m_scoreText;
		m_scoreText = NULL;
	}

	if (m_pAlphaBlendEnable) m_pAlphaBlendEnable->Release();
	if (m_pAlphaBlendDisable) m_pAlphaBlendDisable->Release();
}

//####################################################################################
// Render text
//####################################################################################
void HUD::Render(void)
{
	// Enable transparency
	m_pImmediateContext->OMSetBlendState(m_pAlphaBlendEnable, 0, blendStateSampleMask);

	// Render the text
	m_scoreText->RenderText();
	m_healthText->RenderText();
	m_timerText->RenderText();

	// Disable transparency
	// Need to disable it so it doesn't effect non-text objects
	m_pImmediateContext->OMSetBlendState(m_pAlphaBlendDisable, 0, blendStateSampleMask);
}

//####################################################################################
// Set the text for the score
//####################################################################################
void HUD::SetScoreText(string score, float x, float y, float size)
{
	m_scoreText->AddText(score, x, y, size);
}

//####################################################################################
// Set the text for the health
//####################################################################################
void HUD::SetHealthText(string health, float x, float y, float size)
{
	m_healthText->AddText(health, x, y, size);
}

//####################################################################################
// Set the text for the timer
//####################################################################################
void HUD::SetTimerText(string time, float x, float y, float size)
{
	m_timerText->AddText(time, x, y, size);
}

//####################################################################################
// Set transparency for text
//####################################################################################
void HUD::InitialiseTransparency(void)
{
	// Set up blend for transparency
	// Used mainly for text
	D3D11_BLEND_DESC blendDesc;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.AlphaToCoverageEnable = false;

	// Create the blend state and save it
	m_pD3DDevice->CreateBlendState(&blendDesc, &m_pAlphaBlendEnable);
}




