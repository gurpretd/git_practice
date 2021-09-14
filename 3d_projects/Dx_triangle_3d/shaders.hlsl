// This is the Input Layout [see CreateInputLayout()] we specified in the CPU part of our program - the input to the vertex shader 
struct VS_Input
{
    float3 pos : POSITION;
    float2 uvcoord : TEXCOORD;
};

cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
}

// this is the output of the vertex shader, per vertex
struct VS_Output
{
    float4 position : SV_POSITION; // SV POSITION is a semantic that tells the system the intended use is position
    float2 uvcoord : TEXCOORD;
};

// Vertex Shader
//
// Input Type:  VS_Input  [One per vertex]
// Output Type: VS_Output [One per vertex]
//
VS_Output vs_main(VS_Input input)
{
    VS_Output output = (VS_Output)0;
    output.position = mul(float4(input.pos, 1.0), World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
    output.uvcoord = input.uvcoord;

    return output;
}

// Pixel Shader
//
// Input Type:  VS_Output [One per vertex, but interpolated for _each_ rasterized pixel]
// Output Type: float4    [The color (target value) for each pixel, SV => System Value, also know as a system semantic]
//
float4 ps_main(VS_Output input) : SV_TARGET
{
    float4 outcol = float4(input.uvcoord.x, input.uvcoord.y, 1.0, 1.0);
    return outcol;
}


