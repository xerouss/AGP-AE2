// *********************************************************
//	Name:			Stephen Wong
//	File:			DynamicGameObject.h
//	Last Updated:	21/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once


#pragma region Includes

#include "StaticGameObject.h"

#pragma endregion

class DynamicGameObject : public StaticGameObject
{
protected:
	float m_movementSpeed;

public:
	DynamicGameObject();
	DynamicGameObject(float speed, float xPos, float yPos, float zPos);
	DynamicGameObject(float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle);
	DynamicGameObject(float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale);
	//~DynamicGameObject();

	void InitialiseDynamicGameObject(float speed);
	void LookAtXZ(float worldX, float worldZ);
	void LookAtXYZ(float worldX, float worldY, float worldZ);
	virtual void MoveForward(float distance);
	virtual void MoveForwardIncludingY(float distance);
	bool UpdateTransformAndCheckCollision(float oldValue, float &valueThatWasChanged, StaticGameObject* rootNode);

#pragma region Increment Methods

	bool IncrementXPos(float increaseAmount, StaticGameObject* rootNode);
	bool IncrementYPos(float increaseAmount, StaticGameObject* rootNode);
	bool IncrementZPos(float increaseAmount, StaticGameObject* rootNode);

	virtual bool IncrementXAngle(float increaseAmount, StaticGameObject* rootNode);
	virtual bool IncrementYAngle(float increaseAmount, StaticGameObject* rootNode);
	virtual bool IncrementZAngle(float increaseAmount, StaticGameObject* rootNode);

	bool IncrementScale(float increaseAmount, StaticGameObject* rootNode);

#pragma endregion

	float GetMovementSpeed(void);
	void SetMovementSpeed(float speed);
};