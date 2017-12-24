// *********************************************************
//	Name:			Stephen Wong
//	File:			ModelShader.hlsl
//	Last Updated:	05/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//####################################################################################
// Constant buffer
//####################################################################################
cbuffer cbuffer0
{
    matrix WVPMatrix; // 64
    float4 ambientLightColour; // 16
    float4 directionalLightVector; // 16
    float4 directionalLightColour; // 16
    float4 pointLightVector; // 16
    float4 pointLightColour; // 16

    // TOTAL: 144 bytes
};

Texture2D texture0;
SamplerState sampler0;

// Vertex output structure
struct VertexOut
{
    float4 position : SV_POSITION;
    float4 colour : COLOR;
    float2 texCoord : TEXCOORD;
};

//####################################################################################
// Vertex Shader
//####################################################################################
VertexOut ModelVertexShader(float4 position : POSITION, float2 texCoord : TEXCOORD, float3 normal : NORMAL)
{
    VertexOut output;

    output.position = mul(WVPMatrix, position);

    // Lighting
    output.colour = ambientLightColour; // Ambient Light Colour

    // Directional
    //float diffuseAmount = dot((float3) directionalLightVector, normal); // Light intensity
    //diffuseAmount = saturate(diffuseAmount); // Clamp value between 0 and 1 to stop problems on unlit faces
    //output.colour += (directionalLightColour * diffuseAmount);

    //// Point Light
    //float4 lightVector = pointLightVector - position;
    //lightVector = normalize(lightVector);
    //float pointAmount = dot((float3) lightVector, normal);
    //pointAmount = saturate(pointAmount);
    //output.colour += (pointLightColour * pointAmount);
    
    output.texCoord = texCoord;
    return output;
}

//####################################################################################
// Pixel Shader
//####################################################################################
float4 ModelPixelShader(float4 position : SV_POSITION, float4 colour : COLOR, float2 texCoord : TEXCOORD) : SV_TARGET
{
    return texture0.Sample(sampler0, texCoord) * colour;
}

