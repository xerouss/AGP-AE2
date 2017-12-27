// *********************************************************
//	Name:			Stephen Wong
//	File:			Enemy.h
//	Last Updated:	27/12/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include "DynamicGameObject.h"
#include "Camera.h"

#pragma endregion

#pragma region Constants

const int patrolRange = 10;
const float positionCheckRange = 2;
const float maxDistanceFromStartPosition = 30;

#pragma endregion

class Enemy : public DynamicGameObject
{
private:
	float m_targetXPos;
	float m_targetZPos;
	float m_aggroRange;
	bool m_isChasingPlayer = false;
	float m_startXPos;
	float m_startZPos;

public:
	Enemy(float aggroRange);
	Enemy(float aggroRange, float speed, float xPos, float yPos, float zPos);
	Enemy(float aggroRange, float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle);
	Enemy(float aggroRange, float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale);

	void InitialiseNonPlayerEntity(float aggroRange);
	void Update(StaticGameObject* rootNode, Camera* player);
	void SetNewRandomTargetPosition(void);
	void SetNewTargetPosition(float x, float z);
	int GetRandomPatrolPosition(void);
	bool IsNearPosition(float x, float z, float range);
	virtual void ThisCollidesWithAnotherObject(StaticGameObject* object);
};