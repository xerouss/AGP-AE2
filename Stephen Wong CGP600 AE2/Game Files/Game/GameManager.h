// *********************************************************
//	Name:			Stephen Wong
//	File:			GameManager.h
//	Last Updated:	05/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include <d3d11.h>
#include "Level.h"

#pragma endregion

class GameManager
{
private:
	// Don't delete these since they are passed from another class
	ID3D11Device* m_pD3DDevice; // To pass to the level
	ID3D11RenderTargetView* m_pBackBuffer;
	IDXGISwapChain* m_pSwapChain;
	ID3D11DeviceContext* m_pImmediateContext;
	Level* m_pLevel;

public:
	GameManager(ID3D11Device* device, ID3D11RenderTargetView* backBuffer,
	IDXGISwapChain* swapChain, ID3D11DeviceContext* immediateContext);
	~GameManager();

	HRESULT InitialiseLevel(void);
	void Update(void);
	void Render(void);
};

