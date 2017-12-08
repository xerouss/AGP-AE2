// *********************************************************
//	Name:			Stephen Wong
//	File:			DynamicGameObject.h
//	Last Updated:	07/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once


#pragma region Includes

#include "StaticGameObject.h"

#pragma endregion


class DynamicGameObject : public StaticGameObject
{
private:


public:
	DynamicGameObject();
	DynamicGameObject(float xPos, float yPos, float zPos);
	DynamicGameObject(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle);
	DynamicGameObject(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale);
	//~DynamicGameObject();

	void LookAtXZ(float worldX, float worldZ);
	void LookAtXYZ(float worldX, float worldY, float worldZ);
	virtual void MoveForward(float distance);
	virtual void MoveForwardIncludingY(float distance);

#pragma region Increment Methods

	bool IncrementXPos(float increaseAmount, StaticGameObject* rootNode);
	bool IncrementYPos(float increaseAmount, StaticGameObject* rootNode);
	bool IncrementZPos(float increaseAmount, StaticGameObject* rootNode);

	virtual bool IncrementXAngle(float increaseAmount, StaticGameObject* rootNode);
	virtual bool IncrementYAngle(float increaseAmount, StaticGameObject* rootNode);
	virtual bool IncrementZAngle(float increaseAmount, StaticGameObject* rootNode);

	bool IncrementScale(float increaseAmount, StaticGameObject* rootNode);

#pragma endregion
};