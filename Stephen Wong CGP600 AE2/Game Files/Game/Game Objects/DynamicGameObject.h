// *********************************************************
//	Name:			Stephen Wong
//	File:			DynamicGameObject.h
//	Last Updated:	04/01/2018
//	Project:		CGP600 AE2
// *********************************************************

#pragma once


#pragma region Includes

#include "StaticGameObject.h"

#pragma endregion

const float defaultSpeed = 0;

class DynamicGameObject : public StaticGameObject
{
protected:
	float m_movementSpeed;

public:
	DynamicGameObject();
	DynamicGameObject(float speed, float xPos, float yPos, float zPos);
	DynamicGameObject(float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle);
	DynamicGameObject(float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale);

	void InitialiseDynamicGameObject(float speed);
	void LookAtXZ(float worldX, float worldZ);
	void LookAtXYZ(float worldX, float worldY, float worldZ);
	void MoveForward(float distance, StaticGameObject* rootNode);
	virtual void SetNewForwardPosition(float distance);
	virtual void MoveForwardIncludingY(float distance);
	bool UpdateTransformAndCheckCollision(float oldValue, float &valueThatWasChanged, StaticGameObject* rootNode);
	virtual void ThisCollidesWithAnotherObject(StaticGameObject* object); // When this object collides with any object

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