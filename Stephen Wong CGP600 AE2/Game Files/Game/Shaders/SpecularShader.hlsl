// *********************************************************
//	Name:			Stephen Wong
//	File:			SpecularShader.hlsl
//	Last Updated:	03/01/2018
//	Project:		CGP600 AE2
// *********************************************************

// Used both of these to implement this:
// http://www.rastertek.com/dx11tut10.html (Rastertek, n.d.) Last viewed: 03/01/2018
// https://www.3dgep.com/texturing-lighting-directx-11/#Specular (Oosten 2014) Last viewed: 03/01/2018

//####################################################################################
// Constant buffer
//####################################################################################
cbuffer cbuffer0
{
    matrix WVPMatrix; // 64
    float4 ambientLightColour; // 16
    float4 specularLightVector; // 16
    float4 specularLightColour; // 16
    float specularIntensity; // 4
    float packingBytes1; // 4
    float packingBytes2; // 4
    float packingBytes3; // 4
    float4 directionalLightColour; // 16
    matrix worldViewMatrix; // 64

    // TOTAL: 224 bytes
};

Texture2D texture0;
SamplerState sampler0;

// Vertex output structure
struct VertexOut
{
    float4 position : SV_POSITION;
    float4 normal : NORMAL;
    float2 texCoord : TEXCOORD;
    float3 eyeVector : EYEVECTOR;
};

//####################################################################################
// Vertex Shader
//####################################################################################
VertexOut SpecularVertexShader(float4 position : POSITION, float2 texCoord : TEXCOORD, float4 normal : NORMAL)
{
    VertexOut output;

    output.position = mul(WVPMatrix, position);

    // Position relative to the camera
    // Save xyz since it returns a float 4
    float3 worldViewPosition = mul(worldViewMatrix, position).xyz;
    // Get the reverse eye vector
    output.eyeVector = -normalize(worldViewPosition);
    
    output.normal = normal;
    output.texCoord = texCoord;
    return output;
}

//####################################################################################
// Pixel Shader
//####################################################################################
float4 SpecularPixelShader(float4 position : SV_POSITION, float3 normal : NORMAL, float2 texCoord : TEXCOORD,
float3 eyeVector : EYEVECTOR) : SV_TARGET
{
    float4 colour = ambientLightColour;
    // Calculate the intensity of the light
    float lightIntesity = saturate(dot(normal, float3(specularLightVector.xyz)));
    float4 specular = float4(0, 0, 0, 0);

    // Prevents doing the calculation if there is no light on it
    if (lightIntesity > 0.0f)
    {
        // Add the directional Light colour
        colour += (directionalLightColour * lightIntesity);

        // Saturate it
        colour = saturate(colour);

        // Work out the reflection and the specular
        float3 reflection = normalize(2 * lightIntesity * normal - float3(specularLightVector.xyz));
        specular = pow(saturate(dot(reflection, eyeVector)), specularIntensity);

    }

    // Add the colour to the texture
    colour = colour * texture0.Sample(sampler0, texCoord);
    // Saturate the colour while adding the specular
    colour = saturate(colour + specular);

    return colour;
}

