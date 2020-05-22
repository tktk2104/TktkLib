cbuffer ConstantBuffer : register(b0)
{
	float4x4    WorldMatrix;
	float4x4    ViewMatrix;
	float4x4    ProjectionMatrix;
	//float4x4    BoneMatrices[256];
	float4		lightAmbient;
	float4		lightDiffuse;
	float4		lightSpeqular;
	float3		lightPosition;
	float		lightDataPad;
	float4		materialAmbient;
	float4		materialDiffuse;
	float4		materialSpecular;
	float4		materialEmissive;
	float		materialShiniess;
	float3		materialDataPad;
};

struct PS_INPUT
{
	float4 Position     : SV_POSITION;
	float4 Normal		: NORMAL;
	float2 TexCoord     : TEXCOORD0;
	float3 View			: TEXCOORD1;
	float3 Light		: TEXCOORD2;
};

//// アルベドマップ
//SamplerState g_AlbedoMapSampler  : register(s0);
//Texture2D	 g_AlbedoMapTexture  : register(t0);
//
//// 法線マップ
//SamplerState g_NormalMapSampler  : register(s1);
//Texture2D    g_NormalMapTexture  : register(t1);

Texture2D TextureMapTexture : register(t0);
SamplerState TextureMapSampler : register(s0);

float4 main(PS_INPUT Input) : SV_TARGET
{
	float3 N = float3(0.0, 0.0, 1.0);// (Input.Normal).xyz;//normalize(g_NormalMapTexture.Sample(g_NormalMapSampler, Input.TexCoord).xyz * 2.0 - 1.0);
	float3 V = normalize(Input.View);
	float3 L = normalize(Input.Light);
	float3 H = normalize(L + V);
	
	float diffuse = max(dot(L, N), 0.0);
	float specular = pow(max(dot(N, H), 0.0), materialShiniess);
	
	float4 baseColor = float4(0.3, 0.3, 0.3, 0.3);//g_AlbedoMapTexture.Sample(g_AlbedoMapSampler, Input.TexCoord);
	
	float4 resultColor
		= materialAmbient * lightAmbient * baseColor
		+ materialDiffuse * lightDiffuse * diffuse * baseColor
		+ materialSpecular * lightSpeqular * specular
		+ materialEmissive * baseColor;
	
	resultColor.a = baseColor.a * materialDiffuse.a;
	
	return resultColor;
}