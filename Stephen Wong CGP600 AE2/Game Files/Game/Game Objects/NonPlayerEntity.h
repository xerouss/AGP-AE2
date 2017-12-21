// *********************************************************
//	Name:			Stephen Wong
//	File:			NonPlayerEntity.h
//	Last Updated:	20/12/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include "DynamicGameObject.h"
#include <time.h>

#pragma endregion

const int patrolRange = 10;
const int positionCheckRange = 1;

class NonPlayerEntity : public DynamicGameObject
{
private:
	float m_targetXPos;
	float m_targetZPos;
	float m_startXPos;
	float m_startZPos;

public:
	NonPlayerEntity();
	NonPlayerEntity(float speed, float xPos, float yPos, float zPos);
	NonPlayerEntity(float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle);
	NonPlayerEntity(float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale);

	void InitialiseNonPlayerEntity(void);
	void Update(StaticGameObject* rootNode);
	void SetNewTargetPosition(void);
	int GetRandomPortalPosition(void);
	bool IsNearTargetPosition(void);
};