cbuffer ConstantBuffer : register(b0)
{
	float2 texturePosition;
	float2 textureSize;
	float2 size;
	float2 position;
	float2 scale;
	float angle;
	float padding;
	float4 color;
	float2 center;
	float2 screen;
};

struct PS_INPUT
{
	float2 texcoord : TEXCOORD0;
	float4 position : SV_POSITION;
};

//Texture2D TextureMapTexture : register(t0);

TextureCube TextureMapTexture : register(t0);
SamplerState TextureMapSampler : register(s0);

float4 main(PS_INPUT input) : SV_Target
{
	return TextureMapTexture.Sample(TextureMapSampler, 
		float3(
			(input.texcoord.x * 2) - 1.0,
			-1.0,
			-((input.texcoord.y * 2) - 1.0)
			)
	) * color;
}