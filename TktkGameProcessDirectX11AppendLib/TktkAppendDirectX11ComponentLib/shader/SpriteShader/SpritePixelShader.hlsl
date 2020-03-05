cbuffer ConstantBuffer : register(b0)
{
	float2 textureUvOffset;
	float2 textureUvMulRate;
	float2 textureSize;
	float2 spritePosition;
	float2 spriteScaleRate;
	float spriteAngleDeg;
	float padding;
	float4 blendRate;
	float2 spriteCenterRate;
	float2 screenSize;
};

struct PS_INPUT
{
	float2 texcoord : TEXCOORD0;
	float4 position : SV_POSITION;
};

Texture2D TextureMapTexture : register(t0);
SamplerState TextureMapSampler : register(s0);

float4 main(PS_INPUT input) : SV_Target
{
	return TextureMapTexture.Sample(TextureMapSampler, input.texcoord) * blendRate;
}