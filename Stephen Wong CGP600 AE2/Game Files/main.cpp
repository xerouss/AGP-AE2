// *********************************************************
//	Name:			Stephen Wong
//	File:			main.cpp
//	Last Updated:	09/12/2017
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
#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////
// Constants
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Constants
const LONG startingScreenWidth = 640;
const LONG startingScreenHeight = 480;

#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////
// Global Variables
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Global Variables
//HINSTANCE	g_hInst = NULL;
//HWND		g_hWnd = NULL;

#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Forward Declarations
void ShutdownD3D();
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
		return 0;
	}

	// Start up D3D
	if (FAILED(pDirect3D->InitialiseD3D(pWindow->GetWindow())))
	{
		DXTRACE_MSG("Failed to create Device");
		return 0;
	}

	// Game Manager initiated here because Direct3D needs to be initialised first
	GameManager* pGameManager = new GameManager(pDirect3D->GetBackBuffer(),
		pDirect3D->GetSwapChain(),
		pDirect3D->GetImmediateContext(),
		pDirect3D->GetZBuffer());

	// Set up input
	if (FAILED(pGameManager->InitialiseInput(pWindow->GetHInstance(),
		pWindow->GetWindow())))
	{
		DXTRACE_MSG("Failed to initialise input");
		return 0;
	}

	// Set up the level
	if (FAILED(pGameManager->InitialiseLevel(pDirect3D->GetD3DDevice())))
	{
		DXTRACE_MSG("Failed to initialise level");
		return 0;
	}

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
			// Update objects
			pGameManager->Update();

			// Render graphics
			pGameManager->Render();
		}
	}

	// Delete all objects before exiting the game
	ShutdownD3D();

	delete pGameManager;
	pGameManager = NULL;

	delete pDirect3D;
	pDirect3D = NULL;

	delete pWindow;
	pWindow = NULL;

	return (int)msg.wParam;
}

//####################################################################################
// Clean up objects
//####################################################################################
void ShutdownD3D()
{

}
#pragma endregion
