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
	ID3D11DeviceContext* immediateContext, ID3D11DepthStencilView* ZBuffer)
{
	m_pD3DDevice = device;
	m_pBackBuffer = backBuffer;
	m_pSwapChain = swapChain;
	m_pImmediateContext = immediateContext;
	m_pZBuffer = ZBuffer;
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
	// Clear the back buffer
	float rgba_clear_colour[4] = { 0.1f, 1.0f, 0.1f, 1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pBackBuffer, rgba_clear_colour);

	// Clear zbuffer
	m_pImmediateContext->ClearDepthStencilView(m_pZBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Set the topology, triangle list is chosen since all objects will be made out of triangles
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// RENDER HERE
	m_pLevel->Render();

	// Display what has just been rendered
	m_pSwapChain->Present(0, 0);
}

