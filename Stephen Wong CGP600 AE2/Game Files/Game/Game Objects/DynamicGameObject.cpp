// *********************************************************
//	Name:			Stephen Wong
//	File:			DynamicGameObject.cpp
//	Last Updated:	04/01/2018
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "DynamicGameObject.h"

#pragma endregion

//####################################################################################
// Constructors
//####################################################################################
DynamicGameObject::DynamicGameObject() : StaticGameObject()
{
	// Call static game object's constructor
	InitialiseDynamicGameObject(defaultSpeed);
}

DynamicGameObject::DynamicGameObject(float speed, float xPos, float yPos, float zPos):
	StaticGameObject(xPos, yPos, zPos)
{
	// Call static game object's constructor
	InitialiseDynamicGameObject(speed);
}

DynamicGameObject::DynamicGameObject(float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle) :
	StaticGameObject(xPos, yPos, zPos, xAngle, yAngle, zAngle)
{
	// Call static game object's constructor
	InitialiseDynamicGameObject(speed);
}

DynamicGameObject::DynamicGameObject(float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale) :
	StaticGameObject(xPos, yPos, zPos, xAngle, yAngle, zAngle, scale)
{
	// Call static game object's constructor
	InitialiseDynamicGameObject(speed);
}

//####################################################################################
// Set up the dynamic object
//####################################################################################
void DynamicGameObject::InitialiseDynamicGameObject(float speed)
{
	SetGameObjectType(DYNAMIC);
	m_movementSpeed = speed;
}

//####################################################################################
// Look at a position on the y axis
//####################################################################################
void DynamicGameObject::LookAtXZ(float worldX, float worldZ)
{
	// Work out the differences between the positions
	float dx = worldX - m_xPos;
	float dz = worldZ - m_zPos;

	// Use atan2 since the value could be 0
	// Work out the angle for y
	m_yAngle = atan2(dx, dz);
}

//####################################################################################
// Look at a position on the x axis and y axis
//####################################################################################
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

	// Work out the y angle
	LookAtXZ(worldX, worldZ);
}

//####################################################################################
// Move forward
//####################################################################################
void DynamicGameObject::MoveForward(float distance, StaticGameObject * rootNode)
{
	float oldXPos = m_xPos;
	float oldZPos = m_zPos;

	SetNewForwardPosition(distance);

	// Check collisions
	UpdateTransformAndCheckCollision(oldXPos, m_xPos, rootNode);
	UpdateTransformAndCheckCollision(oldZPos, m_zPos, rootNode);
}

//####################################################################################
// Get new position when moving forward
//####################################################################################
void DynamicGameObject::SetNewForwardPosition(float distance)
{
	// Use sin/cos because it's a rearranged trig equation
	m_xPos += sin(m_yAngle) * distance;
	m_zPos += cos(m_yAngle) * distance;
}


//####################################################################################
// Move forward but include y in the calculations
//####################################################################################
void DynamicGameObject::MoveForwardIncludingY(float distance)
{
	// Move forward but include the y rotation
	float cosXAngle = cos(m_xAngle);
	m_xPos += sin(m_yAngle) * distance * cosXAngle;
	m_yPos += -sin(m_xAngle) * distance;
	m_zPos += cos(m_yAngle) * distance * cosXAngle;
}

//####################################################################################
// Check collision and carry out the collision effect if there is one
//####################################################################################
bool DynamicGameObject::UpdateTransformAndCheckCollision(float oldValue, float &valueChanged, StaticGameObject* rootNode)
{
	XMMATRIX identity = XMMatrixIdentity();

	// Update collision tree since the state has been changed
	rootNode->UpdateCollisionTree(&identity, m_scale);

	// Get the object collided with
	StaticGameObject* collidedObject = CheckCollision(rootNode);

	if (collidedObject != NULL)
	{
		// Unless the object is the camera and the collided object is a collectible, return false
		// This stops other objects than the camera/player picking up the collectible and destroying it
		if (m_gameObjectType != CAMERA && collidedObject->GetGameObjectType() == COLLECTIBLE) return false;

		// Collision
		// Carry out the collided object's collision effect
		collidedObject->ObjectCollidesWithThis(oldValue, valueChanged, this);

		// Carry out this object's collision effect
		ThisCollidesWithAnotherObject(collidedObject);

		// If the object needs to be deleted after collision, delete it
		if (collidedObject->GetDeleteAfterCollision())
		{
			// Detach the collided object to prevent errors
			rootNode->DetachNode(collidedObject); 

			delete collidedObject;
			collidedObject = NULL;
		}
		return true;
	}

	// No Collision
	return false;
}

//####################################################################################
// When this object collides with any object
//####################################################################################
void DynamicGameObject::ThisCollidesWithAnotherObject(StaticGameObject * object)
{
	// Is blank because most objects won't need anything
}

//////////////////////////////////////////////////////////////////////////////////////
// Increment Methods
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Increment Methods

bool DynamicGameObject::IncrementXPos(float increaseAmount, StaticGameObject* rootNode)
{
	// Change pos
	float oldValue = m_xPos;
	m_xPos += increaseAmount;

	// Check for collisions
	return UpdateTransformAndCheckCollision(oldValue, m_xPos, rootNode);
}

bool DynamicGameObject::IncrementYPos(float increaseAmount, StaticGameObject* rootNode)
{
	// Change pos
	float oldValue = m_yPos;
	m_yPos += increaseAmount;

	// Check for collisions
	return UpdateTransformAndCheckCollision(oldValue, m_yPos, rootNode);
}

bool DynamicGameObject::IncrementZPos(float increaseAmount, StaticGameObject* rootNode)
{
	// Change pos
	float oldValue = m_zPos;
	m_zPos += increaseAmount;

	// Check for collisions
	return UpdateTransformAndCheckCollision(oldValue, m_zPos, rootNode);
}

bool DynamicGameObject::IncrementXAngle(float increaseAmount, StaticGameObject* rootNode)
{
	// Change rotation
	float oldValue = m_xAngle;
	m_xAngle += increaseAmount;

	// Check for collisions
	return UpdateTransformAndCheckCollision(oldValue, m_xAngle, rootNode);
}

bool DynamicGameObject::IncrementYAngle(float increaseAmount, StaticGameObject* rootNode)
{
	// Change rotation
	float oldValue = m_yAngle;
	m_yAngle += increaseAmount;

	// Check for collisions
	return UpdateTransformAndCheckCollision(oldValue, m_yAngle, rootNode);
}

bool DynamicGameObject::IncrementZAngle(float increaseAmount, StaticGameObject* rootNode)
{
	// Change rotation
	float oldValue = m_zAngle;
	m_zAngle += increaseAmount;

	// Check for collisions
	return UpdateTransformAndCheckCollision(oldValue, m_zAngle, rootNode);
}

bool DynamicGameObject::IncrementScale(float increaseAmount, StaticGameObject* rootNode)
{
	// Change scale
	float oldValue = m_scale;
	m_scale += increaseAmount;

	// Check for collisions
	return UpdateTransformAndCheckCollision(oldValue, m_scale, rootNode);
}

//####################################################################################
// Get and Set movement speed
//####################################################################################
float DynamicGameObject::GetMovementSpeed(void)
{
	return m_movementSpeed;
}

void DynamicGameObject::SetMovementSpeed(float speed)
{
	m_movementSpeed = speed;
}


#pragma endregion
