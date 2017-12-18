// *********************************************************
//	Name:			Stephen Wong
//	File:			Collectible.cpp
//	Last Updated:	18/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Collectible.h"

#pragma endregion

Collectible::Collectible(int* score) : StaticGameObject()
{
	SetScorePointer(score);
}

Collectible::Collectible(int* score, float xPos, float yPos, float zPos) :
	StaticGameObject(xPos, yPos, zPos)

{
	SetScorePointer(score);
}

Collectible::Collectible(int* score, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle) :
	StaticGameObject(xPos, yPos, zPos, xAngle, yAngle, zAngle)
{
	SetScorePointer(score);
}

Collectible::Collectible(int* score, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale) :
	StaticGameObject(xPos, yPos, zPos, xAngle, yAngle, zAngle, scale)
{
	SetScorePointer(score);
}

void Collectible::SetScorePointer(int* score)
{
	m_pScore = score;
}

void Collectible::CollisionEffect(float oldValue, float &valueThatWasChanged)
{
	// Don't move the object back because the collectible should be able to be walked through
	(*m_pScore)++; // Increase the score

	// TODO: NEED TO DELETE THE COLLECTIBLE AFTER COLLECTION


}
