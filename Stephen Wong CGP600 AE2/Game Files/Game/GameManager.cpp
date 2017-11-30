// *********************************************************
//	Name:			Stephen Wong
//	File:			GameManager.cpp
//	Last Updated:	30/11/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "GameManager.h"

#pragma endregion

//####################################################################################
// Render game objects
//####################################################################################
void GameManager::Render(ID3D11RenderTargetView* backBuffer, IDXGISwapChain* swapChain, ID3D11DeviceContext* immediateContext)
{
	// TESTING STUFF
	// Clear the back buffer - choose a colour you like
	float rgba_clear_colour[4] = { 0.1f, 1.0f, 0.1f, 1.0f };
	immediateContext->ClearRenderTargetView(backBuffer, rgba_clear_colour);

	// RENDER HERE

	// Display what has just been rendered
	swapChain->Present(0, 0);
	}
