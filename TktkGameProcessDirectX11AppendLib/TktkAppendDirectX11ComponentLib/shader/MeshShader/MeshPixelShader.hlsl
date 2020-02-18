cbuffer ConstantBuffer : register(b0)
{
	float4x4    WorldMatrix;
	float4x4    ViewMatrix;
	float4x4    ProjectionMatrix;
	float4x4    BoneMatrices[256];

	float4		MatAmbient;
	float4		MatDiffuse;
	float4		MatSpecular;
	float4		MatEmissive;
	float		MatShiniess;
	float3		padThree;

	float4		ligntAmbient;
	float4		lightDiffuse;
	float4		lightSpeqular;
	float3		lightPosition;
	float		padOneOne;
};

struct PS_INPUT
{
	float4 Position     : SV_POSITION;
	float2 TexCoord     : TEXCOORD0;
	float3 View			: TEXCOORD1;
	float3 Light		: TEXCOORD2;
};

// アルベドマップ
SamplerState g_AlbedoMapSampler  : register(s0);
Texture2D	 g_AlbedoMapTexture  : register(t0);

// メタリックスムースネスマップ
SamplerState g_MetallicSmoothnessMapSampler : register(s1);
Texture2D	 g_MetallicSmoothnessMapTexture : register(t1);

// 法線マップ
SamplerState g_NormalMapSampler  : register(s2);
Texture2D    g_NormalMapTexture  : register(t2);

// アンビエントオクルージョンマップ
SamplerState g_AmbientOcclusionMapSampler : register(s3);
Texture2D	 g_AmbientOcclusionMapTexture : register(t3);

float4 main(PS_INPUT Input) : SV_TARGET
{
	float3 N = normalize(g_NormalMapTexture.Sample(g_NormalMapSampler, Input.TexCoord).xyz * 2.0 - 1.0);
	float3 V = normalize(Input.View);
	float3 L = normalize(Input.Light);
	float3 H = normalize(L + V);
	
	float diffuse = max(dot(L, N), 0.0);
	float specular = pow(max(dot(N, H), 0.0), MatShiniess);
	
	float4 baseColor = g_AlbedoMapTexture.Sample(g_AlbedoMapSampler, Input.TexCoord);
	
	float4 resultColor
		= MatAmbient * ligntAmbient * baseColor
		+ MatDiffuse * lightDiffuse * diffuse * baseColor
		+ MatSpecular * lightSpeqular * specular
		+ MatEmissive * baseColor;
	
	resultColor.a = baseColor.a * MatDiffuse.a;
	
	return resultColor;
}