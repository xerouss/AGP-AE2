// *********************************************************
//	Name:			Stephen Wong
//	File:			PauseMenu.h
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include "Menu.h"

#pragma endregion

#pragma region Constants

const float resumeButtonX = -1;
const float resumeButtonY = 0.4f;
const float resumeButtonSize = 0.2f;
const string pauseMenuTitle = "PAUSED";

#pragma endregion

class PauseMenu : public Menu
{
private:
	Button* m_pResumeButton;
public:
	PauseMenu(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	~PauseMenu();
	
	bool CheckResumeButtonIsPressed(float mouseXPosition, float mouseYPosition, 
		float screenWidth, float screenHeight);

	void Render(void);
};
