// *********************************************************
//	Name:			Stephen Wong
//	File:			Level.h
//	Last Updated:	02/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "Game Objects\Model.h"
#include "Game Objects\StaticGameObject.h"
#include "Game Objects\DynamicGameObject.h"
#include "Game Objects\Camera.h"
#include "Game Objects\Collectible.h"

#pragma endregion


class Level
{
private:
	// TODO: ADD THESE:
	// Lights
	// GameObjects
	// Camera
	// Particles
	// Scene Nodes

	// Need the device and context for the models
	ID3D11Device* m_pD3DDevice;
	ID3D11DeviceContext* m_pImmediateContext;

	Camera* m_pCamera;
	Model* m_pWallModel;
	StaticGameObject* m_pRootWallGameObject;
	DynamicGameObject* m_pWall1GameObject;
	DynamicGameObject* m_pWall2GameObject;
	DynamicGameObject* m_pWall3GameObject;
	Collectible* m_pCollectible1;

public:
	Level(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	~Level();

	HRESULT SetUpLevel(int* m_scoreSaveLocation);
	void Update(void);
	void Render(void);
	
	void MoveCameraForward(float distance);
	void StrafeCamera(float distance);
	void ChangeCameraDirection(float amount);
};
