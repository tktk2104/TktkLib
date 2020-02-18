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
	float3 VPosition	: TEXCOORD1;
	float3 VNormal		: TEXCOORD2;
	float3 VLight		: TEXCOORD3;
	float3 VTangent		: TEXCOORD4;
	float3 VBinormal	: TEXCOORD5;
};

// アルベドマップ
SamplerState g_AlbedoMapSampler  : register(s0);
Texture2D	 g_AlbedoMapTexture  : register(t0);

// 法線マップ
SamplerState g_NormalMapSampler  : register(s1);
Texture2D    g_NormalMapTexture  : register(t1);

// メタリックスムースネスマップ
SamplerState g_MetallicSmoothnessMapSampler : register(s2);
Texture2D	 g_MetallicSmoothnessMapTexture : register(t2);

// アンビエントオクルージョンマップ
SamplerState g_AmbientOcclusionMapSampler : register(s3);
Texture2D	 g_AmbientOcclusionMapTexture : register(t3);

// IBL鏡面反射マップ
SamplerState g_IBLSpecularMapSampler : register(s4);
TextureCube  g_IBLSpecularMapTexture : register(t4);

// IBL_BRDFマップ
SamplerState g_IBLBRDFMapSampler : register(s5);
Texture2D	 g_IBLBRDFMapTexture : register(t5);

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

// 拡散反射BRDF
float3 diffuseBRDF(float3 deffuseColor)
{
	return deffuseColor * fdLambert();
}

// マイクロファセット分布関数（Trowbridge-Reitz[GGX]）
float dGGX(float NoH, float linearRoughness)
{
	float a2 = linearRoughness * linearRoughness;
	float f = (NoH * a2 - NoH) * NoH + 1.0;
	return a2 / (3.1415926 * f * f);
}

// 可視性関数（近似バージョン）
float vSmithGGXCorrelatedFast(float NoV, float NoL, float linearRoughness)
{
	float a = linearRoughness;
	float GGXV = NoL * (NoV * (1.0 - a) + a);
	float GGXL = NoV * (NoL * (1.0 - a) + a);
	return 0.5 / (GGXV + GGXL + 1e-5);
}

// 5乗
float pow5(float x)
{
	return x * x * x * x * x;
}

// フレネル反射
float3 fSchlick(float cosA, float3 f0)
{
	return f0 + (1.0 - f0) * pow5(1.0 - cosA);
}

// 鏡面反射BRDF（Cook-Torrance approximation）
float3 specularBRDF(float3 specularColor, float NoH, float NoV, float NoL, float LoH, float linearRoughness)
{
	float D = dGGX(NoH, linearRoughness);
	float V = vSmithGGXCorrelatedFast(NoV, NoL, linearRoughness);
	float3 F = fSchlick(LoH, specularColor);
	return D * V * F;
}

// IBLの計算
float3 imageBasedLighting(float3 N, float3 R, float NoV, float3 deffuseColor, float3 specularColor, float perceptualRoughness)
{
	float3 Ld = g_IBLSpecularMapTexture.SampleLevel(g_IBLSpecularMapSampler, N, 10 - 0.5).rgb * deffuseColor;

	float3 Lld = g_IBLSpecularMapTexture.SampleLevel(g_IBLSpecularMapSampler, R, perceptualRoughness * 10).rgb;

	float2 Ldfg = g_IBLBRDFMapTexture.Sample(g_IBLBRDFMapSampler, float2(NoV, perceptualRoughness)).xy;

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

// temp
float3 ACESFilm(float3 x)
{
	float a = 2.51f;
	float b = 0.03f;
	float c = 2.43f;
	float d = 0.59f;
	float e = 0.14f;
	return saturate((x*(a*x + b)) / (x*(c*x + d) + e));
}

float4 main(PS_INPUT Input) : SV_TARGET
{
	// アルベドカラーをリニアカラーに変換して取得
	float3 albedoColor = ConvertToLinear(g_AlbedoMapTexture.Sample(g_AlbedoMapSampler, Input.TexCoord).xyz);

	// メタリックとスムースネスの値を取得
	float4 metallicSmoothness = g_MetallicSmoothnessMapTexture.Sample(g_MetallicSmoothnessMapSampler, Input.TexCoord);

	// アンビエントオクルージョンの値を取得
	float4 ambientOcclusion = g_AmbientOcclusionMapTexture.Sample(g_AmbientOcclusionMapSampler, Input.TexCoord);

	// 拡散反射カラーの取得（非金属）
	float3 diffuseColor = lerp(albedoColor, 0.0f, metallicSmoothness.r);
	// 鏡面反射カラーの取得（金属）
	float3 specularColor = lerp(0.04f, albedoColor, metallicSmoothness.r);
	// ラフネスに変換 0.0（ツルツル）～1.0（ザラザラ）
	float perceptualRoughness = smoothnessToPerceptualRoughness(metallicSmoothness.a);
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
	float3 L = mul((Input.VLight - Input.VPosition), matTBN);//normalize(-Input.VLight);
	float3 V = normalize(-Input.VPosition);
	float3 H = normalize(L + V);
	float3 R = reflect(-V, N);

	// 各種ベクトルの内積
	float NoV = abs(dot(N, V)) + 1e-5;
	float NoL = saturate(dot(N, L));
	float NoH = saturate(dot(N, H));
	float LoV = saturate(dot(L, V));
	float LoH = saturate(dot(L, H));

	// 放射照度の計算
	float3 irradiance = NoL * 3.1415926;

	// 双方向反射率分布関数（BRDF）の計算
	float3 Fd = diffuseBRDF(diffuseColor);
	float3 Fr = specularBRDF(specularColor, NoH, NoV, NoL, LoH, linearRoughness);
	float3 BRDF = (Fd + Fr) * irradiance;

	// イメージベースドライティング
	float3 IBL = imageBasedLighting(N, R, NoV, diffuseColor, specularColor, perceptualRoughness);

	// 最終的な色を計算
	float3 finalColor = (BRDF + IBL) * ambientOcclusion.xyz;

	// temp
	finalColor = ACESFilm(finalColor);

	// ノンリニアカラーに変換して出力
	return float4(ConvertToNoneLinear(finalColor), 1.0f);
}