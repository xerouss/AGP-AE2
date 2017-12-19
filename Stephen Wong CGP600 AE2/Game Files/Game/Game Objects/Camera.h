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


const float defaultMovementSpeed = 0.001f;

class Camera: public DynamicGameObject
{
private:
	float m_deltaXPos;
	float m_deltaYPos;
	float m_deltaZPos;

	XMVECTOR m_position;
	XMVECTOR m_lookAtPos;
	XMVECTOR m_up;

	float m_movementSpeed = defaultMovementSpeed;
public:
	Camera();
	Camera(float xPos, float yPos, float zPos);
	Camera(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle);
	Camera(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale);
	// ~Camera();

	void SetDefaultProperties(void);

	void MoveForward(float distance, StaticGameObject* rootNode);
	void Strafe(float distance, StaticGameObject* rootNode);
	//void MoveForwardIncludingY(float distance);

	bool IncrementXAngle(float increaseAmount, StaticGameObject* rootNode);
	bool IncrementYAngle(float increaseAmount, StaticGameObject* rootNode);
	bool IncrementZAngle(float increaseAmount, StaticGameObject* rootNode);

	XMMATRIX GetViewMatrix(void);

	float GetMovementSpeed(void);
	void SetMovementSpeed(float speed);
};