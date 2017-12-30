// *********************************************************
//	Name:			Stephen Wong
//	File:			UserInterface.cpp
//	Last Updated:	29/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "UserInterface.h"

#pragma endregion

//####################################################################################
// Constructor
//####################################################################################
UserInterface::UserInterface(ID3D11Device* device, ID3D11DeviceContext* immediateContext)
{
	m_pImmediateContext = immediateContext;
	
	InitialiseTransparency(device);
}

//####################################################################################
// Destructor
//####################################################################################
UserInterface::~UserInterface()
{
	if (m_pAlphaBlendEnable) m_pAlphaBlendEnable->Release();
	if (m_pAlphaBlendDisable) m_pAlphaBlendDisable->Release();
}

//####################################################################################
// Render user interface
//####################################################################################
void UserInterface::Render(void)
{
	// Is blank since all children of user interface will have this but will need to
	// Be implemented individually.
}

//####################################################################################
// Set whether  the transparency is active or not
//####################################################################################
void UserInterface::SetTransparencyActive(bool active)
{
	if (active)
	{
		// Enable transparency
		m_pImmediateContext->OMSetBlendState(m_pAlphaBlendEnable, 0, blendStateSampleMask);
	}
	else
	{
		// Disable transparency
		m_pImmediateContext->OMSetBlendState(m_pAlphaBlendDisable, 0, blendStateSampleMask);
	}
}

//####################################################################################
// Set transparency for text
//####################################################################################
void UserInterface::InitialiseTransparency(ID3D11Device * device)
{
	// Set up blend for transparency
	// Used mainly for text
	D3D11_BLEND_DESC blendDesc;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.AlphaToCoverageEnable = false;

	// Create the blend state and save it
	device->CreateBlendState(&blendDesc, &m_pAlphaBlendEnable);
}
