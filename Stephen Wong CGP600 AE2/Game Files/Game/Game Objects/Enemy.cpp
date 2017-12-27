// *********************************************************
//	Name:			Stephen Wong
//	File:			Enemy.cpp
//	Last Updated:	27/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Enemy.h"

#pragma endregion

//####################################################################################
// Constructors
//####################################################################################
Enemy::Enemy() : DynamicGameObject()
{
	InitialiseNonPlayerEntity();
}

Enemy::Enemy(float speed, float xPos, float yPos, float zPos) :
	DynamicGameObject(speed, xPos, yPos, zPos)
{
	InitialiseNonPlayerEntity();
}

Enemy::Enemy(float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle):
	DynamicGameObject(speed, xPos, yPos, zPos, xAngle, yAngle, zAngle)
{
	InitialiseNonPlayerEntity();
}

Enemy::Enemy(float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale):
	DynamicGameObject(speed, xPos, yPos, zPos, xAngle, yAngle, zAngle, scale)
{
	InitialiseNonPlayerEntity();
}

//####################################################################################
// Set up the non-player entity
//####################################################################################
void Enemy::InitialiseNonPlayerEntity(void)
{
	m_gameObjectType = ENEMY;
	SetNewTargetPosition();
}

//####################################################################################
// Update the game object's position
//####################################################################################
void Enemy::Update(StaticGameObject* rootNode)
{
	if (IsNearTargetPosition()) SetNewTargetPosition();

	MoveForward(m_movementSpeed, rootNode);
}

//####################################################################################
// Get a new target position
//####################################################################################
void Enemy::SetNewTargetPosition(void)
{
	m_targetXPos = m_xPos + GetRandomPatrolPosition();
	m_targetZPos = m_zPos + GetRandomPatrolPosition();

	LookAtXZ(m_targetXPos, m_targetZPos);
}

//####################################################################################
// Get a random value for the target position
//####################################################################################
int Enemy::GetRandomPatrolPosition(void)
{
	// Does - patrol range /2 so it can go into negatives
	return rand() % patrolRange - (patrolRange / 2);
}

//####################################################################################
// Check if the object is near the target
//####################################################################################
bool Enemy::IsNearTargetPosition(void)
{
	// Check if the game object is near the target position
	if ((m_xPos >= m_targetXPos - positionCheckRange && m_xPos <= m_targetXPos + positionCheckRange) &&
		(m_zPos >= m_targetZPos - positionCheckRange && m_zPos <= m_targetZPos + positionCheckRange))
			return true;
	return false;
}

//####################################################################################
// Collision when this object hit another
//####################################################################################
void Enemy::ThisCollidesWithAnotherObject(StaticGameObject* object)
{
	// Make the object go in the opposite direction that it is currently going in
	m_targetXPos = ((m_xPos - object->GetXPos())) + m_xPos;
	m_targetZPos = ((m_zPos - object->GetZPos()))+ m_zPos;

	LookAtXZ(m_targetXPos, m_targetZPos);

}
