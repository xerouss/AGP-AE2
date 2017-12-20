// *********************************************************
//	Name:			Stephen Wong
//	File:			Window.cpp
//	Last Updated:	20/12/2017
//	Project:		CGP600 AE2
// *********************************************************


//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Window.h"

#pragma endregion

LONG Window::m_screenWidth = 0;
LONG Window::m_screenHeight = 0;
bool  Window::m_updateViewport = false;

//####################################################################################
// Constructor
//####################################################################################
Window::Window(LONG screenWidth, LONG screenHeight, char projectName[100])
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Save the project name
	// Got to do it this way because you can't array = array
	strcpy_s(m_projectName, projectName);

	m_updateViewport = false;

}

//####################################################################################
// Create the window
//####################################################################################
HRESULT Window::InitialiseWindow(HINSTANCE hInstance, int nCmdShow)
{
	// Application window name
	char Name[100] = "Stephen Wong\0";

	// Register class
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = Name;

	// Check if failed
	if (!RegisterClassEx(&wcex)) return E_FAIL;

	// Create window
	m_hInstance = hInstance;

	// Create the rectangle for the window
	RECT rc = { 0, 0, m_screenWidth, m_screenHeight };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	m_hWindow = CreateWindow(Name, m_projectName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left,
		rc.bottom - rc.top, NULL, NULL, hInstance, NULL);

	// Check if failed
	if (!m_hWindow) return E_FAIL;

	// Show window
	ShowWindow(m_hWindow, nCmdShow);

	return S_OK;
}

//####################################################################################
// Window messages
//####################################################################################
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	// Draws window background
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	// When the window is destroyed/application is quit
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		// When the window is resized
	case WM_SIZE:
		m_screenWidth = LOWORD(lParam);
		m_screenHeight = HIWORD(lParam);
		m_updateViewport = true;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


//####################################################################################
// Get methods
//####################################################################################
#pragma region Get Methods

HWND Window::GetWindow(void)
{
	return m_hWindow;
}

HINSTANCE Window::GetHInstance(void)
{
	return m_hInstance;
}

bool Window::GetUpdateViewport(void)
{
	return m_updateViewport;
}

LONG Window::GetScreenWidth(void)
{
	return m_screenWidth;
}

LONG Window::GetScreenHeight(void)
{
	return m_screenHeight;
}
#pragma endregion


#pragma region Set Methods

void Window::SetUpdateViewport(bool shouldUpdate)
{
	m_updateViewport = shouldUpdate;
}

#pragma endregion