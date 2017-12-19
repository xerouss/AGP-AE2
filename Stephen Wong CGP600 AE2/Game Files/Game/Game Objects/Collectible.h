// *********************************************************
//	Name:			Stephen Wong
//	File:			Collectible.h
//	Last Updated:	19/12/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include "StaticGameObject.h"

#pragma endregion
 
class Collectible: public StaticGameObject
{
private:
	int* m_pScore; // Don't need to delete because was not created with new

public:
	Collectible(int* score);
	Collectible(int* score, float xPos, float yPos, float zPos);
	Collectible(int* score, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle);
	Collectible(int* score, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale);

	void InitialiseCollectible(int* score);
	virtual void CollisionEffect(float oldValue, float &valueThatWasChanged, StaticGameObject* object);
};