// *********************************************************
//	Name:			Stephen Wong
//	File:			PauseMenu.h
//	Last Updated:	30/12/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include "UserInterface.h"
#include "Text2D.h"
#include "Button.h"

#pragma endregion

#pragma region Constants

const string pauseTextTitleString = "PAUSED";
const float pauseTextTitleX = -1;
const float pauseTextTitleY = 1;
const float pauseTextTitleSize = 0.4f;

const float resumeButtonX = -1;
const float resumeButtonY = 0.4f;
const float resumeButtonSize = 0.2f;

const float exitButtonX = -1;
const float exitButtonY = 0;
const float exitButtonSize = 0.2f;

#pragma endregion

class PauseMenu : public UserInterface
{
private:
	Text2D* m_pPauseTextTitle;
	Button* m_pResumeButton;
	Button* m_pExitButton;
public:
	PauseMenu(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	~PauseMenu();
	
	bool CheckResumeButtonIsPressed(float mouseXPosition, float mouseYPosition, 
		float screenWidth, float screenHeight);
	bool CheckExitButtonIsPressed(float mouseXPosition, float mouseYPosition, 
		float screenWidth, float screenHeight);

	void Render(void);

};
