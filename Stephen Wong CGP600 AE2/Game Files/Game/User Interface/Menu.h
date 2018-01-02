// *********************************************************
//	Name:			Stephen Wong
//	File:			Nenu.h
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "UserInterface.h"
#include "Text2D.h"
#include "Button.h"

#pragma endregion

#pragma region Constants

const float titleTextTitleX = -1;
const float titleTextTitleY = 1;
const float titleTextTitleSize = 0.2f;

const float exitButtonX = -1;
const float exitButtonY = 0;
const float exitButtonSize = 0.2f;

#pragma endregion


class Menu : public UserInterface
{
private:
	string m_pTextTitleString;
	Text2D* m_pTextTitle;
	Button* m_pExitButton;
public:
	Menu(ID3D11Device* device, ID3D11DeviceContext* immediateContext, string titleText);
	~Menu();
	virtual void Render(void);
	bool CheckExitButtonIsPressed(float mouseXPosition, float mouseYPosition,
		float screenWidth, float screenHeight);
};