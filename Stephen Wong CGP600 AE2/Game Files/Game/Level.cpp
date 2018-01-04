// *********************************************************
//	Name:			Stephen Wong
//	File:			Level.cpp
//	Last Updated:	04/01/2018
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

	if (m_pSpecularLight)
	{
		delete m_pSpecularLight;
		m_pSpecularLight = NULL;
	}

	if (m_pPointLight)
	{
		delete m_pPointLight;
		m_pPointLight = NULL;
	}

	if (m_pDirectionalLight)
	{
		delete m_pDirectionalLight;
		m_pDirectionalLight = NULL;
	}

	if (m_pAmbientLight)
	{
		delete m_pAmbientLight;
		m_pAmbientLight = NULL;
	}

	if (m_pPointLightWallModel)
	{
		delete m_pPointLightWallModel;
		m_pPointLightWallModel;
	}

	if (m_pSpecularModelCube)
	{
		delete m_pSpecularModelCube;
		m_pSpecularModelCube = NULL;
	}

	if (m_pSpecularModelSphere)
	{
		delete m_pSpecularModelSphere;
		m_pSpecularModelSphere = NULL;
	}

	if (m_pReflectiveSphere)
	{
		delete m_pReflectiveSphere;
		m_pReflectiveSphere = NULL;
	}

	// Delete all pointers in the array
	if (m_pCollectibleModels)
	{
		delete m_pCollectibleModels;
		m_pCollectibleModels = NULL;
	}


	if (m_pMovingModel)
	{
		delete m_pMovingModel;
		m_pMovingModel = NULL;
	}

	// Delete all pointers in the array
	if (m_pPushableGameObjectModel)
	{
		delete m_pPushableGameObjectModel;
		m_pPushableGameObjectModel = NULL;
	}

	if (m_pEnemyBody)
	{
		delete m_pEnemyBody;
		m_pEnemyBody = NULL;
	}

	if (m_pEnemyHead)
	{
		delete m_pEnemyHead;
		m_pEnemyHead = NULL;
	}

	// Delete all pointers in the array
	if (m_pWallModels)
	{
		delete m_pWallModels;
		m_pWallModels = NULL;
	}

	//m_pWallModel.clear(); // Clear out the array

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

	/////////////////////////////////////////////////////////////////////////////
	// Create sky box
	m_pSkybox = new Skybox(skyboxScale, m_pD3DDevice, m_pImmediateContext);
	hr = CreateSkybox(m_pSkybox, "Assets/Models/cube.obj", "Assets/Skyboxes/skybox02.dds",
		"Game Files/Game/Shaders/SkyboxShader.hlsl", "SkyboxVertexShader", "SkyboxPixelShader");
	if (FAILED(hr)) return hr;

	hr = m_pSkybox->InitialiseSkybox();
	if (FAILED(hr)) return hr;
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Create wall models
	m_pWallModels = new Model(m_pD3DDevice, m_pImmediateContext);
	hr = CreateModel(m_pWallModels, "Assets/Models/cube.obj", "Assets/Textures/bricks.jpg",
		"Game Files/Game/Shaders/ModelShader.hlsl", "ModelVertexShader", "ModelPixelShader");
	if (FAILED(hr)) return hr;
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Create enemy models
	// Body
	m_pEnemyBody = new Model(m_pD3DDevice, m_pImmediateContext);
	hr = CreateModel(m_pEnemyBody, "Assets/Models/cube.obj", "Assets/Textures/Metal.png",
		"Game Files/Game/Shaders/ModelShader.hlsl", "ModelVertexShader", "ModelPixelShader");
	if (FAILED(hr)) return hr;

	m_pEnemyHead = new Model(m_pD3DDevice, m_pImmediateContext);
	hr = CreateModel(m_pEnemyHead, "Assets/Models/PointySphere.obj", "Assets/Textures/Metal.png",
		"Game Files/Game/Shaders/ModelShader.hlsl", "ModelVertexShader", "ModelPixelShader");
	if (FAILED(hr)) return hr;
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Create pushable game object models
	m_pPushableGameObjectModel = new Model(m_pD3DDevice, m_pImmediateContext);
	hr = CreateModel(m_pPushableGameObjectModel, "Assets/Models/cube.obj", "Assets/Textures/stone.jpg",
		"Game Files/Game/Shaders/ModelShader.hlsl", "ModelVertexShader", "ModelPixelShader");
	if (FAILED(hr)) return hr;
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Moving circle model
	m_pMovingModel = new Model(m_pD3DDevice, m_pImmediateContext);
	hr = CreateModel(m_pMovingModel, "Assets/Models/cube.obj", "Assets/Textures/crate0_diffuse.png",
		"Game Files/Game/Shaders/ModelShader.hlsl", "ModelVertexShader", "ModelPixelShader");
	if (FAILED(hr)) return hr;
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Create pushable game object models
	m_pCollectibleModels = new Model(m_pD3DDevice, m_pImmediateContext);
	hr = CreateModel(m_pCollectibleModels, "Assets/Models/sphere.obj", "Assets/Textures/gold.jpg",
		"Game Files/Game/Shaders/ModelShader.hlsl", "ModelVertexShader", "ModelPixelShader");
	if (FAILED(hr)) return hr;
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Create reflective sphere
	m_pReflectiveSphere = new ReflectiveModel(m_pD3DDevice, m_pImmediateContext);
	hr = CreateModel(m_pReflectiveSphere, "Assets/Models/sphere.obj", "Assets/Skyboxes/skybox02.dds",
		"Game Files/Game/Shaders/ReflectShader.hlsl", "ReflectVertexShader", "ReflectPixelShader");
	if (FAILED(hr)) return hr;
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Create the specular model
	m_pSpecularModelCube = new SpecularModel(m_pD3DDevice, m_pImmediateContext);
	hr = CreateModel(m_pSpecularModelCube, "Assets/Models/cube.obj", "Assets/Textures/glass1.png",
		"Game Files/Game/Shaders/SpecularShader.hlsl", "SpecularVertexShader", "SpecularPixelShader");
	if (FAILED(hr)) return hr;
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Create the specular model
	m_pSpecularModelSphere = new SpecularModel(m_pD3DDevice, m_pImmediateContext);
	hr = CreateModel(m_pSpecularModelSphere, "Assets/Models/sphere.obj", "Assets/Textures/glass1.png",
		"Game Files/Game/Shaders/SpecularShader.hlsl", "SpecularVertexShader", "SpecularPixelShader");
	if (FAILED(hr)) return hr;
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Create the point light model model
	m_pPointLightWallModel = new Model(m_pD3DDevice, m_pImmediateContext);
	hr = CreateModel(m_pPointLightWallModel, "Assets/Models/cube.obj", "Assets/Textures/bricks.jpg",
		"Game Files/Game/Shaders/PointLightShader.hlsl", "PointLightVertexShader", "PointLightPixelShader");
	if (FAILED(hr)) return hr;
	/////////////////////////////////////////////////////////////////////////////

	// Create root game object
	m_pRootGameObject = new StaticGameObject();

	/////////////////////////////////////////////////////////////////////////////
	// Lights
	m_pAmbientLight = new Light(ambientRGBColour, ambientRGBColour, ambientRGBColour);
	m_pDirectionalLight = new DirectionalLight(directionalRGColour, directionalRGColour, directionalBlueColour,
		zeroPosition, zeroPosition, directionalLightZPos, lightRange, zeroRotation, zeroRotation, directionalLightZRotation);
	m_pPointLight = new PointLight(pointLightRBColour, pointLightGColour, pointLightRBColour,
		zeroPosition, zeroPosition, pointLightZ, lightRange);
	m_pSpecularLight = new SpecularLight(specularLightIntensity, specularRGColour, specularRGColour,
		specularBlueColour, zeroPosition, zeroPosition, specularLightZPos, lightRange, zeroRotation, zeroRotation, specularLightZRotation);
	/////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////
	// Specular Model

	m_pSpecularGameObjectCube = new StaticGameObject(specularGameObjectX, zeroPosition, specularGameObjectZ);

	SetUpModelForGameObject(m_pSpecularModelCube, m_pSpecularGameObjectCube, m_pRootGameObject);
	m_pSpecularModelCube->SetSpecularLight(m_pSpecularLight->GetShineFromVector(m_worldMatrix), m_pSpecularLight->GetLightColour(), m_pSpecularLight->GetIntensity());

	m_pSpecularGameObjectSphere = new StaticGameObject(specularGameObjectX * 2, zeroPosition, specularGameObjectZ);
	m_pSpecularGameObjectSphere->SetScale(collectibleScale);
	SetUpModelForGameObject(m_pSpecularModelSphere, m_pSpecularGameObjectSphere, m_pRootGameObject);
	m_pSpecularModelSphere->SetSpecularLight(m_pSpecularLight->GetShineFromVector(m_worldMatrix), m_pSpecularLight->GetLightColour(), m_pSpecularLight->GetIntensity());

	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Reflection game object
	m_pReflectiveGameObject = new StaticGameObject(reflectiveGameObjectX, zeroPosition, camera1Z);

	// Don't call set up model for game object because it doesn't use lighting
	m_pReflectiveGameObject->SetModel(m_pReflectiveSphere);
	m_pRootGameObject->AddChildNode(m_pReflectiveGameObject);

	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Collectibles
	for (int i = 0; i < ARRAYSIZE(m_pCollectibles); i++)
	{
		m_pCollectibles[i] = new Collectible(scoreSaveLocation);

		// Set up model, parent node and lighting
		SetUpModelForGameObject(m_pCollectibleModels, m_pCollectibles[i], m_pRootGameObject);

		// Scale down because its a bit big
		m_pCollectibles[i]->SetScale(collectibleScale);
	}

	// Set collectible positions
	m_pCollectibles[0]->SetXPos(collectible1XPos);
	m_pCollectibles[1]->SetZPos(collectible2ZPos);
	m_pCollectibles[2]->SetXPos(collectible3XPos);
	m_pCollectibles[4]->SetZPos(collectible4ZPos);
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Moving game object
	m_pMovingGameObject = new DynamicGameObject(defaultMovementSpeed, zeroPosition, zeroPosition, movingZPos);
	// Set up model, parent node and lighting
	SetUpModelForGameObject(m_pMovingModel, m_pMovingGameObject, m_pRootGameObject);
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Cameras
	m_pPrimaryCamera = new Camera(time, defaultMovementSpeed * 2, zeroPosition, zeroPosition, camera1Z);
	m_pSecondaryCamera = new Camera(time, defaultMovementSpeed * 2, camera2X, zeroRotation, camera2Z);
	m_pActiveCamera = m_pPrimaryCamera;

	// Set up model, parent node and lighting
	SetUpModelForGameObject(m_pWallModels, m_pPrimaryCamera, m_pRootGameObject);
	SetUpModelForGameObject(m_pWallModels, m_pSecondaryCamera, m_pRootGameObject);

	// Rotate second camera
	// Have to attach the secondary camera for the rotation to be applied correctly
	// It is removed afterwards since we don't want to render it and have collisions with it
	m_pSecondaryCamera->IncrementXAngle(secondaryCameraRotation, m_pRootGameObject);
	m_pSecondaryCamera->IncrementZAngle(secondaryCameraRotation, m_pRootGameObject);
	m_pRootGameObject->DetachNode(m_pSecondaryCamera);
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Enemies
	m_pEnemy = new Enemy(enemyAggroRange, defaultMovementSpeed / enemySpeedChange, enemyXPos, enemyYPos, enemyZPos);
	m_pEnemyHeadObject = new StaticGameObject(enemyXPos, enemyYPos + enemyPositionHeadOffset, zeroPosition, zeroRotation,
		zeroRotation, zeroRotation, enemyHeadScale);

	// Set up model, parent node and lighting
	SetUpModelForGameObject(m_pEnemyHead, m_pEnemyHeadObject, m_pEnemy);

	// Set up model, parent node and lighting
	SetUpModelForGameObject(m_pEnemyBody, m_pEnemy, m_pRootGameObject);
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Pushable Game Objects
	m_pPushableGameObjects[0] = new PushableGameObject(m_pRootGameObject, defaultMovementSpeed,
		pushableGameObjectX, zeroPosition, pushableGameObject1Z);
	m_pPushableGameObjects[1] = new PushableGameObject(m_pRootGameObject, defaultMovementSpeed,
		pushableGameObjectX, zeroPosition, pushableGameObject2Z);

	// Add to root node and add models
	for (int i = 0; i < ARRAYSIZE(m_pPushableGameObjects); i++)
	{
		// Set up model, parent node and lighting
		SetUpModelForGameObject(m_pPushableGameObjectModel, m_pPushableGameObjects[i], m_pRootGameObject);
	}
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Wall Game Objects
	for (int i = 0; i < ARRAYSIZE(m_pWallGameObjects); i++)
	{
		m_pWallGameObjects[i] = new StaticGameObject();

		// Set up model, parent node and lighting
		SetUpModelForGameObject(m_pWallModels, m_pWallGameObjects[i], m_pRootGameObject);
	}

	// Set Wall positions
	m_pWallGameObjects[0]->SetZPos(enemyRoomWallBackZ);
	m_pWallGameObjects[0]->SetScale(bigWallScale);
	m_pWallGameObjects[1]->SetZPos(enemyRoomWallSideZ);
	m_pWallGameObjects[1]->SetXPos(enemyRoomWallRightX);
	m_pWallGameObjects[1]->SetScale(bigWallScale);
	m_pWallGameObjects[2]->SetZPos(enemyRoomWallSideZ);
	m_pWallGameObjects[2]->SetXPos(enemyRoomWallLeftX);
	m_pWallGameObjects[2]->SetScale(bigWallScale);

	m_pWallGameObjects[3]->SetZPos(enemyZPos + enemyTrappingWallOffset);
	m_pWallGameObjects[4]->SetZPos(enemyZPos);
	m_pWallGameObjects[4]->SetXPos(enemyXPos + enemyTrappingWallOffset);
	m_pWallGameObjects[5]->SetZPos(enemyZPos);
	m_pWallGameObjects[5]->SetXPos(enemyXPos - enemyTrappingWallOffset);
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// Point Light Game Object
	m_pPointLightWallGameObject = new StaticGameObject(zeroPosition, zeroPosition, pointLightZ);
	SetUpModelForGameObject(m_pPointLightWallModel, m_pPointLightWallGameObject, m_pRootGameObject);
	/////////////////////////////////////////////////////////////////////////////

	return hr; // Should return S_OK if nothing fails
}

