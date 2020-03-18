cbuffer MaterialConstantBuffer : register(b0)
{
	float4		MatAmbient;
	float4		MatDiffuse;
	float4		MatSpecular;
	float4		MatEmissive;
	float		MatShiniess;
	float3		padThree;
}

cbuffer LightConstantBuffer : register(b1)
{
	float4		lightAmbient;
	float4		lightDiffuse;
	float4		lightSpeqular;
	float3		lightPosition;
	float		padOneOne;
}

cbuffer MonoColorConstantBuffer : register(b2)
{
	float4		albedoColor;
}

struct PS_INPUT
{
	float4 Position     : SV_POSITION;
	float2 TexCoord     : TEXCOORD0;
	float3 View			: TEXCOORD1;
	float3 Light		: TEXCOORD2;
};

// �@���}�b�v
SamplerState g_NormalMapSampler  : register(s0);
Texture2D    g_NormalMapTexture  : register(t0);

float4 main(PS_INPUT Input) : SV_TARGET
{
	float3 N = normalize(g_NormalMapTexture.Sample(g_NormalMapSampler, Input.TexCoord).xyz * 2.0 - 1.0);

	float3 V = normalize(Input.View);
	float3 L = normalize(Input.Light);
	float3 H = normalize(L + V);
	
	float diffuse = max(dot(L, N), 0.0);
	float specular = pow(max(dot(N, H), 0.0), MatShiniess);
	
	float4 resultColor
		= MatAmbient * lightAmbient * albedoColor
		+ MatDiffuse * lightDiffuse * diffuse * albedoColor
		+ MatSpecular * lightSpeqular * specular
		+ MatEmissive * albedoColor;
	
	resultColor.a = albedoColor.a * MatDiffuse.a;
	
	return resultColor;
}