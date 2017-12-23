// *********************************************************
//	Name:			Stephen Wong
//	File:			NonPlayerEntity.h
//	Last Updated:	23/12/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include "DynamicGameObject.h"
#include <time.h>

#pragma endregion

#pragma region Constants

const int patrolRange = 10;
const int positionCheckRange = 1;

#pragma endregion

class NonPlayerEntity : public DynamicGameObject
{
private:
	float m_targetXPos;
	float m_targetZPos;

public:
	NonPlayerEntity();
	NonPlayerEntity(float speed, float xPos, float yPos, float zPos);
	NonPlayerEntity(float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle);
	NonPlayerEntity(float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale);

	void InitialiseNonPlayerEntity(void);
	void Update(StaticGameObject* rootNode);
	void SetNewTargetPosition(void);
	int GetRandomPatrolPosition(void);
	bool IsNearTargetPosition(void);
	virtual void ObjectCollidesWithThis(float oldValue, float &valueThatWasChanged, StaticGameObject* object);
	virtual void ThisCollidesWithAnotherObject(StaticGameObject* object);
};