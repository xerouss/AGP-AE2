// *********************************************************
//	Name:			Stephen Wong
//	File:			ReflectShader.hlsl
//	Last Updated:	02/01/2018
//	Project:		CGP600 AE2
// *********************************************************

//####################################################################################
// Constant buffer
//####################################################################################
cbuffer cbuffer0
{
    matrix WVPMatrix; // 64
    matrix worldViewMatrix; // 64
    // TOTAL: 128 bytes
};

TextureCube cube0;
SamplerState sampler0;

// Vertex output structure
struct VertexOut
{
    float4 position : SV_POSITION;
    float4 colour : COLOR;
    float3 texCoord : TEXCOORD;
};

//####################################################################################
// Vertex Shader
//####################################################################################
VertexOut ReflectVertexShader(float4 position : POSITION, float2 texCoord : TEXCOORD, float3 normal : NORMAL)
{
    VertexOut output;

    // Position
    output.position = mul(WVPMatrix, position);

    // Position relative to the camera
    // Save xyz since it returns a float 4
    float3 worldViewPosition =  mul(worldViewMatrix, position).xyz;

    // Normal relative to the camera
    // Save xyz since it returns a float 4
    // Need to float4 the normal since it is originally a float3 and would cause errors without it
    float3 worldViewNormal = mul(worldViewMatrix, float4(normal, 0)).xyz;
    worldViewNormal = normalize(worldViewNormal);

    // Get the reverse eye vector
    float3 eyeVector = -normalize(worldViewPosition);

    output.texCoord = (2.0 * dot(eyeVector, worldViewNormal) * worldViewNormal - eyeVector).xyz;

    output.colour = float4(0.2, 0.2, 0.2, 1);
    return output;
}

//####################################################################################
// Pixel Shader
//####################################################################################
float4 ReflectPixelShader(float4 position : SV_POSITION, float4 colour : COLOR, float3 texCoord : TEXCOORD) : SV_TARGET
{
    return cube0.Sample(sampler0, texCoord) + (colour / 2);
}

