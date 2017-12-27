// *********************************************************
//	Name:			Stephen Wong
//	File:			GameManager.cpp
//	Last Updated:	20/12/2017
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
	ID3D11DeviceContext* immediateContext, ID3D11DepthStencilView* ZBuffer)
{
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
	if (m_pTime)
	{
		delete m_pTime;
		m_pTime = NULL;
	}

	if (m_pHUD)
	{
		delete m_pHUD;
		m_pHUD = NULL;
	}

	if (m_pInput)
	{
		delete m_pInput;
		m_pInput = NULL;
	}

	if (m_pLevel)
	{
		delete m_pLevel;
		m_pLevel = NULL;
	}
}

//####################################################################################
// Set up input
//####################################################################################
HRESULT GameManager::InitialiseInput(HINSTANCE hInstance, HWND hWND)
{
	HRESULT hr = S_OK;

	m_pInput = new Input();

	// Set up the direct input first
	// Without setting up direct input first we can't set up the keyboard or mouse
	hr = m_pInput->InitialiseDirectInput(hInstance);
	if (FAILED(hr)) return hr;

	// Set up keyboard input
	hr = m_pInput->InitialiseKeyboardInput(hWND);
	if (FAILED(hr)) return hr;

	// Set up mouse input
	hr = m_pInput->InitialiseMouse(hWND);
	return hr; // Will return failed if mouse failed
}

//####################################################################################
// Set up HUD
//####################################################################################
void GameManager::InitialiseHUD(ID3D11Device* device)
{
	m_pHUD = new HUD(device, m_pImmediateContext);
}

//####################################################################################
// Set up the Level
//####################################################################################
HRESULT GameManager::InitialiseLevel(ID3D11Device* device)
{
	HRESULT hr = S_OK;

	m_pLevel = new Level(device, m_pImmediateContext);

	hr = m_pLevel->SetUpLevel(&m_score);

	if (FAILED(hr)) return hr;

	// Set up time since level has now been created
	m_pTime = new Time(); 

	return hr;
}

//####################################################################################
// Update any logic
//####################################################################################
void GameManager::Update(void)
{
	// Get inputs
	m_pInput->ReadInputStates();


	// Exit game if escape pressed
	// Need to make update return bool and true if escape pressed to exit
	// if(m_pInput->IsKeyPressed(DIK_ESCAPE))  

	if (m_pInput->IsKeyDown(DIK_W)) m_pLevel->MoveCameraForward(1);
	if (m_pInput->IsKeyDown(DIK_S)) m_pLevel->MoveCameraForward(-1);
	if (m_pInput->IsKeyDown(DIK_A)) m_pLevel->StrafeCamera(-1);
	if (m_pInput->IsKeyDown(DIK_D)) m_pLevel->StrafeCamera(1);

	float mouseChangeAmount = (float)m_pInput->GetMousePositionChange(true);
	if (mouseChangeAmount != 0) m_pLevel->ChangeCameraDirection(mouseChangeAmount / 100);

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

	// Render the level
	m_pLevel->Render();

	// Show the score in the HUD
	m_pHUD->SetScoreText(to_string(m_score), scoreHUDXPos, scoreHUDYPos, scoreHUDTextSize);
	m_pHUD->SetHealthText(to_string(m_pLevel->GetPlayerHealth()), healthHUDXPos, healthHUDYPos, healthHUDTextSize);
	m_pHUD->SetTimerText(m_pTime->GetTimeSinceStartOfGameFormatted(), timerHUDXPos, timerHUDYPos, timerHUDTextSize);
	m_pHUD->Render();

	// Display what has just been rendered
	m_pSwapChain->Present(0, 0);
}

//####################################################################################
// Set Z buffer
//####################################################################################
void GameManager::SetZBuffer(ID3D11DepthStencilView * zbuffer)
{
	m_pZBuffer = zbuffer; // Need to reset z buffer when resizing window
}

//####################################################################################
// Update the level's projection matrix
//####################################################################################
void GameManager::SetProjectionMatrix(float screenWidth, float screenHeight)
{
	XMMATRIX projection;
	projection = XMMatrixPerspectiveFovLH(defaultProjectionFOVAngleRadian, 
		screenWidth/ screenHeight, defaultNearClippingPlaneZ, defaultFarClippingPlaneZ);

	m_pLevel->SetProjectionMatrix(projection);
}

