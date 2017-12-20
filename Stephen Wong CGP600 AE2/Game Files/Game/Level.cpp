// *********************************************************
//	Name:			Stephen Wong
//	File:			Level.cpp
//	Last Updated:	20/12/2017
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
	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}

	if (m_pWallModel)
	{
		delete m_pWallModel;
		m_pWallModel = NULL;
	}

	// Only delete the root node since the nodes attached to it will be deleted
	if (m_pRootWallGameObject)
	{
		delete m_pRootWallGameObject;
		m_pRootWallGameObject = NULL;
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
	m_pRootWallGameObject = new StaticGameObject();
	m_pWall1GameObject = new DynamicGameObject(-5, 0, 0);
	m_pWall2GameObject = new DynamicGameObject(0, 0, -20);
	m_pWall3GameObject = new DynamicGameObject(5, 0, -10);
	m_pPushableGameObject1 = new PushableGameObject(m_pRootWallGameObject, 0, 0, 0);
	m_pCollectible1 = new Collectible(m_scoreSaveLocation, 5, 0, 0);
	m_pCamera = new Camera(0.0f, 0.0f, -15.0f);

	// Set the children, models and positions
	m_pRootWallGameObject->AddChildNode(m_pWall1GameObject);
	m_pRootWallGameObject->AddChildNode(m_pWall2GameObject);
	m_pRootWallGameObject->AddChildNode(m_pWall3GameObject);
	m_pRootWallGameObject->AddChildNode(m_pCollectible1);
	m_pRootWallGameObject->AddChildNode(m_pPushableGameObject1);
	m_pRootWallGameObject->AddChildNode(m_pCamera);

	// Set the models
	m_pWall1GameObject->SetModel(m_pWallModel);
	m_pWall2GameObject->SetModel(m_pWallModel);
	m_pWall3GameObject->SetModel(m_pWallModel);
	m_pCollectible1->SetModel(m_pWallModel);
	m_pPushableGameObject1->SetModel(m_pWallModel);
	m_pCamera->SetModel(m_pWallModel);

	return hr; // Should return S_OK if nothing fails
}

//####################################################################################
// Update any logic
//####################################################################################
void Level::Update(void)
{
	//m_pCamera->IncrementYAngle(0.001f, m_pRootWallGameObject);
	m_pWall3GameObject->IncrementZPos(0.001f, m_pRootWallGameObject);
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

	m_pRootWallGameObject->Update(&m_worldMatrix, &view, &m_projectionMatrix);
}

void Level::MoveCameraForward(float movementMultiplier)
{
	m_pCamera->MoveForward(m_pCamera->GetMovementSpeed() * movementMultiplier, m_pRootWallGameObject);
}

void Level::StrafeCamera(float movementMultiplier)
{
	m_pCamera->Strafe(m_pCamera->GetMovementSpeed() * movementMultiplier, m_pRootWallGameObject);
}

void Level::ChangeCameraDirection(float amount)
{
	// In order to do a full 360 both need to be incremented
	m_pCamera->IncrementXAngle(amount, m_pRootWallGameObject);
	m_pCamera->IncrementZAngle(amount, m_pRootWallGameObject);
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
