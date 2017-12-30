// *********************************************************
//	Name:			Stephen Wong
//	File:			Input.h
//	Last Updated:	30/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include <dinput.h>

#pragma endregion

#pragma region Constants

const int leftMouseButton = 0;
const int getHighOrderBit = 0x80;
const bool failedGetMousePosition = false;

#pragma endregion


class Input
{
private:
	IDirectInput8* m_pDirectInput; // Pointer to dinput interface
	IDirectInputDevice8* m_pKeyboardDevice; // Pointer to keyboard device
	unsigned char m_keyboardKeysState[256]; // Stores states of all keyboard keys
	bool m_keyboardKeysPressedState[256]; // Stores if the key is currently pressed down
	IDirectInputDevice8* m_pMouseDevice; // Pointer to mouse device
	HWND m_window;
	/*
	 DIMOUSESTATE structure:
	 LONG    lX; - X pos
	 LONG    lY; - Y pos
	 LONG    lZ; - Mouse wheel
	 BYTE    rgbButtons[4];
	 0 = Left mouse button
	 1 = Right mouse button
	 2 = Centre mouse button
	 3 = Other buttons
	*/
	DIMOUSESTATE m_mouseState; // Stores mouse state

	// Used to save the position of the mouse from the previous frame so movement can be worked out
	long m_previousMouseXPos = 0;
	long m_previousMouseYPos = 0;

public:
	~Input();

	HRESULT InitialiseDirectInput(HINSTANCE hInstance, HWND hWND);
	HRESULT InitialiseKeyboardInput(void);
	// TODO: This is separate from initialize input since we need to recall this when changing screen size?
	HRESULT InitialiseMouse(void);
	void ReadInputStates(void);
	bool IsKeyDown(unsigned char DI_keycode);
	bool IsKeyPressed(unsigned char DI_keycode);
	bool IsMouseLeftButtonDown(void);
	long GetMousePositionChange(bool X);

	POINT GetMousePosition(void);
	float GetXMousePosition(void);
	float GetYMousePosition(void);
};