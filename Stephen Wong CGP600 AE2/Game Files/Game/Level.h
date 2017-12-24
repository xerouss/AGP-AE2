// *********************************************************
//	Name:			Stephen Wong
//	File:			Level.h
//	Last Updated:	24/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "Game Objects\Model.h"
#include "Game Objects\StaticGameObject.h"
#include "Game Objects\DynamicGameObject.h"
#include "Game Objects\Camera.h"
#include "Game Objects\Collectible.h"
#include "Game Objects\PushableGameObject.h"
#include "Game Objects\Enemy.h"
#include "Lights\Light.h"
#include "Lights\DirectionalLight.h"

#pragma endregion


const float defaultWorldMatrixValue = 0.0f;
const float defaultMovementSpeed = 0.001f;

class Level
{
private:
	// TODO: ADD THESE:
	// Lights
	// Particles

	// Need the device and context for the models
	ID3D11Device* m_pD3DDevice;
	ID3D11DeviceContext* m_pImmediateContext;

	Camera* m_pCamera;
	Model* m_pWallModel;
	StaticGameObject* m_pRootGameObject;
	DynamicGameObject* m_pWall1GameObject;
	DynamicGameObject* m_pWall2GameObject;
	DynamicGameObject* m_pWall3GameObject;
	Collectible* m_pCollectible1;
	PushableGameObject* m_pPushableGameObject1;
	Enemy* m_pEnemy1;
	Light* m_pAmbientLight;
	DirectionalLight* m_pDirectionalLight1;

	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;

public:
	Level(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	~Level();

	HRESULT SetUpLevel(int* m_scoreSaveLocation);
	void Update(void);
	void Render(void);
	
	void MoveCameraForward(float movementMultiplier);
	void StrafeCamera(float movementMultiplier);
	void ChangeCameraDirection(float amount);

	void SetWorldMatrix(float xPos, float yPos, float zPos,
		float xRot, float yRot, float zRot, float scale);
	void SetProjectionMatrix(XMMATRIX projection);

	int GetPlayerHealth(void);
};
