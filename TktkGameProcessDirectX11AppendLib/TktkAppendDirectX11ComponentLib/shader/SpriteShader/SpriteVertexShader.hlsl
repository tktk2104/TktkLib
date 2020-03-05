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

struct VS_INPUT
{
	float4 position : POSITION;
};

struct VS_OUTPUT
{
	float2 texcoord : TEXCOORD0;
	float4 position : SV_POSITION;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;

	output.position = input.position;
	output.position.xy *= textureSize;
	output.position.xy -= (spriteCenterRate * textureSize);
	output.position.xy *= spriteScaleRate;

	float2 rotate;
	rotate.x = output.position.x * cos(spriteAngleDeg) - output.position.y * sin(spriteAngleDeg);
	rotate.y = output.position.x * sin(spriteAngleDeg) + output.position.y * cos(spriteAngleDeg);

	output.position.xy = rotate;
	output.position.xy += spritePosition;
	output.position.xy = output.position.xy * float2(2.0 / screenSize.x, 2.0 / -screenSize.y) + float2(-1.0, 1.0);
	output.texcoord.xy = (input.position.xy * textureUvMulRate) + textureUvOffset;

	return output;
}