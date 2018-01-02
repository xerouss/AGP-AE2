// *********************************************************
//	Name:			Stephen Wong
//	File:			BasicModel.h
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

#pragma region Includes

#include "ObjectFileModel.h"

#pragma endregion

class BasicModel
{
protected:
	ID3D11Device* m_pD3DDevice;
	ID3D11DeviceContext* m_pImmediateContext;
	ObjectFileModel* m_pObject;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11InputLayout* m_pInputLayer;
	ID3D11Buffer* m_pConstantBuffer;
	ID3D11SamplerState* m_pSamplerState0;
	ID3D11ShaderResourceView* m_pTexture0;

public:
	BasicModel(ID3D11Device* device, ID3D11DeviceContext* immediateContext);
	~BasicModel();
	virtual int LoadObjectModel(char* filename);
	HRESULT CreateVertexShader(char* shaderFileName, char* vertexShaderFunctionName);
	HRESULT CreatePixelShader(char* shaderFileName, char* pixelShaderFunctionName);
	HRESULT CreateInputLayout(ID3DBlob *vertexShader);
	virtual HRESULT CreateConstantBuffer(UINT bufferBytes);
	HRESULT AddTexture(char* textureFileName);
	HRESULT CreateSampler(void);
	virtual void Draw(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection);
	virtual void SetConstantBufferValues(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection);
};