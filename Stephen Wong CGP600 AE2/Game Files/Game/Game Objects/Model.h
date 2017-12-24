// *********************************************************
//	Name:			Stephen Wong
//	File:			Model.h
//	Last Updated:	24/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "ObjectFileModel.h"

#pragma endregion

class Model
{
private:
	ID3D11Device* m_pD3DDevice;
	ID3D11DeviceContext* m_pImmediateContext;
	ObjectFileModel* m_pObject;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11InputLayout* m_pInputLayer;
	ID3D11Buffer* m_pConstantBuffer;
	ID3D11SamplerState* m_pSamplerState0;
	// TODO: Add more textures?
	ID3D11ShaderResourceView* m_pTexture0;

	#pragma region Lights
		XMVECTOR m_ambientLightColour;
		XMVECTOR m_directionalLightShinesFrom;
		XMVECTOR m_directionalLightColour;
		XMVECTOR m_pointLightPosition;
		XMVECTOR m_pointLightColour;
	#pragma endregion

#pragma region Bounding Sphere Collision
	float m_boundingSphereCentreX;
	float m_boundingSphereCentreY;
	float m_boundingSphereCentreZ;
	float m_boundingSphereRadius;

	// These methods are private since they are called internerally when the object model is loaded
	void CalculateModelCentrePoint(void);
	void CalculateBoundingSphereRadius(void);
	float GetMidPointFromTwoFloats(float point1, float point2);
#pragma endregion

public:
	Model(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	~Model();
	int LoadObjectModel(char* filename);
	HRESULT CreateVertexShader(char* shaderFileName, char* vertexShaderFunctionName);
	HRESULT CreatePixelShader(char* shaderFileName, char* pixelShaderFunctionName);
	HRESULT CreateInputLayout(ID3DBlob *vertexShader);
	HRESULT CreateConstantBuffer();
	HRESULT AddTexture(char* textureFileName);
	HRESULT CreateSampler(void);
	void Draw(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection);

#pragma region Set Methods

	// Lights
	void SetAmbientLight(XMVECTOR colour);
	void SetDirectionalLight(XMVECTOR pos, XMVECTOR colour);
	void SetPointLight(XMVECTOR pos, XMVECTOR colour);

#pragma endregion

#pragma region Get Methods

	//Lights
	//XMVECTOR GetAmbientLightColour(void);
	//XMVECTOR GetDirectionalLightPos(void);
	//XMVECTOR GetDirectionalLightColour(void);
	//XMVECTOR GetPointLightPos(void);
	//XMVECTOR GetPointLightColour(void);

	// Collision
	float GetBoundingSphereRadius(void);
	float GetBoundingSphereX(void);
	float GetBoundingSphereY(void);
	float GetBoundingSphereZ(void);

#pragma endregion

};