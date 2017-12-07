// *********************************************************
//	Name:			Stephen Wong
//	File:			DynamicGameObject.cpp
//	Last Updated:	07/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "DynamicGameObject.h"

#pragma endregion

DynamicGameObject::DynamicGameObject() : StaticGameObject()
{
}

void DynamicGameObject::LookAtXZ(float worldX, float worldZ)
{
	// Use atan2 since the value could be 0

	float dx = worldX - m_xPos;
	float dz = worldZ - m_zPos;

	m_yAngle = atan2(dx, dz);
}

void DynamicGameObject::LookAtXYZ(float worldX, float worldY, float worldZ)
{
	// Work out the differences between the positions
	float dy = worldY - m_yPos;
	float dx = worldX - m_xPos;
	float dz = worldZ - m_zPos;

	// Use atan2 since the value could be 0
	// Use Pythagoras to work out the distance between the object on x and z
	float distanceXZ = sqrt(pow(dx, 2) + pow(dz, 2));

	m_xAngle = -atan2(dy, distanceXZ);// *180.0f / XM_PI;

	LookAtXZ(worldX, worldZ);
}

void DynamicGameObject::MoveForward(float distance)
{
	// TODO: CONVERT TO RADIANS/DEGREES?
	// Don't need to convert to radians since its already radians
	m_xPos += sin(m_yAngle) * distance;
	m_zPos += cos(m_yAngle) * distance;
}

void DynamicGameObject::MoveForwardIncludingY(float distance)
{
	float cosXAngle = cos(m_xAngle);
	m_xPos += sin(m_yAngle) * distance * cosXAngle;
	m_yPos += -sin(m_xAngle) * distance;
	m_zPos += cos(m_yAngle) * distance * cosXAngle;
}

//////////////////////////////////////////////////////////////////////////////////////
// Increment Methods
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Increment Methods

bool DynamicGameObject::IncrementXPos(float increaseAmount, StaticGameObject* rootNode)
{
	float oldValue = m_xPos;
	m_xPos += increaseAmount;

	return UpdateTransformAndCheckCollision(oldValue, m_xPos, rootNode);
}

bool DynamicGameObject::IncrementYPos(float increaseAmount, StaticGameObject* rootNode)
{
	float oldValue = m_yPos;
	m_yPos += increaseAmount;

	return UpdateTransformAndCheckCollision(oldValue, m_yPos, rootNode);
}

bool DynamicGameObject::IncrementZPos(float increaseAmount, StaticGameObject* rootNode)
{
	float oldValue = m_zPos;
	m_zPos += increaseAmount;

	return UpdateTransformAndCheckCollision(oldValue, m_zPos, rootNode);
}

bool DynamicGameObject::IncrementXAngle(float increaseAmount, StaticGameObject* rootNode)
{
	float oldValue = m_xAngle;
	m_xAngle += increaseAmount;

	return UpdateTransformAndCheckCollision(oldValue, m_xAngle, rootNode);
}

bool DynamicGameObject::IncrementYAngle(float increaseAmount, StaticGameObject* rootNode)
{
	float oldValue = m_yAngle;
	m_yAngle += increaseAmount;

	return UpdateTransformAndCheckCollision(oldValue, m_yAngle, rootNode);
}

bool DynamicGameObject::IncrementZAngle(float increaseAmount, StaticGameObject* rootNode)
{
	float oldValue = m_zAngle;
	m_zAngle += increaseAmount;

	return UpdateTransformAndCheckCollision(oldValue, m_zAngle, rootNode);
}

bool DynamicGameObject::IncrementScale(float increaseAmount, StaticGameObject* rootNode)
{
	float oldValue = m_scale;
	m_scale += increaseAmount;

	return UpdateTransformAndCheckCollision(oldValue, m_scale, rootNode);
}

#pragma endregion
