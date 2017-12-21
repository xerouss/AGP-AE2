// *********************************************************
//	Name:			Stephen Wong
//	File:			StaticGameObject.cpp
//	Last Updated:	19/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "StaticGameObject.h"

#pragma endregion

//####################################################################################
// Constructors
//####################################################################################
StaticGameObject::StaticGameObject()
{
	SetDefaultProperties(defaultAxisPos, defaultAxisPos, defaultAxisPos,
		defaultAxisRotation, defaultAxisRotation, defaultAxisRotation, defaultScale);
}

StaticGameObject::StaticGameObject(float xPos, float yPos, float zPos)
{
	SetDefaultProperties(xPos, yPos, zPos,
		defaultAxisRotation, defaultAxisRotation, defaultAxisRotation, defaultScale);
}

StaticGameObject::StaticGameObject(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle)
{
	SetDefaultProperties(xPos, yPos, zPos, xAngle, yAngle, zAngle, defaultScale);
}

StaticGameObject::StaticGameObject(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale)
{
	SetDefaultProperties(xPos, yPos, zPos, xAngle, yAngle, zAngle, scale);
}

//####################################################################################
// Set the values for the object when the object is created
//####################################################################################
void StaticGameObject::SetDefaultProperties(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale)
{
	m_pModel = NULL;

	m_xPos = xPos;
	m_yPos = yPos;
	m_zPos = zPos;

	m_xAngle = xAngle;
	m_yAngle = yAngle;
	m_zAngle = zAngle;

	m_scale = scale;
}

//####################################################################################
// Destructor
//####################################################################################
StaticGameObject::~StaticGameObject()
{
	// Delete all pointers in the array
	// TODO: CHANGE THIS?
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		if (m_pChildren[i])
		{
			delete m_pChildren[i];
			m_pChildren[i] = NULL;
		}
	}
	m_pChildren.clear(); // Clear out the array

						 //if (m_pModel)
						 //{
						 //	delete m_pModel;
						 //	m_pModel = NULL;
						 //}
}

//####################################################################################
// Add child to the game object
//####################################################################################
void StaticGameObject::AddChildNode(StaticGameObject *node)
{
	m_pChildren.push_back(node);
}

//####################################################################################
// Remove child from the game object
//####################################################################################
bool StaticGameObject::DetachNode(StaticGameObject * node)
{
	// Go through the tree
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		// If the child is the node
		if (node == m_pChildren[i])
		{
			// Remove it from the tree
			m_pChildren.erase(m_pChildren.begin() + i);
			return true; // Was in the tree and detached
		}

		// Check the child's children to see if the node is in there
		if (m_pChildren[i]->DetachNode(node) == true) return true;
	}

	return false; // Node not in the tree
}

//####################################################################################
// Update the position of the object
//####################################################################################
void StaticGameObject::Render(XMMATRIX *world, XMMATRIX* view, XMMATRIX* projection)
{
	// Local World used to calculate local transforms from this node
	XMMATRIX localWorld = XMMatrixIdentity();

	// Scale
	localWorld = XMMatrixScaling(m_scale, m_scale, m_scale);

	// Rotation
	localWorld *= XMMatrixRotationX(XMConvertToRadians(m_xAngle));
	localWorld *= XMMatrixRotationY(XMConvertToRadians(m_yAngle));
	localWorld *= XMMatrixRotationZ(XMConvertToRadians(m_zAngle));

	// Translation
	localWorld *= XMMatrixTranslation(m_xPos, m_yPos, m_zPos);

	// The passed world matrix contains the transformations of all parent nodes
	// So need to become relative to those
	localWorld *= *world;

	// Draw if model is attached
	// TODO MOVE THIS TO A RENDER METHOD?
	if (m_pModel) m_pModel->Draw(&localWorld, view, projection);

	// Go through all the child nodes and pass the world matrix
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->Render(&localWorld, view, projection);
	}
}

//####################################################################################
// Update the collision tree when the object changes
//####################################################################################
void StaticGameObject::UpdateCollisionTree(XMMATRIX * world, float scale)
{
	// Local World used to calculate local transforms from this node
	XMMATRIX localWorld = XMMatrixIdentity();

	// Scale
	localWorld = XMMatrixScaling(m_scale, m_scale, m_scale);

	// Rotation
	localWorld *= XMMatrixRotationX(XMConvertToRadians(m_xAngle));
	localWorld *= XMMatrixRotationY(XMConvertToRadians(m_yAngle));
	localWorld *= XMMatrixRotationZ(XMConvertToRadians(m_zAngle));

	// Translation
	localWorld *= XMMatrixTranslation(m_xPos, m_yPos, m_zPos);

	// The passed world matrix contains the transformations of all parent nodes
	// So need to become relative to those
	localWorld *= *world;

	// Get world scale
	m_worldScale = scale * m_scale;

	XMVECTOR vector;

	// If there is a model, calc the bounding sphere world coords
	if (m_pModel)
	{
		vector = XMVectorSet(m_pModel->GetBoundingSphereX(),
			m_pModel->GetBoundingSphereY(),
			m_pModel->GetBoundingSphereZ(), 0.0f);
	}
	else vector = XMVectorSet(0, 0, 0, 0); // No model so default to 0

	// Get and store world space bounding sphere centre
	vector = XMVector3Transform(vector, localWorld);
	m_worldCentreX = XMVectorGetX(vector);
	m_worldCentreY = XMVectorGetY(vector);
	m_worldCentreZ = XMVectorGetZ(vector);

	// Traverse all child notes, passing the world data
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->UpdateCollisionTree(&localWorld, m_worldScale);
	}
}

