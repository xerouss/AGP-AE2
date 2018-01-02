// *********************************************************
//	Name:			Stephen Wong
//	File:			SkyboxShader.hlsl
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************

//####################################################################################
// Constant buffer
//####################################################################################
cbuffer cbuffer0
{
    matrix WVPMatrix; // 64

    // TOTAL: 64 bytes
};

TextureCube cube0;
SamplerState sampler0;

// Vertex output structure
struct VertexOut
{
    float4 position : SV_POSITION;
    float3 texCoord : TEXCOORD;
};

//####################################################################################
// Vertex Shader
//####################################################################################
VertexOut SkyboxVertexShader(float4 position : POSITION, float2 texCoord : TEXCOORD, float3 normal : NORMAL)
{
    VertexOut output;

    output.position = mul(WVPMatrix, position);
    
    output.texCoord = position.xyz;
    return output;
}

//####################################################################################
// Pixel Shader
//####################################################################################
float4 SkyboxPixelShader(float4 position : SV_POSITION, float3 texCoord : TEXCOORD) : SV_TARGET
{
    return cube0.Sample(sampler0, texCoord);
}

