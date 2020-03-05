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
	float2 TexCoord     : TEXCOORD;
	float3 View			: TEXCOORD1;
	float3 Light		: TEXCOORD2;
};

// 法線マップ
SamplerState g_NormalMapSampler  : register(s0);
Texture2D    g_NormalMapTexture  : register(t0);

// スムースネスをラフネスに変換
float smoothnessToPerceptualRoughness(float smoothness)
{
	return (1.0f - smoothness);
}

// 知覚的なラフネスを実際のラフネスに変換
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
	// 拡散反射カラーの取得（金属）
	float3 specularColor = lerp(0.04f, linearAlbedoColor, metallic);
	// ラフネスに変換 0.0（ツルツル）～1.0（ザラザラ）
	float perceptualRoughness = smoothnessToPerceptualRoughness(smoothness);
	// リニア空間のラフネスに変換 0.0（ツルツル）～1.0（ザラザラ）
	float linearRoughness = perceptualRoughnessToRoughness(perceptualRoughness);

	// 各種ベクトルを求める
	float3 N = normalize(g_NormalMapTexture.Sample(g_NormalMapSampler, Input.TexCoord).xyz * 2.0 - 1.0);
	float3 L = normalize(Input.Light);
	float3 V = normalize(Input.View);
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

	// ノンリニアカラーに変換して出力
	return float4(ConvertToNoneLinear(BRDF), 1.0f);
}