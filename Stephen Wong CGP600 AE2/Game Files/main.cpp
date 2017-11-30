// *********************************************************
//	Name:			Stephen Wong
//	File:			main.cpp
//	Last Updated:	30/11/2017
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
#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////
// Constants
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Constants
LONG startingScreenWidth = 640;
LONG startingScreenHeight = 480;

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
	Window* window = new Window(startingScreenWidth, startingScreenHeight, "Stephen Wong AE2\0");

	// Start up the window
	if (FAILED(window->InitialiseWindow(hInstance, nCmdShow)))
	{
		DXTRACE_MSG("Failed to create Window");
		return 0;
	}

	// Start up the input
	/*if (FAILED(g_pInput->InitialiseInput(hInstance, g_hWnd)))
	{
	DXTRACE_MSG("Failed to initialise input");
	return 0;
	}*/

	// Start up D3D
	//if (FAILED(InitialiseD3D()))
	//{
	//	DXTRACE_MSG("Failed to create Device");
	//	return 0;
	//}

	//// Start up the graphics
	//if (FAILED(InitialiseGraphics()))
	//{
	//	DXTRACE_MSG("Failed to initialise graphics");
	//	return 0;
	//}

	//// Main message loop
	MSG msg = { 0 };
	int colourChoice = 0;
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Render graphics
			//RenderFrame();
		}
	}

	// Delete all objects before exiting the game
	ShutdownD3D();

	// Delete the pointer before exiting
	delete window;
	window = NULL;

	return (int)msg.wParam;
}

//####################################################################################
// Clean up objects
//####################################################################################
void ShutdownD3D()
{

}
#pragma endregion
