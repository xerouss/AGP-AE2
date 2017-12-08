// *********************************************************
//	Name:			Stephen Wong
//	File:			Camera.cpp
//	Last Updated:	07/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Camera.h"

#pragma endregion

const float defaultDeltaPos = 0;
//const float radianToDegrees = 0.01745329251f;

//####################################################################################
// Constructors
//####################################################################################
Camera::Camera() : DynamicGameObject()
{
	SetDefaultProperties();
	// Call dynamic game object constructor
}

Camera::Camera(float xPos, float yPos, float zPos) :
	DynamicGameObject(xPos, yPos, zPos)
{
	SetDefaultProperties();
	// Call static game object's constructor
}

Camera::Camera(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle) :
	DynamicGameObject(xPos, yPos, zPos, xAngle, yAngle, zAngle)
{
	SetDefaultProperties();
	// Call static game object's constructor
}

Camera::Camera(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale) :
	DynamicGameObject(xPos, yPos, zPos, xAngle, yAngle, zAngle, scale)
{
	SetDefaultProperties();
	// Call static game object's constructor
}

void Camera::SetDefaultProperties()
{
	m_deltaXPos = (float)sin(0);
	m_deltaYPos = (float)tan(0);
	m_deltaZPos = (float)cos(0);
}

void Camera::MoveForward(float distance)
{
	m_xPos += distance * m_deltaZPos;
	m_zPos += distance * m_deltaZPos;
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

	m_deltaXPos = (float)sin(m_xAngle);
	return false;
}

bool Camera::IncrementYAngle(float increaseAmount, StaticGameObject * rootNode)
{
	bool collision = DynamicGameObject::IncrementYAngle(increaseAmount, rootNode);

	if (collision) return true;

	m_deltaYPos = (float)sin(m_yAngle);
	return false;
}

bool Camera::IncrementZAngle(float increaseAmount, StaticGameObject * rootNode)
{
	bool collision = DynamicGameObject::IncrementZAngle(increaseAmount, rootNode);

	if (collision) return true;

	m_deltaZPos = (float)sin(m_zAngle);
	return false;
}

XMMATRIX Camera::GetViewMatrix(void)
{
	// THINK IM MISSING SOMETHING
	// LOOK THROUGH TUTORIALS
	m_position = XMVectorSet(m_xPos, m_yPos, m_zPos, 0.0);
	m_lookAtPos = XMVectorSet(m_xPos + m_deltaXPos, m_yPos + m_deltaYPos, m_zPos + m_deltaZPos, 0.0);
	m_up = XMVectorSet(0.0, 1.0, 0.0, 0.0);
	return XMMatrixLookAtLH(m_position, m_lookAtPos, m_up);
}


