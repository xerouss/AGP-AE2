// *********************************************************
//	Name:			Stephen Wong
//	File:			Camera.cpp
//	Last Updated:	04/01/2018
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Camera.h"

#pragma endregion

//####################################################################################
// Constructors
//####################################################################################
Camera::Camera(Time* time) : DynamicGameObject()
{	
	// Call dynamic game object constructor
	InitialiseCamera(time);
}

Camera::Camera(Time* time, float speed, float xPos, float yPos, float zPos) :
	DynamicGameObject(speed, xPos, yPos, zPos)
{
	// Call dynamic game object constructor
	InitialiseCamera(time);
}

Camera::Camera(Time* time, float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle) :
	DynamicGameObject(speed, xPos, yPos, zPos, xAngle, yAngle, zAngle)
{
	// Call dynamic game object constructor
	InitialiseCamera(time);
}

Camera::Camera(Time* time, float speed, float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale) :
	DynamicGameObject(speed, xPos, yPos, zPos, xAngle, yAngle, zAngle, scale)
{
	// Call dynamic game object constructor
	InitialiseCamera(time);
}

//####################################################################################
// Set up the camera
//####################################################################################
void Camera::InitialiseCamera(Time* time)
{
	m_pTime = time;
	m_gameObjectType = CAMERA;

	// Vector facing up
	m_up = XMVectorSet(0, 1.0f, 0, 0);

	// Set default delta values
	m_deltaXPos = (float)sin(0);
	m_deltaYPos = (float)tan(0);
	m_deltaZPos = (float)cos(0);
}

//####################################################################################
// Get new position when moving forward
//####################################################################################
void Camera::SetNewForwardPosition(float distance)
{
	// Times by delta since they is where the camera is looking
	m_xPos += distance * m_deltaXPos;
	m_zPos += distance * m_deltaZPos;
}

//####################################################################################
// Move the camera left/right
//####################################################################################
void Camera::Strafe(float distance, StaticGameObject* rootNode)
{
	// Saved old position in case of a collision
	float oldXPos = m_xPos;
	float oldZPos = m_zPos;

	// Used this to help implement strafing: http://www.cplusplus.com/forum/beginner/124843/ (hdn, 2014) Last Viewed 27/12/17
	// Instead of using y I sued the z since its rotating on x and z
	// I made the z have the minus since it was rotating the wrong way round
	m_xPos += distance * m_deltaZPos;
	m_zPos += distance * -m_deltaXPos;

	// Check for collisions
	UpdateTransformAndCheckCollision(oldXPos, m_xPos, rootNode);
	UpdateTransformAndCheckCollision(oldZPos, m_zPos, rootNode);
}

//####################################################################################
// Increase x angle
//####################################################################################
bool Camera::IncrementXAngle(float increaseAmount, StaticGameObject * rootNode)
{
	// Check if the camera will collide with an object when it rotates
	bool collision = DynamicGameObject::IncrementXAngle(increaseAmount, rootNode);

	// Don't change the angle if it collides with something
	if (collision) return true;

	// Use sin because it's a rearranged trig equation
	m_deltaXPos = sin(m_xAngle * DegreesToRadians);
	return false;
}

//####################################################################################
// Increase y angle
//####################################################################################
bool Camera::IncrementYAngle(float increaseAmount, StaticGameObject * rootNode)
{
	// Check if the camera will collide with an object when it rotates
	bool collision = DynamicGameObject::IncrementYAngle(increaseAmount, rootNode);

	// Don't change the angle if it collides with something
	if (collision) return true;

	// Use tan because it's a rearranged trig equation
	m_deltaYPos = tan(m_yAngle * DegreesToRadians);
	return false;
}

//####################################################################################
// Increase z angle
//####################################################################################
bool Camera::IncrementZAngle(float increaseAmount, StaticGameObject * rootNode)
{
	// Check if the camera will collide with an object when it rotates
	bool collision = DynamicGameObject::IncrementZAngle(increaseAmount, rootNode);

	// Don't change the angle if it collides with something
	if (collision) return true;

	// Use cos because it's a rearranged trig equation
	m_deltaZPos = cos(m_zAngle * DegreesToRadians);
	return false;
}

//####################################################################################
// What happens when the player collides with another object
//####################################################################################
void Camera::ObjectCollidesWithThis(float oldValue, float &valueThatWasChanged, StaticGameObject* object)
{
	if (object->GetGameObjectType() == ENEMY)
	{
		// Make sure time has passed between hits or the player will lose all of their health
		if (m_pTime->GetSecondsSinceStartOfGame() - m_timeAtCollision >= timeBetweenHits)
		{
			m_currentHealth -= damage;

			// Make the lowest amount 0 for the HUD as well as for health checks
			if (m_currentHealth < 0) m_currentHealth = 0;

			// Save the time the collision happened
			m_timeAtCollision = m_pTime->GetSecondsSinceStartOfGame();
		}
	}

	// Call the dynamics game object version which should move the object back to it's original position
	DynamicGameObject::ObjectCollidesWithThis(oldValue, valueThatWasChanged, object);
}

//####################################################################################
// Get the view matrix to display the world
//####################################################################################
XMMATRIX Camera::GetViewMatrix(void)
{
	m_position = XMVectorSet(m_xPos, m_yPos, m_zPos, 0.0f);
	m_lookAtPos = XMVectorSet(m_xPos + m_deltaXPos, m_yPos + m_deltaYPos, m_zPos + m_deltaZPos, 0.0f);
	return XMMatrixLookAtLH(m_position, m_lookAtPos, m_up);
}

//####################################################################################
// Get current health
//####################################################################################
int Camera::GetCurrentHealth(void)
{
	return m_currentHealth;
}

