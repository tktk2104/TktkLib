cbuffer ConstantBuffer : register(b0)
{
	float3x3 worldMatrix;
	float4 blendRate;
	float2 textureUvOffset;
	float2 textureUvMulRate;
	float2 textureSize;
	float2 spriteCenterRate;
	float2 screenSize;
	float2 pad;
};

struct PS_INPUT
{
	float2 texcoord : TEXCOORD0;
	float4 position : SV_POSITION;
};

Texture2D<float>	TextureMapTexture : register(t0);
SamplerState		TextureMapSampler : register(s0);

float4 main(PS_INPUT input) : SV_Target
{
	float temp = TextureMapTexture.Sample(TextureMapSampler, input.texcoord);
	
	return float4(temp, temp, temp, 1.0) * blendRate;
}