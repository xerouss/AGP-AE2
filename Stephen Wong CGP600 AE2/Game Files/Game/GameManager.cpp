// *********************************************************
//	Name:			Stephen Wong
//	File:			GameManager.cpp
//	Last Updated:	05/12/2017
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
GameManager::GameManager(ID3D11Device* device, ID3D11RenderTargetView* backBuffer, IDXGISwapChain* swapChain,
	ID3D11DeviceContext* immediateContext)
{
	m_pD3DDevice = device;
	m_pBackBuffer = backBuffer;
	m_pSwapChain = swapChain;
	m_pImmediateContext = immediateContext;
}

//####################################################################################
// Destructor
//####################################################################################
GameManager::~GameManager()
{
	if (m_pLevel)
	{
		delete m_pLevel;
		m_pLevel = NULL;
	}
}

//####################################################################################
// Set up the Level
//####################################################################################
HRESULT GameManager::InitialiseLevel(void)
{
	HRESULT hr = S_OK;

	m_pLevel = new Level(m_pD3DDevice, m_pImmediateContext);

	hr = m_pLevel->SetUpLevel();

	// If failed will return fail else it would have been set up
	return hr;
}

//####################################################################################
// Update any logic
//####################################################################################
void GameManager::Update(void)
{
	m_pLevel->Update();
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
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// RENDER HERE
	m_pLevel->Render();

	// Display what has just been rendered
	m_pSwapChain->Present(0, 0);
}

