// *********************************************************
//	Name:			Stephen Wong
//	File:			Level.cpp
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Level.h"

#pragma endregion

//####################################################################################
// Constructor
//####################################################################################
Level::Level(ID3D11Device *device, ID3D11DeviceContext *immediateContext)
{
	m_pD3DDevice = device;
	m_pImmediateContext = immediateContext;
}

//####################################################################################
// Destructor
//####################################################################################
Level::~Level()
{
	if (m_pSkybox)
	{
		delete m_pSkybox;
		m_pSkybox = NULL;
	}

	if (m_pPointLight1)
	{
		delete m_pPointLight1;
		m_pPointLight1 = NULL;
	}

	if (m_pDirectionalLight1)
	{
		delete m_pDirectionalLight1;
		m_pDirectionalLight1 = NULL;
	}

	if (m_pAmbientLight)
	{
		delete m_pAmbientLight;
		m_pAmbientLight = NULL;
	}

	if (m_pWallModel)
	{
		delete m_pWallModel;
		m_pWallModel = NULL;
	}

	// Only delete the root node since the nodes attached to it will be deleted
	if (m_pRootGameObject)
	{
		delete m_pRootGameObject;
		m_pRootGameObject = NULL;
	}

	// Is an else statement because only one of these should be attached to the root game object
	if (m_pSecondaryCamera != NULL)
	{
		delete m_pSecondaryCamera;
		m_pSecondaryCamera = NULL;
	}
	else
	{
		delete m_pPrimaryCamera;
		m_pPrimaryCamera = NULL;
	}
}

