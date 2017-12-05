// *********************************************************
//	Name:			Stephen Wong
//	File:			StaticGameObject.h
//	Last Updated:	05/12/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT

#include <d3d11.h>
#include <DirectXMath.h>
#include "Model.h"

using namespace DirectX;


#pragma endregion


class StaticGameObject
{
private:
	Model* m_pModel;
	vector<StaticGameObject*> m_pChildren;

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
	~StaticGameObject();

	void AddChildNode(StaticGameObject *node);
	bool DetachNode(StaticGameObject *node);
	void Update(XMMATRIX *world, XMMATRIX* view, XMMATRIX* projection);
	void UpdateCollisionTree(XMMATRIX* world, float scale);
	bool CheckCollision(StaticGameObject* compareTree);
	bool CheckCollision(StaticGameObject* compareTree, StaticGameObject* objectTreeRoot);
	bool UpdateTransformAndCheckCollision(float oldValue, float &valueChanged, StaticGameObject* rootNode);

#pragma region Set Methods
	void SetModel(Model* model);

	void SetXPos(float xPos);
	void SetYPos(float yPos);
	void SetZPos(float zPos);

	void SetXRotation(float xRot);
	void SetYRotation(float yRot);
	void SetZRotation(float zRot);

	void SetScale(float scale);
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
#pragma endregion

};