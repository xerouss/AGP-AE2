// *********************************************************
//	Name:			Stephen Wong
//	File:			HUD.h
//	Last Updated:	18/12/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include "Text2D.h"

#pragma endregion

const UINT blendStateSampleMask = 0xffffffff;

class HUD
{
private:
	Text2D* m_scoreText;
	ID3D11BlendState* m_pAlphaBlendEnable;
	ID3D11BlendState* m_pAlphaBlendDisable;

	// Don't delete these pointers since they are passed down
	// These are stored in case more text are added in the future during the game
	ID3D11Device* m_pD3DDevice;
	ID3D11DeviceContext* m_pImmediateContext; // This is needed for the transparent text
public:
	HUD(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	~HUD();

	void Render(void);

	// Will need to be called every frame since it is deleted after use
	void SetScoreText(string score, float x, float y, float size);
	void InitialiseTransparency(void);
};