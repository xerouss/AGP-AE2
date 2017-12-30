// *********************************************************
//	Name:			Stephen Wong
//	File:			main.cpp
//	Last Updated:	30/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>

// Fixes the dxerr error
#include <stdio.h>
int (WINAPIV * __vsnprintf_s)(char *, size_t, const char*, va_list) = _vsnprintf;

#include "Window.h"
#include "Direct3D.h"
#include "Game\GameManager.h"
#include <time.h>
#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////
// Constants
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Constants
const LONG startingScreenWidth = 640;
const LONG startingScreenHeight = 480;
const int failed = 0;
#pragma endregion


//////////////////////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Functions

//####################################################################################
// Start point and message processing
//####################################################################################
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Create the window
	Window* pWindow = new Window(startingScreenWidth, startingScreenHeight, "Stephen Wong AE2\0");
	Direct3D* pDirect3D = new Direct3D;

	// Start up the window
	if (FAILED(pWindow->InitialiseWindow(hInstance, nCmdShow)))
	{
		DXTRACE_MSG("Failed to create Window");
		return failed;
	}

	// Start up D3D
	if (FAILED(pDirect3D->InitialiseD3D(pWindow->GetWindow())))
	{
		DXTRACE_MSG("Failed to create Device");
		return failed;
	}

	// Game Manager initiated here because Direct3D needs to be initialised first
	GameManager* pGameManager = new GameManager(pDirect3D->GetD3DDevice(),
		pDirect3D->GetBackBuffer(),
		pDirect3D->GetSwapChain(),
		pDirect3D->GetImmediateContext(),
		pDirect3D->GetZBuffer());

	// Set up input
	if (FAILED(pGameManager->InitialiseInput(pWindow->GetHInstance(),
		pWindow->GetWindow())))
	{
		DXTRACE_MSG("Failed to initialise input");
		return failed;
	}

	// Set up the level
	if (FAILED(pGameManager->InitialiseLevel()))
	{
		DXTRACE_MSG("Failed to initialise level");
		return failed;
	}

	// Set up the projection matrix
	pGameManager->SetProjectionMatrix((float)pWindow->GetScreenWidth(),
		(float)pWindow->GetScreenHeight());

	// Set up the HUD for the game
	pGameManager->InitialiseHUD();

	srand((unsigned int)time(NULL)); // Set up the random seed

	//// Main message loop
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		// Check the message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); // Translate message
			DispatchMessage(&msg); // Send to the application window
		}
		else
		{
			// Check if the window has been resized
			if (pWindow->GetUpdateViewport() == true)
			{
				// Update the viewport so it re-creates the buffers to match the new viewport size
				if (FAILED(pDirect3D->UpdateViewport(pWindow->GetScreenWidth(),
					pWindow->GetScreenHeight())))
				{
					DXTRACE_MSG("Failed to update viewport");
					return failed;
				}

				// Update the projection matrix with the new window size
				pGameManager->SetProjectionMatrix((float)pWindow->GetScreenWidth(),
					(float)pWindow->GetScreenHeight());

				// Need to reset the zbuffer or else the screen will be blank
				pGameManager->SetZBuffer(pDirect3D->GetZBuffer());

				// Viewport is updated so don't update again until it is changed again
				pWindow->SetUpdateViewport(false);
			}

			// Update objects
			pGameManager->Update();

			// Render graphics
			pGameManager->Render();
		}
	}

	// Delete all objects before exiting the game
	delete pGameManager;
	pGameManager = NULL;

	delete pDirect3D;
	pDirect3D = NULL;

	delete pWindow;
	pWindow = NULL;

	return (int)msg.wParam;
}
#pragma endregion
