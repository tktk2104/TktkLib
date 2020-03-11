cbuffer ConstantBuffer : register(b0)
{
	float4 lineColor;
};

struct PS_INPUT
{
	float4 position : SV_POSITION;
};

float4 main(PS_INPUT input) : SV_Target
{
	return lineColor;
}