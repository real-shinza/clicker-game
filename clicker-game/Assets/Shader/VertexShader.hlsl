float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}

struct VSOutput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

VSOutput VSMain(float4 pos : POSITION, float4 color : COLOR, float2 uv : TEXCOORD)
{
    VSOutput output;
    output.pos = pos;
    output.color = color;
    output.uv = uv;
	
    return output;
}
