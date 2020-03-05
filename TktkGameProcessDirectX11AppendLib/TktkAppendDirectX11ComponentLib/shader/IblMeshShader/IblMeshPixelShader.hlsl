cbuffer PbrConstantBuffer : register(b0)
{
	float4		albedoColor;
	float		metallic;
	float		smoothness;
	float2		padTwoTwo;
}

struct PS_INPUT
{
	float4 Position     : SV_POSITION;
	float2 TexCoord     : TEXCOORD0;
	float3 VPosition	: TEXCOORD1;
	float3 VNormal		: TEXCOORD2;
	float3 VLight		: TEXCOORD3;
	float3 VTangent		: TEXCOORD4;
	float3 VBinormal	: TEXCOORD5;
};

// 法線マップ
SamplerState g_NormalMapSampler  : register(s0);
Texture2D    g_NormalMapTexture  : register(t0);

// IBL鏡面反射マップ
SamplerState g_IBLSpecularMapSampler : register(s1);
TextureCube  g_IBLSpecularMapTexture : register(t1);

// IBL_BRDFマップ
SamplerState g_IBLBRDFMapSampler : register(s2);
Texture2D	 g_IBLBRDFMapTexture : register(t2);

// スムースネスをラフネスに変換
float smoothnessToPerceptualRoughness(float smoothness)
{
	return (1.0f - smoothness);
}

// リニア空間のラフネスに変換
float perceptualRoughnessToRoughness(float perceptualRoughness)
{
	return perceptualRoughness * perceptualRoughness;
}

// 拡散反射
float fdLambert()
{
	return 1.0 / 3.1415926;
}

// IBLの計算
float3 imageBasedLighting(float3 N, float3 R, float NoV, float3 deffuseColor, float3 specularColor, float perceptualRoughness)
{
	float3 Ld = g_IBLSpecularMapTexture.SampleLevel(g_IBLSpecularMapSampler, N, 10.0 - 0.5).rgb * deffuseColor;

	float3 Lld = g_IBLSpecularMapTexture.SampleLevel(g_IBLSpecularMapSampler, R, perceptualRoughness * 10.0).rgb;

	float2 Ldfg = g_IBLBRDFMapTexture.Sample(g_IBLBRDFMapSampler, float2(NoV, 1.0 - perceptualRoughness)).xy;

	float3 Lr = (specularColor * Ldfg.x + Ldfg.y) * Lld;

	return Ld + Lr;
}

// ノンリニア空間からリニア空間に変換
float3 ConvertToLinear(float3 color)
{
	return pow(color, 2.2);
}

// リニア空間からノンリニア空間に変換
float3 ConvertToNoneLinear(float3 color)
{
	return pow(color, 1 / 2.2);
}

float4 main(PS_INPUT Input) : SV_TARGET
{
	// リニアカラーに変換
	float3 linearAlbedoColor = ConvertToLinear(albedoColor.xyz);

	// 拡散反射カラーの取得（非金属）
	float3 diffuseColor = lerp(linearAlbedoColor, 0.0f, metallic);
	// 鏡面反射カラーの取得（金属）
	float3 specularColor = lerp(0.04f, linearAlbedoColor, metallic);
	// ラフネスに変換 0.0（ツルツル）～1.0（ザラザラ）
	float perceptualRoughness = smoothnessToPerceptualRoughness(smoothness);
	// リニア空間のラフネスに変換 0.0（ツルツル）～1.0（ザラザラ）
	float linearRoughness = perceptualRoughnessToRoughness(perceptualRoughness);

	// 接空間変換行列を計算
	float3x3 matTBN = float3x3(
		normalize(Input.VTangent),
		normalize(Input.VBinormal),
		normalize(Input.VNormal)
		);

	// 各種ベクトルを求める
	float3 N = mul(normalize(g_NormalMapTexture.Sample(g_NormalMapSampler, Input.TexCoord).xyz * 2.0 - 1.0), matTBN);
	float3 L = normalize(-Input.VLight);
	float3 V = normalize(-Input.VPosition);
	float3 H = normalize(L + V);
	float3 R = reflect(-V, N);

	// 各種ベクトルの内積
	float NoV = abs(dot(N, V)) + 1e-5;
	float NoL = saturate(dot(N, L));
	float NoH = saturate(dot(N, H));
	float LoV = saturate(dot(L, V));
	float LoH = saturate(dot(L, H));

	// イメージベースドライティング
	float3 IBL = imageBasedLighting(N, R, NoV, diffuseColor, specularColor, perceptualRoughness);

	// ノンリニアカラーに変換して出力
	return float4(ConvertToNoneLinear(IBL), 1.0f);
}