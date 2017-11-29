//// *********************************************************
////	Name:			Stephen Wong
////	File:			Window.cpp
////	Last Updated:	29/11/2017
////	Project:		CGP600 AE2
//// *********************************************************
//
////////////////////////////////////////////////////////////////////////////////////////
//// All The includes for the file
////////////////////////////////////////////////////////////////////////////////////////
//#pragma region Includes
//
//#include "Window.h"
//
//#pragma endregion
//
//HRESULT Window::InitialiseWindow(HINSTANCE hInstance, int nCmdShow)
//{
//	// Give your app window your own name
//	char Name[100] = "Stephen Wong\0";
//
//	// Register class
//	WNDCLASSEX wcex = { 0 };
//	wcex.cbSize = sizeof(WNDCLASSEX);
//	wcex.style = CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc = WndProc; // <- ERROR HERE
//	wcex.hInstance = hInstance;
//	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wcex.lpszClassName = Name;
//
//	if (!RegisterClassEx(&wcex)) return E_FAIL;
//
//	// Create window
//	m_hInstance = hInstance;
//
//	// Change screen width and height to a long to prevent conversion errors
//	// Can't change the variable to long since when getting the mouse position they require a float
//	RECT rc = { 0, 0, m_screenWidth, m_screenHeight};
//	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
//	m_hWindow = CreateWindow(Name, m_projectName, WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left,
//		rc.bottom - rc.top, NULL, NULL, hInstance, NULL);
//
//	if (!m_hWindow)
//		return E_FAIL;
//
//	ShowWindow(m_hWindow, nCmdShow);
//
//	return S_OK;
//}
//
//LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	PAINTSTRUCT ps;
//	HDC hdc;
//
//	switch (message)
//	{
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		EndPaint(hWnd, &ps);
//		break;
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//
//	return LRESULT();
//}