//####################################################################################
// Place the game objects around the level to create it
//####################################################################################
HRESULT Level::SetUpLevel(int* scoreSaveLocation, Time* time)
{
	HRESULT hr = S_OK;

	// Set up world matrix
	SetWorldMatrix(defaultWorldMatrixValue, defaultWorldMatrixValue, defaultWorldMatrixValue,
		defaultWorldMatrixValue, defaultWorldMatrixValue, defaultWorldMatrixValue, 1);

	// Create sky box
	m_pSkybox = new Skybox(skyboxScale, m_pD3DDevice, m_pImmediateContext);
	hr = m_pSkybox->LoadObjectModel("Assets/Models/cube.obj");
	if (FAILED(hr)) return hr;

	// Set up the skybox
	hr = m_pSkybox->InitialiseSkybox();
	if (FAILED(hr)) return hr;

	// Create constant buffer for models
	hr = m_pSkybox->CreateConstantBuffer();
	if (FAILED(hr)) return hr;

	// Add texture to the models
	hr = m_pSkybox->AddTexture("Assets/Skyboxes/skybox02.dds");
	if (FAILED(hr)) return hr;

	// Create filter for the texture
	hr = m_pSkybox->CreateSampler();
	if (FAILED(hr)) return hr;

	// Create vertex shader
	hr = m_pSkybox->CreateVertexShader("Game Files/Game/Shaders/SkyboxShader.hlsl", "SkyboxVertexShader");
	if (FAILED(hr)) return hr;

	// Create pixel shader
	hr = m_pSkybox->CreatePixelShader("Game Files/Game/Shaders/SkyboxShader.hlsl", "SkyboxPixelShader");
	if (FAILED(hr)) return hr;

	// Create the model and load it from the assets folder
	m_pWallModel = new Model(m_pD3DDevice, m_pImmediateContext);
	hr = m_pWallModel->LoadObjectModel("Assets/Models/cube.obj");
	if (FAILED(hr)) return hr;

	// Create constant buffer for models
	hr = m_pWallModel->CreateConstantBuffer();
	if (FAILED(hr)) return hr;

	// Add texture to the models
	hr = m_pWallModel->AddTexture("Assets/Textures/crate0_diffuse.png");
	if (FAILED(hr)) return hr;

	// Create filter for the texture
	hr = m_pWallModel->CreateSampler();
	if (FAILED(hr)) return hr;

	// Create vertex shader
	hr = m_pWallModel->CreateVertexShader("Game Files/Game/Shaders/ModelShader.hlsl", "ModelVertexShader");
	if (FAILED(hr)) return hr;

	// Create pixel shader
	hr = m_pWallModel->CreatePixelShader("Game Files/Game/Shaders/ModelShader.hlsl", "ModelPixelShader");
	if (FAILED(hr)) return hr;

	// Create the game objects
	m_pRootGameObject = new StaticGameObject();
	m_pWall1GameObject = new DynamicGameObject(defaultMovementSpeed, -5, 0, 2);
	m_pWall2GameObject = new DynamicGameObject(defaultMovementSpeed, 0, 0, 5);
	m_pWall3GameObject = new DynamicGameObject(defaultMovementSpeed, 5, 0, 2);
	m_pPushableGameObject1 = new PushableGameObject(m_pRootGameObject, defaultMovementSpeed, 0, 0, -20);
	m_pCollectible1 = new Collectible(scoreSaveLocation, 5, 0, 0);

	// Cameras
	m_pPrimaryCamera = new Camera(time, defaultMovementSpeed, 0.0f, 0.0f, -15.0f);
	m_pSecondaryCamera = new Camera(time, defaultMovementSpeed, -30, 0, 0);

	m_pActiveCamera = m_pPrimaryCamera;

	// Enemies
	m_pEnemy1 = new Enemy(25, defaultMovementSpeed / 2, 0, 0, 0);

	// Lights
	// TODO: REMOVE MAGIC NUMBERS
	m_pAmbientLight = new Light(0.1f, 0.1f, 0.1f);
	m_pDirectionalLight1 = new DirectionalLight(0.1f, 0.1f, 1, 0, 0, -1, 10, 0, 0, 1);
	m_pPointLight1 = new PointLight(0.1f, 1, 0.1f, -5, 0, 0, 10);

	// Set the children, models and positions
	m_pRootGameObject->AddChildNode(m_pWall1GameObject);
	m_pRootGameObject->AddChildNode(m_pWall2GameObject);
	m_pRootGameObject->AddChildNode(m_pWall3GameObject);
	m_pRootGameObject->AddChildNode(m_pCollectible1);
	m_pRootGameObject->AddChildNode(m_pPushableGameObject1);
	m_pRootGameObject->AddChildNode(m_pPrimaryCamera);
	m_pRootGameObject->AddChildNode(m_pEnemy1);

	// Set the models
	m_pWall1GameObject->SetModel(m_pWallModel);
	m_pWall2GameObject->SetModel(m_pWallModel);
	m_pWall3GameObject->SetModel(m_pWallModel);
	m_pCollectible1->SetModel(m_pWallModel);
	m_pPushableGameObject1->SetModel(m_pWallModel);
	m_pPrimaryCamera->SetModel(m_pWallModel);
	m_pSecondaryCamera->SetModel(m_pWallModel);
	m_pEnemy1->SetModel(m_pWallModel);

	// Transformations
	// Have to attach the secondary camera for the rotation to be applied correctly
	// It is removed afterwards since we don't want to render it and have collisions with it
	m_pRootGameObject->AddChildNode(m_pSecondaryCamera);
	m_pSecondaryCamera->IncrementXAngle(secondaryCameraRotation, m_pRootGameObject);
	m_pSecondaryCamera->IncrementZAngle(secondaryCameraRotation, m_pRootGameObject);
	m_pRootGameObject->DetachNode(m_pSecondaryCamera);

	// Set Lighting
	m_pWallModel->SetAmbientLight(m_pAmbientLight->GetLightColour());
	// TODO: Check range
	m_pWallModel->SetDirectionalLight(m_pDirectionalLight1->GetShineFromVector(), m_pDirectionalLight1->GetLightColour());
	m_pWallModel->SetPointLight(m_pPointLight1->GetShineFromVector(m_worldMatrix), m_pPointLight1->GetLightColour());

	return hr; // Should return S_OK if nothing fails
}

//####################################################################################
// Update any logic
//####################################################################################
void Level::Update(void)
{
	//m_pPrimaryCamera->IncrementYAngle(0.001f, m_pRootWallGameObject);
	//m_pWall3GameObject->IncrementZPos(m_pWall3GameObject->GetMovementSpeed(), m_pRootGameObject);

	m_pEnemy1->Update(m_pRootGameObject, m_pActiveCamera);
	m_pPointLight1->SetPosition(m_pPointLight1->GetPosition().vector4_f32[0] + 0.001f, 0, 0);
	m_pWallModel->SetPointLight(m_pPointLight1->GetShineFromVector(m_worldMatrix), m_pPointLight1->GetLightColour());
	m_pWall1GameObject->SetXPos(m_pPointLight1->GetPosition().vector4_f32[0]);
	m_pWall1GameObject->SetYPos(m_pPointLight1->GetPosition().vector4_f32[1]);
	m_pWall1GameObject->SetZPos(m_pPointLight1->GetPosition().vector4_f32[2]);
}

