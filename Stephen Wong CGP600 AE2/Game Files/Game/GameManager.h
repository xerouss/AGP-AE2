// *********************************************************
//	Name:			Stephen Wong
//	File:			GameManager.h
//	Last Updated:	30/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include <d3d11.h>
#include "Level.h"
#include "Input.h"
#include "User Interface\HUD.h"
#include "User Interface\PauseMenu.h"
#include "Time.h"

#pragma endregion

#pragma region Constants
// TODO: MOVE TO HUD???
const float scoreHUDXPos = -1;
const float scoreHUDYPos = 1;
const float scoreHUDTextSize = 0.2f;

const float healthHUDXPos = -1;
const float healthHUDYPos = 0.8f;
const float healthHUDTextSize = 0.2f;

const float timerHUDXPos = -1;
const float timerHUDYPos = 0.6f;
const float timerHUDTextSize = 0.2f;

const float defaultProjectionFOVAngleRadian = 0.785398f; // 45 in degrees
const float defaultNearClippingPlaneZ = 1.0f;
const float defaultFarClippingPlaneZ = 100.0f;
const int convertFromScreenToWorldAmount = 100;
const float movementAmount = 1;
#pragma endregion

enum GameStates
{
	PLAYING, PAUSED, GAMEOVER, NUMOFGAMESTATES
};

class GameManager
{
private:

	Level* m_pLevel;
	Input* m_pInput;
	HUD* m_pHUD;
	Time* m_pTime;
	PauseMenu* m_pPauseMenu;
	int m_score = 0;
	// Save the screen width and height for the user interface
	float m_screenWidth;
	float m_screenHeight;
	GameStates m_currentGameState;

	// Don't delete these since they are passed from another class
	ID3D11Device* m_pD3Device;
	ID3D11RenderTargetView* m_pBackBuffer;
	IDXGISwapChain* m_pSwapChain;
	ID3D11DeviceContext* m_pImmediateContext;
	ID3D11DepthStencilView* m_pZBuffer;
public:
	GameManager(ID3D11Device* device, ID3D11RenderTargetView* backBuffer,
		IDXGISwapChain* swapChain, ID3D11DeviceContext* immediateContext,
		ID3D11DepthStencilView* ZBuffer);
	~GameManager();

	// Initialise methods
	HRESULT InitialiseLevel(void);
	HRESULT InitialiseInput(HINSTANCE hInstance, HWND hWND);

	// Does not return HRESULT since there is nothing that can fail
	void InitialiseHUD(void);

	void Update(void);
	void Render(void);

	void SetZBuffer(ID3D11DepthStencilView* zbuffer);
	void SetProjectionMatrix(float screenWidth, float screenHeight);
	void SetPauseActive(void);
};

