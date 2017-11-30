// *********************************************************
//	Name:			Stephen Wong
//	File:			Window.h
//	Last Updated:	30/11/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include <d3d11.h>

#pragma endregion

class Window
{
private:
	LONG m_screenWidth;
	LONG m_screenHeight;
	HINSTANCE m_hInstance;
	HWND m_hWindow;
	char m_projectName[100];
public:
	Window(LONG screenWidth, LONG screenHeight, char projectName[100]);
	HRESULT InitialiseWindow(HINSTANCE hInstance, int nCmdShow);

	// This is static because the wndproc would not set when initialising if it wasn't
	// Got the solution from here: http://www.rastertek.com/dx11s2tut02.html (rastertek, n.d.) Last viewed: 30/11/2017
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//~Window();

#pragma region Get Methods

	HWND GetWindow(void);

#pragma endregion

};