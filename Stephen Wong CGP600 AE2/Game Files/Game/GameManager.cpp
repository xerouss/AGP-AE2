// *********************************************************
//	Name:			Stephen Wong
//	File:			GameManager.cpp
//	Last Updated:	02/01/2018
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
	m_pD3Device = device;
	m_pBackBuffer = backBuffer;
	m_pSwapChain = swapChain;
	m_pImmediateContext = immediateContext;
	m_pZBuffer = ZBuffer;
	m_currentGameState = PLAYING;
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
	hr = m_pInput->InitialiseDirectInput(hInstance, hWND);
	if (FAILED(hr)) return hr;

	// Set up keyboard input
	hr = m_pInput->InitialiseKeyboardInput();
	if (FAILED(hr)) return hr;

	// Set up mouse input
	hr = m_pInput->InitialiseMouse();
	return hr; // Will return failed if mouse failed
}

//####################################################################################
// Set up HUD
//####################################################################################
void GameManager::InitialiseHUD(void)
{
	// Create the HUD
	m_pHUD = new HUD(m_pD3Device, m_pImmediateContext);
}

//####################################################################################
// Set up the Level
//####################################################################################
HRESULT GameManager::InitialiseLevel(void)
{
	HRESULT hr = S_OK;

	// Set up time
	m_pTime = new Time();

	// Set up the level
	m_pLevel = new Level(m_pD3Device, m_pImmediateContext);

	hr = m_pLevel->SetUpLevel(&m_score, m_pTime);

	if (FAILED(hr)) return hr;

	return hr;
}

//####################################################################################
// Update any logic
//####################################################################################
void GameManager::Update(HWND window)
{
	// Get inputs
	m_pInput->ReadInputStates();

	// Only check inputs and move object if the player is playing the game
	if (m_currentGameState == PLAYING)
	{
		// Check if the player has done anything
		CheckPlayingInput();

		// Update the level objects
		m_pLevel->Update();
	}
	// IF the game is paused
	else if (m_currentGameState == PAUSED)
	{
		CheckPauseMenuInput(window);
	}
	else if (m_currentGameState == GAMEOVER)
	{
		CheckGameOverMenuInput(window);
	}

	// If not game over
	if (m_currentGameState != GAMEOVER)
	{
		// PAUSE/UNPAUSE GAME
		if (m_pInput->IsKeyPressed(DIK_ESCAPE))
		{
			SetPauseActive();
		}
	}
	
	// Check the player's health
	// Have to check if the game over menu is null otherwise it will
	// Create the game over menu every frame
	if (m_pLevel->GetPlayerHealth() == 0 && m_pGameOverMenu == NULL)
	{
		// The player has died
		GameOver();
	}
}

