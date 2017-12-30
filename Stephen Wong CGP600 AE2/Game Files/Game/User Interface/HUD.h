// *********************************************************
//	Name:			Stephen Wong
//	File:			HUD.h
//	Last Updated:	29/12/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include "Text2D.h"
#include "UserInterface.h"

#pragma endregion

class HUD : public UserInterface
{
private:
	Text2D* m_pScoreText;
	Text2D* m_pHealthText;
	Text2D* m_pTimerText;
public:
	HUD(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	~HUD();

	void Render(void);

	// Will need to be called every frame since it is deleted after use
	void SetScoreText(string score, float x, float y, float size);
	void SetHealthText(string health, float x, float y, float size);
	void SetTimerText(string time, float x, float y, float size);
};