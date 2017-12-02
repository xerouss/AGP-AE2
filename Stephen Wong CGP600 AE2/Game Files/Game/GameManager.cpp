// *********************************************************
//	Name:			Stephen Wong
//	File:			GameManager.cpp
//	Last Updated:	02/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "GameManager.h"

#pragma endregion


//####################################################################################
// Constructor
//####################################################################################
GameManager::GameManager(ID3D11RenderTargetView* backBuffer, IDXGISwapChain* swapChain,
	ID3D11DeviceContext* immediateContext)
{
	m_pBackBuffer = backBuffer;
	m_pSwapChain = swapChain;
	m_pImmediateContext = immediateContext;
}

//####################################################################################
// Set up the graphics
//####################################################################################
void GameManager::InitialiseGraphics(void)
{
}

//####################################################################################
// Update any logic
//####################################################################################
void GameManager::Update(void)
{
}

//####################################################################################
// Render game objects
//####################################################################################
void GameManager::Render(void)
{
	// TESTING STUFF
	// Clear the back buffer - choose a colour you like
	float rgba_clear_colour[4] = { 0.1f, 1.0f, 0.1f, 1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pBackBuffer, rgba_clear_colour);

	// RENDER HERE

	// Display what has just been rendered
	m_pSwapChain->Present(0, 0);
}

