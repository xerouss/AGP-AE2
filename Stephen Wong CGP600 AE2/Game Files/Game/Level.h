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

public:
	Level(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	~Level();

	HRESULT SetUpLevel(void);
	void Update(void);
	void Render(void);
	void PlayerInput(unsigned char pressedKeys[]);
};
