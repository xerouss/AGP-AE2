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
	//~DynamicGameObject();

	void LookAtXZ(float worldX, float worldZ);
	void LookAtXYZ(float worldX, float worldY, float worldZ);
	void MoveForward(float distance);
	void MoveForwardIncludingY(float distance);

#pragma region Increment Methods

	bool IncrementXPos(float increaseAmount, StaticGameObject* rootNode);
	bool IncrementYPos(float increaseAmount, StaticGameObject* rootNode);
	bool IncrementZPos(float increaseAmount, StaticGameObject* rootNode);

	bool IncrementXAngle(float increaseAmount, StaticGameObject* rootNode);
	bool IncrementYAngle(float increaseAmount, StaticGameObject* rootNode);
	bool IncrementZAngle(float increaseAmount, StaticGameObject* rootNode);

	bool IncrementScale(float increaseAmount, StaticGameObject* rootNode);

#pragma endregion
};