cbuffer MatrixBuffer : register(b0)
{
    matrix ortho;
};

struct VSInput
{
    float4 pos : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct VSOutput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    output.pos = mul(input.pos, ortho);
    output.color = input.color;
    output.uv = input.uv;
    return output;
}
