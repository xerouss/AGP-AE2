// *********************************************************
//	Name:			Stephen Wong
//	File:			GameManager.h
//	Last Updated:	30/11/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include <d3d11.h>

#pragma endregion

class GameManager
{
private:
	

public:
	//GameManager();
	//~GameManager();

	// TODO: MAKE THESE ATTRIBUTES
	void Render(ID3D11RenderTargetView* backBuffer, 
		IDXGISwapChain* swapChain, ID3D11DeviceContext* immediateContext);
};

