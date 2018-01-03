// *********************************************************
//	Name:			Stephen Wong
//	File:			SpecularModel.h
//	Last Updated:	03/01/2018
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "Model.h"

#pragma endregion

class SpecularModel : public Model
{
private:
	XMVECTOR m_specularLightShinesFrom;
	XMVECTOR m_specularLightColour;
	float m_specularLightIntestity;
public:
	SpecularModel(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	virtual HRESULT CreateConstantBuffer();
	virtual void SetConstantBufferValues(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection);

	void SetSpecularLight(XMVECTOR pos, XMVECTOR colour, float intesity);
};
