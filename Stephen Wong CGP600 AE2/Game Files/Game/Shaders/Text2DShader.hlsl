// *********************************************************
//	Name:			Stephen Wong
//	File:			Text2DShader.hlsl
//	Last Updated:	17/12/2017
//	Project:		CGP600 AE2
// *********************************************************
// #########################################################
// THIS IS THE SAME SCRIPT FROM THE SOLENT ONLINE LEARNING
// PAGE FOR TUTORIAL 9.
// THE MODIFCATIONS I MADE WAS I CHANGED THE NAME OF THE
// CLASS FROM text2D_shader TO Text2DShader, VARIABLE NAMES
// + ADDED COMMENTS
// #########################################################
// *********************************************************

Texture2D texture0;
SamplerState sampler0;

// Vertex output structure
struct VertexOut
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
};

//####################################################################################
// Vertex Shader
//####################################################################################
VertexOut TextVS(float4 position : POSITION, float2 texcoord : TEXCOORD)
{
    VertexOut output;

    output.position = position;

    output.texcoord = texcoord;

    return output;
}

//####################################################################################
// Pixel Shader
//####################################################################################
float4 TextPS(float4 position : SV_POSITION, float2 texcoord : TEXCOORD) : SV_TARGET
{
    return texture0.Sample(sampler0, texcoord);
}