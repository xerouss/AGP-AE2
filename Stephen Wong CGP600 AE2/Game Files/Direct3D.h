// *********************************************************
//	Name:			Stephen Wong
//	File:			Direct3D.h
//	Last Updated:	09/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include <d3d11.h>

#pragma endregion

class Direct3D
{
private:
	D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device* m_pD3DDevice = NULL;
	ID3D11DeviceContext* m_pImmediateContext = NULL;
	IDXGISwapChain* m_pSwapChain = NULL;
	ID3D11RenderTargetView* m_pBackBufferRenderTargetView = NULL;
	ID3D11DepthStencilView* m_pZBuffer;
	UINT m_descCount; // Store the swap chain desc count

public:
	//Direct3D();
	~Direct3D();

	HRESULT InitialiseD3D(HWND hWindow);
	HRESULT CreateZBuffer(UINT descCount, UINT width, UINT height, HRESULT hr);

#pragma region Get Methods

	ID3D11Device* GetD3DDevice(void);
	ID3D11RenderTargetView* GetBackBuffer(void);
	IDXGISwapChain* GetSwapChain(void);
	ID3D11DeviceContext* GetImmediateContext(void);
	ID3D11DepthStencilView* GetZBuffer(void);

#pragma endregion
};
