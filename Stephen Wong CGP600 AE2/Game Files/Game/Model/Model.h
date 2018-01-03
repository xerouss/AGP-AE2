// *********************************************************
//	Name:			Stephen Wong
//	File:			Model.h
//	Last Updated:	03/01/2018
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "BasicModel.h"

#pragma endregion

class Model : public BasicModel
{
private:
#pragma region Lights
	XMVECTOR m_directionalLightShinesFrom;
	XMVECTOR m_pointLightPosition;
	XMVECTOR m_pointLightColour;
#pragma endregion

#pragma region Bounding Sphere Collision
	float m_boundingSphereCentreX;
	float m_boundingSphereCentreY;
	float m_boundingSphereCentreZ;
	float m_boundingSphereRadius;

	// These methods are private since they are called internally when the object model is loaded
	void CalculateModelCentrePoint(void);
	void CalculateBoundingSphereRadius(void);
	float GetMidPointFromTwoFloats(float point1, float point2);
#pragma endregion

protected:
	XMVECTOR m_ambientLightColour;
	XMVECTOR m_directionalLightColour;

public:
	Model(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	virtual HRESULT CreateConstantBuffer();
	virtual void SetConstantBufferValues(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection);
	int LoadObjectModel(char* filename);

#pragma region Set Methods

	// Lights
	void SetAmbientLight(XMVECTOR colour);
	void SetDirectionalLight(XMVECTOR pos, XMVECTOR colour);
	void SetPointLight(XMVECTOR pos, XMVECTOR colour);

#pragma endregion

#pragma region Get Methods

	// Collision
	float GetBoundingSphereRadius(void);
	float GetBoundingSphereX(void);
	float GetBoundingSphereY(void);
	float GetBoundingSphereZ(void);

#pragma endregion

};