// *********************************************************
//	Name:			Stephen Wong
//	File:			Level.cpp
//	Last Updated:	09/12/2017
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
HRESULT Level::SetUpLevel(void)
{
	HRESULT hr = S_OK;

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
	m_pWall1GameObject = new DynamicGameObject();
	m_pWall2GameObject = new DynamicGameObject();

	// Set the children, models and positions
	m_pRootWallGameObject->AddChildNode(m_pWall1GameObject);
	m_pRootWallGameObject->AddChildNode(m_pWall2GameObject);
	m_pWall1GameObject->SetModel(m_pWallModel);
	m_pWall2GameObject->SetModel(m_pWallModel);
	//m_pRootWallGameObject->AddChildNode(m_pCamera);
	m_pWall1GameObject->SetZPos(10);


	m_pCamera = new Camera(0.0f, 0.0f, 0.0f);

	return hr; // Should return S_OK if nothing fails
}

//####################################################################################
// Update any logic
//####################################################################################
void Level::Update(void)
{
	//m_pCamera->IncrementYAngle(0.001f, m_pRootWallGameObject);
	//m_pWall1GameObject->IncrementZPos(0.001f, m_pRootWallGameObject);
}

//####################################################################################
// Render objects
//####################################################################################
void Level::Render(void)
{
	// TODO MOVE THIS?
	// Could move this to game manager, pass down the value including the screen width/height
	// Or keep it here and just pass the with/height
	XMMATRIX world, projection, view;

	// Depending on the z position it will either move it closer or further away
	world = XMMatrixRotationRollPitchYaw(0, 0, 0);
	world *= XMMatrixTranslation(0, 0, 15.0f); // World transformation
	
	// TODO: CHANGE THIS
	// Change the width and height so its dynamic
	projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0f), 640 / 480, 1.0f, 100.0f); // Projection transformation
	view = m_pCamera->GetViewMatrix(); // Change this to camera 

	m_pRootWallGameObject->Update(&world, &projection, &view);
}

void Level::MoveCameraForward(float distance)
{
	m_pCamera->MoveForward(distance);
}

void Level::MoveCameraLeft(float distance)
{
}

void Level::MoveCameraRight(float distance)
{
}

void Level::ChangeCameraDirection(float amount)
{
	//m_pCamera->IncrementXAngle(amount, m_pRootWallGameObject);
}