//####################################################################################
// Check collision with another object
//####################################################################################
StaticGameObject* StaticGameObject::CheckCollision(StaticGameObject* compareTree)
{
	return CheckCollision(compareTree, this);
}

//####################################################################################
// Check collision with another object 
//####################################################################################
StaticGameObject* StaticGameObject::CheckCollision(StaticGameObject* compareTree, StaticGameObject* objectTreeRoot)
{
	// Check if both roots are the same
	if (objectTreeRoot == compareTree) return false;

	// Check for collision if both have models
	if (m_pModel && compareTree->m_pModel)
	{
		XMVECTOR vector1 = GetWorldCentrePosition();
		XMVECTOR vector2 = compareTree->GetWorldCentrePosition();
		// Get difference between the two
		XMVECTOR vectorDifference = vector1 - vector2;

		// Get distance
		float x1 = XMVectorGetX(vector1);
		float x2 = XMVectorGetX(vector2);
		float y1 = XMVectorGetY(vector1);
		float y2 = XMVectorGetY(vector2);
		float z1 = XMVectorGetZ(vector1);
		float z2 = XMVectorGetZ(vector2);

		float dx = x1 - x2;
		float dy = y1 - y2;
		float dz = z1 - z2;

		// Check bounding sphere collision
		// TODO: INSTEAD OF SQRT, POW THE OTHER SIDE?
		if (sqrt(dx*dx + dy * dy + dz * dz) <
			(compareTree->m_pModel->GetBoundingSphereRadius() * compareTree->m_worldScale) +
			(this->m_pModel->GetBoundingSphereRadius() * m_worldScale))
		{
			return compareTree; // Collision
		}
	}

	// Go through compare tree child nodes
	for (size_t i = 0; i < compareTree->m_pChildren.size(); i++)
	{
		// Check for collision against child nodes
		if (CheckCollision(compareTree->m_pChildren[i], objectTreeRoot) != NULL)
			return compareTree->m_pChildren[i];
	}

	// Go through own tree child nodes
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		// Check for collision against child nodes
		if (m_pChildren[i]->CheckCollision(compareTree, objectTreeRoot) != NULL)
			return m_pChildren[i];
	}

	return false;
}

//####################################################################################
// What happens when an object collides with this
//####################################################################################
void StaticGameObject::CollisionEffect(float oldValue, float &valueThatWasChanged, StaticGameObject* object)
{
	// Move the object back to it's original position
	valueThatWasChanged = oldValue;
}

//////////////////////////////////////////////////////////////////////////////////////
// Set Methods
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Set Methods

void StaticGameObject::SetModel(Model* model)
{
	m_pModel = model;
}

void StaticGameObject::SetXPos(float xPos)
{
	m_xPos = xPos;
}

void StaticGameObject::SetYPos(float yPos)
{
	m_yPos = yPos;
}

void StaticGameObject::SetZPos(float zPos)
{
	m_zPos = zPos;
}

void StaticGameObject::SetXRotation(float xAngle)
{
	m_xAngle = xAngle;
}

void StaticGameObject::SetYRotation(float yAngle)
{
	m_yAngle = yAngle;
}

void StaticGameObject::SetZRotation(float zAngle)
{
	m_zAngle = zAngle;
}

void StaticGameObject::SetScale(float scale)
{
	m_scale = scale;
}

void StaticGameObject::SetDeleteAfterCollision(bool shouldDelete)
{
	m_deleteAfterCollision = shouldDelete;
}

void StaticGameObject::SetGameObjectType(GameObjectTypes type)
{
	m_gameObjectType = type;
}
#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////
// Get Methods
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Get Methods

float StaticGameObject::GetXPos(void)
{
	return m_xPos;
}

float StaticGameObject::GetYPos(void)
{
	return m_yPos;
}

float StaticGameObject::GetZPos(void)
{
	return m_zPos;
}

float StaticGameObject::GetXRotation(void)
{
	return m_xAngle;
}

float StaticGameObject::GetYRotation(void)
{
	return m_yAngle;
}

float StaticGameObject::GetZRotation(void)
{
	return m_zAngle;
}

float StaticGameObject::GetScale(void)
{
	return m_scale;
}

XMVECTOR StaticGameObject::GetWorldCentrePosition()
{
	return XMVectorSet(m_worldCentreX, m_worldCentreY,
		m_worldCentreZ, 0.0f);
}

bool StaticGameObject::GetDeleteAfterCollision(void)
{
	return m_deleteAfterCollision;
}

GameObjectTypes StaticGameObject::GetGameObjectType(void)
{
	return m_gameObjectType;
}

#pragma endregion