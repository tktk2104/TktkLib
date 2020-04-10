
cbuffer cbuff0 : register(b0)
{
	float4x4 mat;
}

struct VSInput
{
	float4 pos	: POSITION;
	float2 uv	: TEXCOORD;
};

struct VSOutput
{
	float4 pos	: SV_POSITION;
	float2 uv	: TEXCOORD;
};

VSOutput main(VSInput input)
{
	VSOutput output;
	output.pos = mul(mat, input.pos);
	output.uv = input.uv;
	return output;
}