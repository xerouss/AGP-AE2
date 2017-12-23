// *********************************************************
//	Name:			Stephen Wong
//	File:			PushableGameObject.h
//	Last Updated:	23/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "DynamicGameObject.h"

#pragma endregion

const float pushSpeed = 0.1f;

class PushableGameObject : public DynamicGameObject
{
private:
	StaticGameObject* m_pWorldRootGameObject;

public:
	PushableGameObject(StaticGameObject* rootGameObject);
	PushableGameObject(StaticGameObject* rootGameObject, float speed, float xPos, float yPos, float zPos);
	PushableGameObject(StaticGameObject* rootGameObject, float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle);
	PushableGameObject(StaticGameObject* rootGameObject, float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale);

	void InitialisePushabelGameObject(StaticGameObject* rootGameObject);
	virtual void ObjectCollidesWithThis(float oldValue, float &valueThatWasChanged, StaticGameObject* object);

};