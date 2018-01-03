// *********************************************************
//	Name:			Stephen Wong
//	File:			Level.h
//	Last Updated:	03/01/2018
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "Model\Model.h"
#include "Model\Skybox.h"
#include "Model\ReflectiveModel.h"
#include "Model\SpecularModel.h"
#include "Game Objects\StaticGameObject.h"
#include "Game Objects\DynamicGameObject.h"
#include "Game Objects\Camera.h"
#include "Game Objects\Collectible.h"
#include "Game Objects\PushableGameObject.h"
#include "Game Objects\Enemy.h"
#include "Lights\Light.h"
#include "Lights\DirectionalLight.h"
#include "Lights\PointLight.h"
#include "Lights\\SpecularLight.h"

#pragma endregion

#pragma region Constants

const float defaultWorldMatrixValue = 0.0f;
const float defaultMovementSpeed = 0.001f;
const float secondaryCameraRotation = 90;
const float skyboxScale = 30;

#pragma endregion


class Level
{
private:
	// Need the device and context for the models
	ID3D11Device* m_pD3DDevice;
	ID3D11DeviceContext* m_pImmediateContext;

	Camera* m_pPrimaryCamera;
	Camera* m_pSecondaryCamera;
	Camera* m_pActiveCamera;

	Model* m_pWallModel;
	Skybox* m_pSkybox;
	ReflectiveModel* m_pReflectiveSphere;
	SpecularModel* m_pSpecularModel;

	StaticGameObject* m_pRootGameObject;
	DynamicGameObject* m_pWall1GameObject;
	DynamicGameObject* m_pWall2GameObject;
	DynamicGameObject* m_pWall3GameObject;
	Collectible* m_pCollectible1;
	PushableGameObject* m_pPushableGameObject1;
	Enemy* m_pEnemy1;

	Light* m_pAmbientLight;
	DirectionalLight* m_pDirectionalLight1;
	PointLight* m_pPointLight1;
	SpecularLight* m_pSpecularLight;

	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;

public:
	Level(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	~Level();

	HRESULT SetUpLevel(int* scoreSaveLocation, Time* time);
	void Update(void);
	void Render(void);
	
	// Changes made by the player
	void MoveCameraForward(float movementMultiplier);
	void StrafeCamera(float movementMultiplier);
	void ChangeCameraXAndZDirection(float amount);
	void ChangeCameraYDirection(float amount);
	void ChangeActiveCamera(void);

	void SetWorldMatrix(float xPos, float yPos, float zPos,
		float xRot, float yRot, float zRot, float scale);
	void SetProjectionMatrix(XMMATRIX projection);
	XMMATRIX GetSkyboxWorldMatrix(float scale);
	int GetPlayerHealth(void);
};