//####################################################################################
// Render objects
//####################################################################################
void Level::Render(void)
{
	// Only view is done here since we don't need to redo the world matrix unless it changes
	// The same goes for projection matrix
	XMMATRIX view;
	
	// Get the camera view
	view = m_pActiveCamera->GetViewMatrix();

	// Render all game objects in the level
	m_pRootGameObject->Render(&m_worldMatrix, &view, &m_projectionMatrix);

	// Render the skybox
	m_pSkybox->Draw(&GetSkyboxWorldMatrix(m_pSkybox->GetScale()), &view, &m_projectionMatrix);
}

//####################################################################################
// Move the active camera forward
//####################################################################################
void Level::MoveCameraForward(float movementMultiplier)
{
	m_pActiveCamera->MoveForward(m_pActiveCamera->GetMovementSpeed() * movementMultiplier, m_pRootGameObject);
}

//####################################################################################
// Move the active camera to the side
//####################################################################################
void Level::StrafeCamera(float movementMultiplier)
{
	m_pActiveCamera->Strafe(m_pActiveCamera->GetMovementSpeed() * movementMultiplier, m_pRootGameObject);
}

//####################################################################################
// Rotate the active camera to the sides
//####################################################################################
void Level::ChangeCameraXAndZDirection(float amount)
{
	// In order to do a full 360 both need to be incremented
	m_pActiveCamera->IncrementXAngle(amount, m_pRootGameObject);
	m_pActiveCamera->IncrementZAngle(amount, m_pRootGameObject);
}

//####################################################################################
// Rotate the active camera up and down
//####################################################################################
void Level::ChangeCameraYDirection(float amount)
{
	m_pActiveCamera->IncrementYAngle(amount, m_pRootGameObject);
}


//####################################################################################
// Change which camera is being used
//####################################################################################
void Level::ChangeActiveCamera(void)
{
	// Set new active camera
	// Detach old one and attach new one to the root node
	// This prevents collisions and rendering for the unused camera
	if (m_pActiveCamera == m_pPrimaryCamera)
	{
		m_pActiveCamera = m_pSecondaryCamera;
		m_pRootGameObject->AddChildNode(m_pSecondaryCamera);
		m_pRootGameObject->DetachNode(m_pPrimaryCamera);
	}
	else
	{
		m_pActiveCamera = m_pPrimaryCamera;
		m_pRootGameObject->AddChildNode(m_pPrimaryCamera);
		m_pRootGameObject->DetachNode(m_pSecondaryCamera);
	}
}

//####################################################################################
// Set the world matrix for rendering
//####################################################################################
void Level::SetWorldMatrix(float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float scale)
{
	m_worldMatrix = XMMatrixScaling(scale, scale, scale);
	m_worldMatrix *= XMMatrixRotationRollPitchYaw(xRot, yRot, zRot);
	m_worldMatrix *= XMMatrixTranslation(xPos, yPos, zPos);
}

//####################################################################################
// Set the projection matrix for rendering
//####################################################################################
void Level::SetProjectionMatrix(XMMATRIX projection)
{
	m_projectionMatrix = projection;
}

//####################################################################################
// Get the world matrix for the skybox
//####################################################################################
XMMATRIX Level::GetSkyboxWorldMatrix(float scale)
{
	// Use the current world matrix
	// Apply scaling first, then the translation
	// No rotation because it is axis aligned
	// We want to do that since we want the sky box at the same position of the camera
	XMMATRIX skyBoxWorldMatrix = m_worldMatrix;
	skyBoxWorldMatrix *= XMMatrixScaling(scale, scale, scale);
	skyBoxWorldMatrix *= XMMatrixTranslation(m_pActiveCamera->GetXPos(),
		m_pActiveCamera->GetYPos(), m_pActiveCamera->GetZPos());

	return skyBoxWorldMatrix;
}

//####################################################################################
// Get the player's health
//####################################################################################
int Level::GetPlayerHealth(void)
{
	return m_pActiveCamera->GetCurrentHealth();
}
