float4 main() : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}

struct PSInput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

float4 PSMain(PSInput input) : SV_TARGET
{
    return input.color;
}