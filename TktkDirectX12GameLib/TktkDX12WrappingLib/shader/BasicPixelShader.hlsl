
Texture2D<float4>	tex : register(t0);
SamplerState		smp : register(s0);

struct PSInput
{
	float4 pos	: SV_POSITION;
	float2 uv	: TEXCOORD;
};

float4 main(PSInput input) : SV_TARGET
{
	return float4(tex.Sample(smp, input.uv));
}