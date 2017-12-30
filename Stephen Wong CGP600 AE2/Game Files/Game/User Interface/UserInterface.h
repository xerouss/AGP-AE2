// *********************************************************
//	Name:			Stephen Wong
//	File:			UserInterface.h
//	Last Updated:	29/12/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include <d3d11.h>

#pragma endregion

#pragma region Constants

// Used when doing transparency which the child classes will use
const UINT blendStateSampleMask = 0xffffffff;

#pragma endregion


class UserInterface
{
protected:
	ID3D11BlendState* m_pAlphaBlendEnable;
	ID3D11BlendState* m_pAlphaBlendDisable;
	// Don't delete this because it is passed down
	ID3D11DeviceContext* m_pImmediateContext; // This is needed for the transparent text
public:
	UserInterface(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	~UserInterface();
	virtual void Render(void);
	void SetTransparencyActive(bool active);
	void InitialiseTransparency(ID3D11Device* device);
};