//####################################################################################
// Render game objects
//####################################################################################
void GameManager::Render(void)
{
	// Clear the back buffer
	m_pImmediateContext->ClearRenderTargetView(m_pBackBuffer, m_clearColour);

	// Clear zbuffer
	m_pImmediateContext->ClearDepthStencilView(m_pZBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Set the topology, triangle list is chosen since all objects will be made out of triangles
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Render the level
	m_pLevel->Render();

	// If the game is paused show the pause menu
	// Don't want to render the HUD while paused because it will
	// Clutter up the screen
	if (m_currentGameState == PAUSED)
	{
		m_pPauseMenu->Render();
	}
	// If playing show the HUD
	else if (m_currentGameState == PLAYING)
	{
		// Show the HUD
		m_pHUD->SetScoreText(to_string(m_score), scoreHUDXPos, scoreHUDYPos, scoreHUDTextSize);
		m_pHUD->SetHealthText(to_string(m_pLevel->GetPlayerHealth()), healthHUDXPos, healthHUDYPos, healthHUDTextSize);
		m_pHUD->SetTimerText(m_pTime->GetTimeSinceStartOfGameFormatted(), timerHUDXPos, timerHUDYPos, timerHUDTextSize);
		m_pHUD->Render();
	}
	else if (m_currentGameState == GAMEOVER)
	{
		m_pGameOverMenu->Render();
	}

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
	// Screen width and height are passed as floats so a float value can be retrieved
	// In the projection matrix when they are divided together
	// This is only called when the screen width / height has been changed.
	// This stops the projection matrix being worked out every frame

	// Save the screen width and height for the user interface
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Get the new projection matrix and pass it to the level
	XMMATRIX projection;
	projection = XMMatrixPerspectiveFovLH(defaultProjectionFOVAngleRadian,
		screenWidth / screenHeight, defaultNearClippingPlaneZ, defaultFarClippingPlaneZ);

	m_pLevel->SetProjectionMatrix(projection);
}

//####################################################################################
// Set whether to pause the game or not
//####################################################################################
void GameManager::SetPauseActive()
{
	if (m_currentGameState == PLAYING)
	{
		// Change state and create the pause menu to show
		m_currentGameState = PAUSED;
		m_pPauseMenu = new PauseMenu(m_pD3Device, m_pImmediateContext);
		m_pTime->StartPause(); // Pause the time
	}
	else
	{
		// Change game state and delete the pause menu since its not being used
		m_currentGameState = PLAYING;
		delete m_pPauseMenu;
		m_pPauseMenu = NULL;
		m_pTime->EndPause(); // Stop pausing the time
	}
}

//####################################################################################
// Check to see if the player has done anything while playing the game
//####################################################################################
void GameManager::CheckPlayingInput(void)
{
	if (m_pInput->IsKeyDown(DIK_W)) m_pLevel->MoveCameraForward(movementAmount);
	if (m_pInput->IsKeyDown(DIK_S)) m_pLevel->MoveCameraForward(-movementAmount);
	if (m_pInput->IsKeyDown(DIK_A)) m_pLevel->StrafeCamera(-movementAmount);
	if (m_pInput->IsKeyDown(DIK_D)) m_pLevel->StrafeCamera(movementAmount);
	if (m_pInput->IsKeyPressed(DIK_SPACE)) m_pLevel->ChangeActiveCamera();

	// Get x mouse change
	float mouseChangeAmount = (float)m_pInput->GetMousePositionChange(true);
	// If change has happened rotate the camera on X and Z
	// The amount is divided by an amount to prevent the rotation being super fast
	if (mouseChangeAmount != 0) m_pLevel->ChangeCameraXAndZDirection(mouseChangeAmount / convertFromScreenToWorldAmount);

	// Get y mouse change
	mouseChangeAmount = (float)m_pInput->GetMousePositionChange(false);
	// If change has happened rotate the camera on Y
	// The amount is divided by an amount to prevent the rotation being super fast
	if (mouseChangeAmount != 0) m_pLevel->ChangeCameraYDirection(-mouseChangeAmount / convertFromScreenToWorldAmount);
}

//####################################################################################
// Check to see if the player has done anything on the pause menu
//####################################################################################
void GameManager::CheckPauseMenuInput(HWND window)
{
	// If the player pressed his left mouse button
	if (m_pInput->IsMouseLeftButtonDown())
	{
		// Check if the player's mouse if over any of the buttons
		if (m_pPauseMenu->CheckResumeButtonIsPressed(m_pInput->GetXMousePosition(),
			m_pInput->GetYMousePosition(), m_screenWidth, m_screenHeight))
		{
			// Un-pause the game
			SetPauseActive();
		}
		else CheckExitButton(m_pPauseMenu, window);
	}
}

//####################################################################################
// Check to see if the player has  has done anything on the game over menu
//####################################################################################
void GameManager::CheckGameOverMenuInput(HWND window)
{
	// If the player pressed his left mouse button
	if (m_pInput->IsMouseLeftButtonDown())
	{
		// Check if the player's mouse if over any of the buttons
		if (m_pGameOverMenu->CheckRetryButtonIsPressed(m_pInput->GetXMousePosition(),
			m_pInput->GetYMousePosition(), m_screenWidth, m_screenHeight))
		{
			// Un-pause the game
			RecreateLevel();
		}
		else CheckExitButton(m_pGameOverMenu, window);
	}
}

//####################################################################################
// Check to see if the player has pressed the exit button on a menu
//####################################################################################
void GameManager::CheckExitButton(Menu* menu, HWND window)
{
	// Check if the exit button has been pressed
	if (menu->CheckExitButtonIsPressed(m_pInput->GetXMousePosition(),
		m_pInput->GetYMousePosition(), m_screenWidth, m_screenHeight))
	{
		// Close the window
		DestroyWindow(window);
	}
}

//####################################################################################
// Remake the level
//####################################################################################
void GameManager::RecreateLevel(void)
{
	// Delete the level
	delete m_pLevel;
	m_pLevel = NULL;

	// Delete the time
	delete m_pTime;
	m_pTime = NULL;

	// Re-create both the time and level
	InitialiseLevel();

	// Re-create the projection matrix
	SetProjectionMatrix(m_screenWidth, m_screenHeight);

	m_currentGameState = PLAYING;

	// Delete the game over menu
	delete m_pGameOverMenu;
	m_pGameOverMenu = NULL;
}

//####################################################################################
// Game over, the player has died
//####################################################################################
void GameManager::GameOver(void)
{
	// Change state of the game
	m_currentGameState = GAMEOVER;
	
	// Create the game over menu
	m_pGameOverMenu = new GameOverMenu(m_pD3Device, m_pImmediateContext);
}

