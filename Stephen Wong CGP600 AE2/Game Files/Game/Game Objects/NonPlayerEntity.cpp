// *********************************************************
//	Name:			Stephen Wong
//	File:			NonPlayerEntity.cpp
//	Last Updated:	20/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "NonPlayerEntity.h"

#pragma endregion

//####################################################################################
// Constructors
//####################################################################################
NonPlayerEntity::NonPlayerEntity() : DynamicGameObject()
{
	InitialiseNonPlayerEntity();
}

NonPlayerEntity::NonPlayerEntity(float speed, float xPos, float yPos, float zPos) :
	DynamicGameObject(speed, xPos, yPos, zPos)
{
	InitialiseNonPlayerEntity();
}

NonPlayerEntity::NonPlayerEntity(float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle):
	DynamicGameObject(speed, xPos, yPos, zPos, xAngle, yAngle, zAngle)
{
	InitialiseNonPlayerEntity();
}

NonPlayerEntity::NonPlayerEntity(float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale):
	DynamicGameObject(speed, xPos, yPos, zPos, xAngle, yAngle, zAngle, scale)
{
	InitialiseNonPlayerEntity();
}

//####################################################################################
// Set up the non-player entity
//####################################################################################
void NonPlayerEntity::InitialiseNonPlayerEntity(void)
{
	m_gameObjectType = NONPLAYERENTITY;
	m_startXPos = m_xPos;
	m_startZPos = m_zPos;

	SetNewTargetPosition();
}

//####################################################################################
// Update the game object's position
//####################################################################################
void NonPlayerEntity::Update(StaticGameObject* rootNode)
{
	if (IsNearTargetPosition()) SetNewTargetPosition();

	MoveForward(m_movementSpeed);
}

//####################################################################################
// Get a new target position
//####################################################################################
void NonPlayerEntity::SetNewTargetPosition(void)
{
	m_targetXPos = m_xPos + GetRandomPatrolPosition();
	m_targetZPos = m_zPos + GetRandomPatrolPosition();

	LookAtXZ(m_targetXPos, m_targetZPos);
}

//####################################################################################
// Get a random value for the target position
//####################################################################################
int NonPlayerEntity::GetRandomPatrolPosition(void)
{
	// Does - patrol range /2 so it can go into negatives
	return rand() % patrolRange - (patrolRange / 2);
}

//####################################################################################
// Check if the object is near the target
//####################################################################################
bool NonPlayerEntity::IsNearTargetPosition(void)
{
	// Check if the game object is near the target position
	if ((m_xPos >= m_targetXPos - positionCheckRange && m_xPos <= m_targetXPos + positionCheckRange) &&
		(m_zPos >= m_targetZPos - positionCheckRange && m_zPos <= m_targetZPos + positionCheckRange))
			return true;
	return false;
}