//####################################################################################
// Update any logic
//####################################################################################
void Level::Update(void)
{
	// Update the enemy and the lighting on it
	m_pEnemy->Update(m_pRootGameObject, m_pActiveCamera);

	// Pass the enemy world rotation to the directional light so it the faces facing the directional light
	// Without this it would just light up the fron of the model even if it was facing away from the light
	XMMATRIX enemyWorldRotation = XMMatrixIdentity();
	enemyWorldRotation *= XMMatrixRotationX(m_pEnemy->GetXRotation());
	enemyWorldRotation *= XMMatrixRotationY(m_pEnemy->GetYRotation());
	enemyWorldRotation *= XMMatrixRotationZ(m_pEnemy->GetZRotation());

	// Lighting does not seem to update and just shines from the front
	m_pEnemyBody->SetDirectionalLight(m_pDirectionalLight->GetShineFromVector(enemyWorldRotation), m_pDirectionalLight->GetLightColour());
	m_pEnemyHead->SetDirectionalLight(m_pDirectionalLight->GetShineFromVector(enemyWorldRotation), m_pDirectionalLight->GetLightColour());

	// Move the game object along the x parallel with the point light
	m_pMovingGameObject->MoveForward(m_pMovingGameObject->GetMovementSpeed() * m_pointLightMovementDirection, m_pRootGameObject);


	// Get point light x
	float pointLightXPos = m_pPointLight->GetPosition().vector4_f32[x];

	// If above the light range, move back
	if (pointLightXPos > m_pPointLight->GetLightRange())
		m_pointLightMovementDirection = moveBackwards;
	// Else move forward
	else if (pointLightXPos < -m_pPointLight->GetLightRange())
		m_pointLightMovementDirection = moveForward;

	// Move the point light on the x
	m_pPointLight->SetPosition(m_pPointLight->GetPosition().vector4_f32[x] + (defaultMovementSpeed * m_pointLightMovementDirection),
		zeroPosition, pointLightZ);

	// Add the new point light info the model
	m_pPointLightWallModel->SetPointLight(m_pPointLight->GetShineFromVector(m_worldMatrix), m_pPointLight->GetLightColour());

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
// Set up the model
//####################################################################################
HRESULT Level::CreateModel(Model* model, char*  objectFileName, char*  textureFileName,
	char*  shaderFileName, char*  vertexShaderName, char*  pixelShaderName)
{
	HRESULT hr = S_OK;

	// Create constant buffer for models
	hr = model->CreateConstantBuffer();
	if (FAILED(hr)) return hr;

	hr = SetModelSettings(model, objectFileName, textureFileName, shaderFileName, vertexShaderName, pixelShaderName);
	return hr;
}

//####################################################################################
// Set up the sky box
// This is the same as create model but in different methods because the basic model
// Which they inherit from, the constant buffer takes a UINT parameter which is the
// Constant buffer size so they can't be one method which takes a basic model since
// We would have to pass a size we don't know. We also don't need to store the constant
// Buffer size too.
//####################################################################################
HRESULT Level::CreateSkybox(Skybox * model, char * objectFileName, char * textureFileName,
	char * shaderFileName, char * vertexShaderName, char * pixelShaderName)
{
	HRESULT hr = S_OK;

	// Create constant buffer for models
	hr = model->CreateConstantBuffer();
	if (FAILED(hr)) return hr;

	hr = SetModelSettings(model, objectFileName, textureFileName, shaderFileName, vertexShaderName, pixelShaderName);
	return hr;
}

//####################################################################################
// Set up the model setting (shaders, textures, models, etc)
//####################################################################################
HRESULT Level::SetModelSettings(BasicModel* model, char*  objectFileName, char*  textureFileName,
	char* shaderFileName, char*  vertexShaderName, char*  pixelShaderName)
{
	HRESULT hr = S_OK;

	hr = model->LoadObjectModel(objectFileName);
	if (FAILED(hr)) return hr;

	// Add texture to the models
	hr = model->AddTexture(textureFileName);
	if (FAILED(hr)) return hr;

	// Create filter for the texture
	hr = model->CreateSampler();
	if (FAILED(hr)) return hr;

	// Create vertex shader
	hr = model->CreateVertexShader(shaderFileName, vertexShaderName);
	if (FAILED(hr)) return hr;

	// Create pixel shader
	hr = model->CreatePixelShader(shaderFileName, pixelShaderName);

	return hr;
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

//####################################################################################
// Set directional and ambient light to a model
//####################################################################################
void Level::SetUpModelForGameObject(Model* model, StaticGameObject* gameObject, StaticGameObject* root)
{
	// Add game object to root for collision and rendering
	root->AddChildNode(gameObject);

	// Set model
	gameObject->SetModel(model);

	XMVECTOR ambientLightColour = m_pAmbientLight->GetLightColour();
	XMVECTOR directionalLightPos = m_pDirectionalLight->GetShineFromVector(m_worldMatrix);
	XMVECTOR directionalLightColour = m_pDirectionalLight->GetLightColour();

	// Add lighting to them
	model->SetDirectionalLight(directionalLightPos, directionalLightColour);
	model->SetAmbientLight(ambientLightColour);
}
