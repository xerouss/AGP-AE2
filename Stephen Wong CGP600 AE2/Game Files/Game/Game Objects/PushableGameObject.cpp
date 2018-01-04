// *********************************************************
//	Name:			Stephen Wong
//	File:			PushableGameObject.cpp
//	Last Updated:	04/04/2018
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "PushableGameObject.h"

#pragma endregion

//####################################################################################
// Constructors
//####################################################################################
PushableGameObject::PushableGameObject(StaticGameObject* rootGameObject) : DynamicGameObject()
{
	// Call dynamic game object constructor
	InitialisePushabelGameObject(rootGameObject);
}

PushableGameObject::PushableGameObject(StaticGameObject* rootGameObject, float speed, float xPos, float yPos, float zPos) :
	DynamicGameObject(speed, xPos, yPos, zPos)
{
	// Call dynamic game object constructor
	InitialisePushabelGameObject(rootGameObject);
}

PushableGameObject::PushableGameObject(StaticGameObject* rootGameObject, float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle) :
	DynamicGameObject(speed, xPos, yPos, zPos, xAngle, yAngle, zAngle)
{
	// Call dynamic game object constructor
	InitialisePushabelGameObject(rootGameObject);
}

PushableGameObject::PushableGameObject(StaticGameObject* rootGameObject, float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale) :
	DynamicGameObject(speed, xPos, yPos, zPos, xAngle, yAngle, zAngle, scale)
{
	// Call dynamic game object constructor
	InitialisePushabelGameObject(rootGameObject);
}

//####################################################################################
// Set up the pushable game object
//####################################################################################
void PushableGameObject::InitialisePushabelGameObject(StaticGameObject* rootGameObject)
{
	SetGameObjectType(PUSHABLE);
	m_pWorldRootGameObject = rootGameObject;
}

//####################################################################################
// What happens on collision
//####################################################################################
void PushableGameObject::ObjectCollidesWithThis(float oldValue, float &valueThatWasChanged, StaticGameObject* object)
{
	// Work out the direction the object is colliding the pushable object from
	float dx = (m_xPos - object->GetXPos()) * pushSpeed;
	float dy = (m_yPos - object->GetYPos()) * pushSpeed;
	float dz = (m_zPos - object->GetZPos()) * pushSpeed;

	// Move the object in the same direction it is being pushed in
	bool XCollision = IncrementXPos(dx, m_pWorldRootGameObject);
	bool YCollision = IncrementYPos(dy, m_pWorldRootGameObject);
	bool ZCollision = IncrementZPos(dz, m_pWorldRootGameObject);

	// If the object collides with something in the direction it's getting pushed
	// Make sure the game object doesn't go into the object
	if (XCollision && YCollision && ZCollision) DynamicGameObject::ObjectCollidesWithThis(oldValue, valueThatWasChanged, object);
}
