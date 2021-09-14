// This is the Input Layout [see CreateInputLayout()] we specified in the CPU part of our program - the input to the vertex shader
struct VS_Input
{
    float3 pos : POS;
    float4 color : COL;
};

// this is the output of the vertex shader, per vertex
struct VS_Output
{
    float4 position : SV_POSITION; // SV POSITION is a semantic that tells the system the intended use is position
    float4 color : COL;
};

// Vertex Shader
//
// Input Type:  VS_Input  [One per vertex]
// Output Type: VS_Output [One per vertex]
//
VS_Output vs_main(VS_Input input)
{
    VS_Output output;
    output.position = float4(input.pos, 1.0f);
    output.color = input.color;

    return output;
}

// Pixel Shader
//
// Input Type:  VS_Output [One per vertex, but interpolated for _each_ rasterized pixel]
// Output Type: float4    [The color (target value) for each pixel, SV => System Value, also know as a system semantic]
//
float4 ps_main(VS_Output input) : SV_TARGET
{
    return input.color;
}
