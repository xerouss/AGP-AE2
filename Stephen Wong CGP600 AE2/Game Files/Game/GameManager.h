// *********************************************************
//	Name:			Stephen Wong
//	File:			GameManager.h
//	Last Updated:	09/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include <d3d11.h>
#include "Level.h"
#include "Input.h"

#pragma endregion

class GameManager
{
private:
	// Don't delete these since they are passed from another class
	//ID3D11Device* m_pD3DDevice; // Made this a parameter for initialise level since its only used there
	ID3D11RenderTargetView* m_pBackBuffer;
	IDXGISwapChain* m_pSwapChain;
	ID3D11DeviceContext* m_pImmediateContext;
	ID3D11DepthStencilView* m_pZBuffer;

	Level* m_pLevel;
	Input* m_pInput;

public:
	GameManager(ID3D11RenderTargetView* backBuffer,
	IDXGISwapChain* swapChain, ID3D11DeviceContext* immediateContext,
		ID3D11DepthStencilView* ZBuffer);
	~GameManager();

	HRESULT InitialiseLevel(ID3D11Device* device);
	HRESULT InitialiseInput(HINSTANCE hInstance, HWND hWND);
	void Update(void);
	void Render(void);
};

