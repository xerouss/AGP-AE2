// *********************************************************
//	Name:			Stephen Wong
//	File:			StaticGameObject.h
//	Last Updated:	23/12/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT

#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include "Model.h"

using namespace DirectX;
using namespace DirectX::PackedVector;


#pragma endregion

#pragma region Constants

const float defaultScale = 1.0f;
const float defaultAxisPos = 0.0f;
const float defaultAxisRotation = 0.0f;

#pragma endregion

enum GameObjectTypes
{
	STATIC, DYNAMIC, COLLECTIBLE, PUSHABLE, CAMERA, ENEMY, NUMOFOBJECTTYPES
};


class StaticGameObject
{
private:
	Model* m_pModel;
	vector<StaticGameObject*> m_pChildren;

protected:
	bool m_deleteAfterCollision = false;
	// This allows different collision effects to happen based of the object type
	GameObjectTypes m_gameObjectType = STATIC;

#pragma region Position attributes

	float m_xPos;
	float m_yPos;
	float m_zPos;

	float m_worldCentreX;
	float m_worldCentreY;
	float m_worldCentreZ;

#pragma endregion

#pragma region Rotation attributes

	float m_xAngle;
	float m_yAngle;
	float m_zAngle;

#pragma endregion

#pragma region Scale Attributes
	float m_scale;

	float m_worldScale;
#pragma endregion
	
public:
	StaticGameObject();
	StaticGameObject(float xPos, float yPos, float zPos);
	StaticGameObject(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle);
	StaticGameObject(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale);
	// TODO: MAKE THIS VIRTUAL AND USE IT IN INHERITED OBJECTS
	void SetDefaultProperties(float xPos, float yPos, float zPos, float xAngle, float yAngle, float zAngle, float scale);
	virtual ~StaticGameObject();

	void AddChildNode(StaticGameObject *node);
	bool DetachNode(StaticGameObject *node);
	void Render(XMMATRIX *world, XMMATRIX* view, XMMATRIX* projection);
	void UpdateCollisionTree(XMMATRIX* world, float scale);
	// These returns what it collides with
	StaticGameObject* CheckCollision(StaticGameObject* compareTree);
	StaticGameObject* CheckCollision(StaticGameObject* compareTree, StaticGameObject* objectTreeRoot);
	// When this object gets collided with another
	virtual void ObjectCollidesWithThis(float oldValue, float &valueThatWasChanged, StaticGameObject* object);

#pragma region Set Methods
	void SetModel(Model* model);

	void SetXPos(float xPos);
	void SetYPos(float yPos);
	void SetZPos(float zPos);

	void SetXRotation(float xRot);
	void SetYRotation(float yRot);
	void SetZRotation(float zRot);

	void SetScale(float scale);

	void SetDeleteAfterCollision(bool shouldDelete);
	void SetGameObjectType(GameObjectTypes type);
#pragma endregion

#pragma region Get Methods

	float GetXPos(void);
	float GetYPos(void);
	float GetZPos(void);

	float GetXRotation(void);
	float GetYRotation(void);
	float GetZRotation(void);

	float GetScale(void);

	XMVECTOR GetWorldCentrePosition();

	bool GetDeleteAfterCollision(void);
	GameObjectTypes GetGameObjectType(void);
#pragma endregion

};