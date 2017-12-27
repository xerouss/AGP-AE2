// *********************************************************
//	Name:			Stephen Wong
//	File:			Camera.h
//	Last Updated:	27/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "DynamicGameObject.h"
#include "../Time.h"

#pragma endregion


#pragma region Constants

const float defaultDeltaPos = 0;
const float DegreesToRadians = 0.01745329251f;
const int defaultMaxHealth = 100;
const int timeBetweenHits = 2;

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

	int m_currentHealth = defaultMaxHealth;
	int m_timeAtCollision = 0;

	Time* m_pTime;
public:
	Camera(Time* time);
	Camera(Time* time, float speed, float xPos, float yPos, float zPos);
	Camera(Time* time, float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle);
	Camera(Time* time, float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale);
	// ~Camera();

	void InitialiseCamera(Time* time);

	virtual void SetNewForwardPosition(float distance);
	void Strafe(float distance, StaticGameObject* rootNode);
	//void MoveForwardIncludingY(float distance);

	bool IncrementXAngle(float increaseAmount, StaticGameObject* rootNode);
	bool IncrementYAngle(float increaseAmount, StaticGameObject* rootNode);
	bool IncrementZAngle(float increaseAmount, StaticGameObject* rootNode);
	virtual void ThisCollidesWithAnotherObject(StaticGameObject* object);
	XMMATRIX GetViewMatrix(void);
	int GetCurrentHealth(void);
};