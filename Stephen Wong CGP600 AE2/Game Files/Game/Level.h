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
const float zeroPosition = 0;
const float zeroRotation = 0;
const float defaultRotation = 0;

const float skyboxScale = 30;
const float bigWallScale = 10;

const float enemyRoomWallBackZ = 40;
const float enemyRoomWallRightX = 25;
const float enemyRoomWallLeftX = -25;
const float enemyRoomWallSideZ = 10;
const float enemyTrappingWallOffset = 5;

const float enemyAggroRange = 25;
const float enemyXPos = 0;
const float enemyYPos = 0;
const float enemyZPos = 10;
const int enemyPositionHeadOffset = 2;
const float enemyHeadScale = 0.3f;
const int enemySpeedChange = 2;

const float pushableGameObjectX = 7;
const float pushableGameObject1Z = -15;
const float pushableGameObject2Z = -5;

const float camera1Z = -15;
const float camera2X = -10;
const float camera2Z = -5;

const float movingZPos = -10;

const float collectibleScale = 0.3f;
const float collectible1XPos = 10;
const float collectible2ZPos = -25;
const float collectible3XPos = -10;
const float collectible4ZPos = 5;

const float specularGameObjectX = -3;
const float specularGameObjectZ = -8;

const float reflectiveGameObjectX = -10;

const float pointLightWallX = 10;

const float ambientRGBColour = 0.1f;
const float directionalRGColour = 0.1f;
const float directionalBlueColour = 1;
const float directionalLightZPos = -1;
const float directionalLightZRotation = 1;
const float lightRange = 10;

const float specularRGColour = 0.1f;
const float specularBlueColour = 1;
const float specularLightZRotation = 1;
const float specularLightIntensity = 64;
const float specularLightZPos = -1;

const float pointLightRBColour = 0.1f;
const float pointLightGColour = 1;
const float pointLightZ = -20;
const int pointLightWallIndex = 6;

const int x = 0;
const int moveForward = 1;
const int moveBackwards = -1;
#pragma endregion


class Level
{
private:
	// Need the device and context for the models
	ID3D11Device* m_pD3DDevice;
	ID3D11DeviceContext* m_pImmediateContext;

	// The root game object which all game object will attach to
	StaticGameObject* m_pRootGameObject;

	// Cameras
	Camera* m_pPrimaryCamera;
	Camera* m_pSecondaryCamera;
	Camera* m_pActiveCamera;

	// Walls
	Model* m_pWallModels[6];
	StaticGameObject* m_pWallGameObjects[6];

	// Skybox
	Skybox* m_pSkybox;

	// Reflective object
	ReflectiveModel* m_pReflectiveSphere;
	StaticGameObject* m_pReflectiveGameObject;

	// Specular object
	SpecularModel* m_pSpecularModel;
	StaticGameObject* m_pSpecularGameObject;

	//Point Light
	Model* m_pPointLightWallModel;
	StaticGameObject* m_pPointLightWallGameObject;

	// Moving game object
	DynamicGameObject* m_pMovingGameObject;
	Model* m_pMovingModel;

	// Collectibles
	Collectible* m_pCollectibles[4];
	Model* m_pCollectibleModels[4];

	// Pushable Game Objects
	PushableGameObject* m_pPushableGameObjects[2];
	Model* m_pPushableGameObjectModel[2];

	// Enemy
	Enemy* m_pEnemy;
	StaticGameObject* m_pEnemyHeadObject;
	Model* m_pEnemyBody;
	Model* m_pEnemyHead;

	// Lights
	Light* m_pAmbientLight;
	DirectionalLight* m_pDirectionalLight;
	PointLight* m_pPointLight;
	SpecularLight* m_pSpecularLight;

	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;

	int m_pointLightMovementDirection = moveForward;
public:
	Level(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	~Level();

	HRESULT SetUpLevel(int* scoreSaveLocation, Time* time);	
	HRESULT CreateModel(Model* model, char*  objectFileName, char*  textureFileName,
		char* shaderFileName, char*  vertexShaderName, char*  pixelShaderName);
	HRESULT CreateSkybox(Skybox* model, char*  objectFileName, char*  textureFileName,
		char* shaderFileName, char*  vertexShaderName, char*  pixelShaderName);
	HRESULT SetModelSettings(BasicModel* model, char*  objectFileName, char*  textureFileName,
		char* shaderFileName, char*  vertexShaderName, char*  pixelShaderName);

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

	void SetUpModelForGameObject(Model* model, StaticGameObject* gameObject, StaticGameObject* root);
};
