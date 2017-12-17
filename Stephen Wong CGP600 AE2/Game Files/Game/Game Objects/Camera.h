// *********************************************************
//	Name:			Stephen Wong
//	File:			Camera.h
//	Last Updated:	07/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "DynamicGameObject.h"

#pragma endregion


class Camera: public DynamicGameObject
{
private:
	float m_deltaXPos;
	float m_deltaYPos;
	float m_deltaZPos;

	XMVECTOR m_position;
	XMVECTOR m_lookAtPos;
	XMVECTOR m_up;

public:
	Camera();
	Camera(float xPos, float yPos, float zPos);
	Camera(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle);
	Camera(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale);
	// ~Camera();

	void SetDefaultProperties(void);

	void MoveForward(float distance);
	void Strafe(float distance);
	//void MoveForwardIncludingY(float distance);

	bool IncrementXAngle(float increaseAmount, StaticGameObject* rootNode);
	bool IncrementYAngle(float increaseAmount, StaticGameObject* rootNode);
	bool IncrementZAngle(float increaseAmount, StaticGameObject* rootNode);

	XMMATRIX GetViewMatrix(void);
};