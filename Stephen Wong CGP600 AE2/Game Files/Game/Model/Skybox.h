// *********************************************************
//	Name:			Stephen Wong
//	File:			Skybox.h
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "BasicModel.h"

#pragma endregion

class Skybox : public BasicModel
{
private:
	ID3D11RasterizerState* m_pRasterSolid = 0;
	ID3D11RasterizerState* m_pRasterSkybox = 0;
	ID3D11DepthStencilState* m_pDepthWriteSolid = 0;
	ID3D11DepthStencilState* m_pDepthWriteSkybox = 0;
	float m_scale;

public:
	Skybox(float scale, ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	~Skybox();
	HRESULT InitialiseSkybox(void);
	HRESULT CreateConstantBuffer(void);
	void Draw(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection);
	void SetConstantBufferValues(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection);

	float GetScale(void);

};
