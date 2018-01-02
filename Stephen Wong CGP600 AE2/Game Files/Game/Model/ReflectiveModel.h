// *********************************************************
//	Name:			Stephen Wong
//	File:			ReflectiveModel.h
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "Model.h"

#pragma endregion

class ReflectiveModel : public Model
{
private:

public:
	ReflectiveModel(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	virtual HRESULT CreateConstantBuffer();
	virtual void SetConstantBufferValues(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection);
};
