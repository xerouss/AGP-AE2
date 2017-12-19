// *********************************************************
//	Name:			Stephen Wong
//	File:			Collectible.cpp
//	Last Updated:	19/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Collectible.h"

#pragma endregion

//####################################################################################
// Constructors
//####################################################################################
Collectible::Collectible(int* score) : StaticGameObject()
{
	// Call static game object's constructor
	InitialiseCollectible(score);
}

Collectible::Collectible(int* score, float xPos, float yPos, float zPos) :
	StaticGameObject(xPos, yPos, zPos)

{
	// Call static game object's constructor
	InitialiseCollectible(score);
}

Collectible::Collectible(int* score, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle) :
	StaticGameObject(xPos, yPos, zPos, xAngle, yAngle, zAngle)
{
	// Call static game object's constructor
	InitialiseCollectible(score);
}

Collectible::Collectible(int* score, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale) :
	StaticGameObject(xPos, yPos, zPos, xAngle, yAngle, zAngle, scale)
{
	// Call static game object's constructor
	InitialiseCollectible(score);
}

//####################################################################################
// Set up the collectible object
//####################################################################################
void Collectible::InitialiseCollectible(int* score)
{
	// Delete after being collected to stop the player getting it multiple times
	m_deleteAfterCollision = true; 
	m_pScore = score;
	SetGameObjectType(COLLECTIBLE);
}

//####################################################################################
// What happens on collision
//####################################################################################
void Collectible::CollisionEffect(float oldValue, float &valueThatWasChanged, StaticGameObject* object)
{
	// Don't move the object back because the collectible should be able to be walked through
	// Only increase the score if its the camera/player
	// This prevents other object colliding with it and increasing the score
	if (object->GetGameObjectType() == CAMERA)
	{
		(*m_pScore)++; // Increase the score
	}
}
