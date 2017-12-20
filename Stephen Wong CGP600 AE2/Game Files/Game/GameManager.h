// *********************************************************
//	Name:			Stephen Wong
//	File:			GameManager.h
//	Last Updated:	20/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include <d3d11.h>
#include "Level.h"
#include "Input.h"
#include "HUD.h"

#pragma endregion

#pragma region Constants

const float scoreHUDXPos = -1;
const float scoreHUDYPos = 1;
const float scoreHUDTextSize = 0.2f;
const float defaultProjectionFOVAngleRadian = 0.785398f; // 45 in degrees
const float defaultNearClippingPlaneZ = 1.0f;
const float defaultFarClippingPlaneZ = 100.0f;
#pragma endregion

class GameManager
{
private:

	Level* m_pLevel;
	Input* m_pInput;
	HUD* m_HUD;
	int m_score = 0;

	// Don't delete these since they are passed from another class
	ID3D11RenderTargetView* m_pBackBuffer;
	IDXGISwapChain* m_pSwapChain;
	ID3D11DeviceContext* m_pImmediateContext;
	ID3D11DepthStencilView* m_pZBuffer;
public:
	GameManager(ID3D11RenderTargetView* backBuffer,
		IDXGISwapChain* swapChain, ID3D11DeviceContext* immediateContext,
		ID3D11DepthStencilView* ZBuffer);
	~GameManager();

	// Initialise methods
	HRESULT InitialiseLevel(ID3D11Device* device);
	HRESULT InitialiseInput(HINSTANCE hInstance, HWND hWND);

	// Does not return HRESULT since there is nothing that can fail
	void InitialiseHUD(ID3D11Device* device);

	void Update(void);
	void Render(void);

	void SetZBuffer(ID3D11DepthStencilView* zbuffer);
	void SetProjectionMatrix(float screenWidth, float screenHeight);
};

