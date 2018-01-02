// *********************************************************
//	Name:			Stephen Wong
//	File:			GameOverMenu.h
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "Menu.h"

#pragma endregion

#pragma region Constants

const float retryButtonX = -1;
const float retryButtonY = 0.4f;
const float retryButtonSize = 0.2f;
const string gameOverMenuTitle = "GAME OVER";

#pragma endregion


class GameOverMenu : public Menu
{
private:
	Button* m_pRetryButton;

public:
	GameOverMenu(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	~GameOverMenu();

	bool CheckRetryButtonIsPressed(float mouseXPosition, float mouseYPosition,
		float screenWidth, float screenHeight);

	void Render(void);
};