// *********************************************************
//	Name:			Stephen Wong
//	File:			Camera.cpp
//	Last Updated:	30/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Camera.h"

#pragma endregion

const float defaultDeltaPos = 0;
const float DegreesToRadians = 0.01745329251f;

//####################################################################################
// Constructors
//####################################################################################
Camera::Camera() : DynamicGameObject()
{	
	// Call dynamic game object constructor
	SetDefaultProperties();
}

Camera::Camera(float xPos, float yPos, float zPos) :
	DynamicGameObject(xPos, yPos, zPos)
{
	// Call dynamic game object constructor
	SetDefaultProperties();
}

Camera::Camera(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle) :
	DynamicGameObject(xPos, yPos, zPos, xAngle, yAngle, zAngle)
{
	// Call dynamic game object constructor
	SetDefaultProperties();
}

Camera::Camera(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale) :
	DynamicGameObject(xPos, yPos, zPos, xAngle, yAngle, zAngle, scale)
{
	// Call dynamic game object constructor
	SetDefaultProperties();
}

//####################################################################################
// Set up the camera
//####################################################################################
void Camera::SetDefaultProperties()
{
	m_gameObjectType = CAMERA;

	m_deltaXPos = (float)sin(0);
	m_deltaYPos = (float)tan(0);
	m_deltaZPos = (float)cos(0);
}

//####################################################################################
// Move the camera forward/backwards
//####################################################################################
void Camera::MoveForward(float distance, StaticGameObject* rootNode)
{
	float oldXPos = m_xPos;
	float oldZPos = m_zPos;

	m_xPos += distance * m_deltaXPos;
	m_zPos += distance * m_deltaZPos;

	UpdateTransformAndCheckCollision(oldXPos, m_xPos, rootNode);
	UpdateTransformAndCheckCollision(oldZPos, m_zPos, rootNode);
}

//####################################################################################
// Move the camera left/right
//####################################################################################
void Camera::Strafe(float distance, StaticGameObject* rootNode)
{

	// TODO: USE THIS TO FIX https://gamedev.stackexchange.com/questions/63819/first-person-camera-strafing-at-angle
	float oldXPos = m_xPos;
	float oldZPos = m_zPos;

	m_xPos += distance * m_deltaZPos;
	m_zPos += distance * m_deltaXPos;

	UpdateTransformAndCheckCollision(oldXPos, m_xPos, rootNode);
	UpdateTransformAndCheckCollision(oldZPos, m_zPos, rootNode);
}

//void Camera::MoveForwardIncludingY(float distance)
//{
//}
//

// TODO: Make these into one method?
bool Camera::IncrementXAngle(float increaseAmount, StaticGameObject * rootNode)
{
	bool collision = DynamicGameObject::IncrementXAngle(increaseAmount, rootNode);

	if (collision) return true;

	m_deltaXPos = sinf(m_xAngle * DegreesToRadians);
	return false;
}

bool Camera::IncrementYAngle(float increaseAmount, StaticGameObject * rootNode)
{
	bool collision = DynamicGameObject::IncrementYAngle(increaseAmount, rootNode);

	if (collision) return true;

	m_deltaYPos = tan(m_yAngle * DegreesToRadians);
	return false;
}

bool Camera::IncrementZAngle(float increaseAmount, StaticGameObject * rootNode)
{
	bool collision = DynamicGameObject::IncrementZAngle(increaseAmount, rootNode);

	if (collision) return true;

	m_deltaZPos = cos(m_zAngle * DegreesToRadians);
	return false;
}

//####################################################################################
// Get the view matrix to display the world
//####################################################################################
XMMATRIX Camera::GetViewMatrix(void)
{
	m_position = XMVectorSet(m_xPos, m_yPos, m_zPos, 0.0f);
	m_lookAtPos = XMVectorSet(m_xPos + m_deltaXPos, m_yPos + m_deltaYPos, m_zPos + m_deltaZPos, 0.0f);
	m_up = XMVectorSet(0, 1.0f, 0, 0);
	return XMMatrixLookAtLH(m_position, m_lookAtPos, m_up);
}

//####################################################################################
// Get and Set movement speed
//####################################################################################
float Camera::GetMovementSpeed(void)
{
	return m_movementSpeed;
}

void Camera::SetMovementSpeed(float speed)
{
	m_movementSpeed = speed;
}


