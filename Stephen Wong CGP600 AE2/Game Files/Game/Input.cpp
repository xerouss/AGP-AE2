// *********************************************************
//	Name:			Stephen Wong
//	File:			Input.cpp
//	Last Updated:	30/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Input.h"

#pragma endregion

//####################################################################################
// Destructor
//####################################################################################
Input::~Input()
{
	if (m_pMouseDevice)
	{
		m_pMouseDevice->Unacquire();
		m_pMouseDevice->Release();
	}

	if (m_pKeyboardDevice)
	{
		m_pKeyboardDevice->Unacquire();
		m_pKeyboardDevice->Release();
	}
	if (m_pDirectInput) m_pDirectInput->Release();
}

//####################################################################################
// Start up direct input
//####################################################################################
HRESULT Input::InitialiseDirectInput(HINSTANCE hInstance, HWND hWND)
{
	HRESULT hr = S_OK;

	// Initialise direct input
	hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL);

	m_window = hWND;

	return hr; // Will return failed if set up failed
}

//####################################################################################
// Start up the input for keyboard
//####################################################################################
HRESULT Input::InitialiseKeyboardInput(void)
{
	HRESULT hr = S_OK;

	ZeroMemory(m_keyboardKeysState, sizeof(m_keyboardKeysState)); // Clear the array

	// Initialise the keyboard device
	hr = m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboardDevice, NULL);
	if (FAILED(hr)) return hr;

	// Use format to set up the keyboard device
	hr = m_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) return hr;

	// Set the behaviour so it can interact with other apps
	// The foreground only gets input from active window
	// While the nonexclusive will share the device with others
	hr = m_pKeyboardDevice->SetCooperativeLevel(m_window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) return hr;

	// Start the keyboard device
	hr = m_pKeyboardDevice->Acquire();
	return hr; // Will return failed if keyboard failed
}

//####################################################################################
// Start up the mouse input
//####################################################################################
HRESULT Input::InitialiseMouse(void)
{
	HRESULT hr = S_OK;

	// Initialise the mouse device
	hr = m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pMouseDevice, NULL);
	if (FAILED(hr)) return hr;

	// Use format to set up the mouse device
	hr = m_pMouseDevice->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr)) return hr;

	// Set the behaviour so it can interact with other apps
	// The foreground only gets input from active window
	// While the nonexclusive will share the device with others
	hr = m_pMouseDevice->SetCooperativeLevel(m_window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) return hr;

	// Start the mouse device
	hr = m_pMouseDevice->Acquire();

	return hr; // Will return failed if mouse failed
}

//####################################################################################
// Get inputs from the player
//####################################################################################
void Input::ReadInputStates(void)
{
	HRESULT hr;

	// Read the keyboard state
	hr = m_pKeyboardDevice->GetDeviceState(sizeof(m_keyboardKeysState),
		(LPVOID)&m_keyboardKeysState);

	if (FAILED(hr))
	{
		// Get the keyboard access again if lost
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_pKeyboardDevice->Acquire();
		}
	}

	// Read Mouse State
	hr = m_pMouseDevice->GetDeviceState(sizeof(m_mouseState), (LPVOID)&m_mouseState);

	if (FAILED(hr))
	{
		// Get the mouse access again if lost
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_pMouseDevice->Acquire();
		}
	}
}

//####################################################################################
// Check if the passed key is being held down
//####################################################################################
bool Input::IsKeyDown(unsigned char DI_keycode)
{
	// Check for key input using bitwise compare
	// Return constantly if the button is being held down
	// & is a bitwise AND
	// Using * with 0x80 returns the high order bit.
	// If the bit is 1 the key is down while otherwise it is up
	return m_keyboardKeysState[DI_keycode] & getHighOrderBit;
}

//####################################################################################
// Check if the passed key is being pressed
//####################################################################################
bool Input::IsKeyPressed(unsigned char DI_keycode)
{
	// The key has been pressed so prevent constant action while pressed
	if (!m_keyboardKeysPressedState[DI_keycode] && IsKeyDown(DI_keycode))
	{
		m_keyboardKeysPressedState[DI_keycode] = true;
		return true; // Return its being pressed
	}
	// Key has been released so free the key
	else if (m_keyboardKeysPressedState[DI_keycode] && !IsKeyDown(DI_keycode))
	{
		m_keyboardKeysPressedState[DI_keycode] = false;
	}

	return false;
}

//####################################################################################
// Return if the left mouse button was pressed
//####################################################################################
bool Input::IsMouseLeftButtonDown(void)
{
	return m_mouseState.rgbButtons[leftMouseButton];
}

//####################################################################################
// Get the change in position of the mouse
//####################################################################################
long Input::GetMousePositionChange(bool CheckXAxis)
{
	long change;

	if (CheckXAxis)
	{
		// Return the change in the mouse X position from the previous position
		// They are added onto each other because the start position is 0
		// When moving in left/right it will increase or decrease so the change is added onto the position
		// E.g. 0 + 4 = the new mouse position
		// If the mouse stays in the same place the mouse state will be 0
		change = m_previousMouseXPos + m_mouseState.lX;
		m_previousMouseXPos = m_mouseState.lX; // Save position so it can be used in the next frame
		return change;
	}
	else
	{
		// Return the change in the mouse Y position from the previous position
		change = m_previousMouseYPos + m_mouseState.lY;
		m_previousMouseYPos = m_mouseState.lY; // Save position so it can be used in the next frame
		return change;
	}
}

//####################################################################################
// Get the current mouse position
//####################################################################################
POINT Input::GetMousePosition(void)
{
	// Get the mouse postion
	POINT mousePosition;
	GetCursorPos(&mousePosition);

	// Convert the position from screen to the window
	ScreenToClient(m_window, &mousePosition);

	// Return the position
	// Should return (0,0) if failed
	return mousePosition;
}

//####################################################################################
// Get the current X mouse position
//####################################################################################
float Input::GetXMousePosition(void)
{
	// Get the current mouse position
	POINT mousePosition = GetMousePosition();

	// Return the x value
	return ((float)mousePosition.x);
}

//####################################################################################
// Get the current Y mouse position
//####################################################################################
float Input::GetYMousePosition(void)
{
	// Get the current mouse position
	POINT mousePosition = GetMousePosition();

	// Return the y value
	return ((float)mousePosition.y);
}
