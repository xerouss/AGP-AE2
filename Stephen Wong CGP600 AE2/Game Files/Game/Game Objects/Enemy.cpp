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
Enemy::Enemy(float aggroRange) : DynamicGameObject()
{
	// Call dynamic game object constructor first

	InitialiseNonPlayerEntity(aggroRange);
}

Enemy::Enemy(float aggroRange, float speed, float xPos, float yPos, float zPos) :
	DynamicGameObject(speed, xPos, yPos, zPos)
{
	// Call dynamic game object constructor first

	InitialiseNonPlayerEntity(aggroRange);
}

Enemy::Enemy(float aggroRange, float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle):
	DynamicGameObject(speed, xPos, yPos, zPos, xAngle, yAngle, zAngle)
{
	// Call dynamic game object constructor first

	InitialiseNonPlayerEntity(aggroRange);
}

Enemy::Enemy(float aggroRange, float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale):
	DynamicGameObject(speed, xPos, yPos, zPos, xAngle, yAngle, zAngle, scale)
{
	// Call dynamic game object constructor first

	InitialiseNonPlayerEntity(aggroRange);
}

//####################################################################################
// Set up the non-player entity
//####################################################################################
void Enemy::InitialiseNonPlayerEntity(float aggroRange)
{
	m_startXPos = m_xPos;
	m_startZPos = m_zPos;
	m_aggroRange = aggroRange;
	m_gameObjectType = ENEMY;
	SetNewRandomTargetPosition();
}

//####################################################################################
// Update the game object's position
//####################################################################################
void Enemy::Update(StaticGameObject* rootNode, Camera* player)
{
	float playerXPos = player->GetXPos();
	float playerZPos = player->GetZPos();

	// Check if player is in aggro range
	if (IsNearPosition(playerXPos, playerZPos, m_aggroRange))
	{
		m_isChasingPlayer = true;
		// Make the player position the target
		SetNewTargetPosition(playerXPos, playerZPos);
	}
	// Is else if so that it only gets a new random position once the player is out of aggro range
	else if (m_isChasingPlayer == true)
	{
		m_isChasingPlayer = false;
		// Go back to the original position once the player is out of aggro range
		SetNewTargetPosition(m_startXPos, m_startZPos);
	}

	// Get new target position if near the current one
	// Does this while not chasing so it doesn't randomly stop chasing when it gets near the target position
	if(IsNearPosition(m_targetXPos, m_targetZPos, positionCheckRange) 
		&& !m_isChasingPlayer) SetNewRandomTargetPosition();

	// If the enemy walks to far from the start position go back to it
	if(!IsNearPosition(m_startXPos, m_startZPos, maxDistanceFromStartPosition) &&
		!m_isChasingPlayer)
		SetNewTargetPosition(m_startXPos, m_startZPos);

	MoveForward(m_movementSpeed, rootNode);
}

//####################################################################################
// Set a new target position by using random numbers
//####################################################################################
void Enemy::SetNewRandomTargetPosition(void)
{
	SetNewTargetPosition(m_xPos + GetRandomPatrolPosition(), m_zPos + GetRandomPatrolPosition());
}

//####################################################################################
// Set a new target position
//####################################################################################
void Enemy::SetNewTargetPosition(float x, float z)
{
	m_targetXPos = x;
	m_targetZPos = z;

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
bool Enemy::IsNearPosition(float x, float z, float range)
{
	// Half the range since one half will be used for the upper bound
	// While the other half is the lower bound
	range = range / 2;

	// Check if the game object is near the target position
	// Only check x and z because the enemy doesn't jump
	if ((m_xPos >= x - range && m_xPos <= x + range) &&
		(m_zPos >= z - range && m_zPos <= z + range))
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
