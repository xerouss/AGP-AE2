// *********************************************************
//	Name:			Stephen Wong
//	File:			Level.cpp
//	Last Updated:	23/12/2017
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
}

//####################################################################################
// Place the game objects around the level to create it
//####################################################################################
HRESULT Level::SetUpLevel(int* m_scoreSaveLocation)
{
	HRESULT hr = S_OK;

	// Set up world matrix
	SetWorldMatrix(defaultWorldMatrixValue, defaultWorldMatrixValue, defaultWorldMatrixValue,
		defaultWorldMatrixValue, defaultWorldMatrixValue, defaultWorldMatrixValue, 1);

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
	m_pCollectible1 = new Collectible(m_scoreSaveLocation, 5, 0, 0);
	m_pCamera = new Camera(defaultMovementSpeed, 0.0f, 0.0f, -15.0f);
	m_pEnemy1 = new Enemy(defaultMovementSpeed, 0, 0, 0);
	m_pAmbientLight = new Light(1, 0.2f, 0.2f);

	// Set the children, models and positions
	m_pRootGameObject->AddChildNode(m_pWall1GameObject);
	m_pRootGameObject->AddChildNode(m_pWall2GameObject);
	m_pRootGameObject->AddChildNode(m_pWall3GameObject);
	m_pRootGameObject->AddChildNode(m_pCollectible1);
	m_pRootGameObject->AddChildNode(m_pPushableGameObject1);
	m_pRootGameObject->AddChildNode(m_pCamera);
	m_pRootGameObject->AddChildNode(m_pEnemy1);

	// Set the models
	m_pWall1GameObject->SetModel(m_pWallModel);
	m_pWall2GameObject->SetModel(m_pWallModel);
	m_pWall3GameObject->SetModel(m_pWallModel);
	m_pCollectible1->SetModel(m_pWallModel);
	m_pPushableGameObject1->SetModel(m_pWallModel);
	m_pCamera->SetModel(m_pWallModel);
	m_pEnemy1->SetModel(m_pWallModel);

	// Set Lighting
	m_pWallModel->SetAmbientLight(m_pAmbientLight->GetLightColour());

	return hr; // Should return S_OK if nothing fails
}

//####################################################################################
// Update any logic
//####################################################################################
void Level::Update(void)
{
	//m_pCamera->IncrementYAngle(0.001f, m_pRootWallGameObject);
	//m_pWall3GameObject->IncrementZPos(m_pWall3GameObject->GetMovementSpeed(), m_pRootGameObject);

	m_pEnemy1->Update(m_pRootGameObject);
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
	view = m_pCamera->GetViewMatrix();

	// Render all game objects in the level
	m_pRootGameObject->Render(&m_worldMatrix, &view, &m_projectionMatrix);
}

void Level::MoveCameraForward(float movementMultiplier)
{
	m_pCamera->MoveForward(m_pCamera->GetMovementSpeed() * movementMultiplier, m_pRootGameObject);
}

void Level::StrafeCamera(float movementMultiplier)
{
	m_pCamera->Strafe(m_pCamera->GetMovementSpeed() * movementMultiplier, m_pRootGameObject);
}

void Level::ChangeCameraDirection(float amount)
{
	// In order to do a full 360 both need to be incremented
	m_pCamera->IncrementXAngle(amount, m_pRootGameObject);
	m_pCamera->IncrementZAngle(amount, m_pRootGameObject);
}

void Level::SetWorldMatrix(float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float scale)
{
	m_worldMatrix = XMMatrixScaling(scale, scale, scale);
	m_worldMatrix *= XMMatrixRotationRollPitchYaw(xRot, yRot, zRot);
	m_worldMatrix *= XMMatrixTranslation(xPos, yPos, zPos);
}

void Level::SetProjectionMatrix(XMMATRIX projection)
{
	m_projectionMatrix = projection;
}

int Level::GetPlayerHealth(void)
{
	return m_pCamera->GetCurrentHealth();
}
