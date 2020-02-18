cbuffer ConstantBuffer : register(b0)
{
	float4x4    WorldMatrix;
	float4x4    ViewMatrix;
	float4x4    ProjectionMatrix;
	float4x4    BoneMatrices[256];

	float4		albedoColor;
	float		metallic;
	float		smoothness;
	float2		padTwo;

	float4		ligntAmbient;
	float4		lightDiffuse;
	float4		lightSpeqular;
	float3		lightPosition;
	float		padOneOne;
};

struct PS_INPUT
{
	float4 Position     : SV_POSITION;
	float2 TexCoord     : TEXCOORD;
	float3 View			: TEXCOORD1;
	float3 Light		: TEXCOORD2;
};

// �@���}�b�v
SamplerState g_NormalMapSampler  : register(s0);
Texture2D    g_NormalMapTexture  : register(t0);

// �X���[�X�l�X�����t�l�X�ɕϊ�
float smoothnessToPerceptualRoughness(float smoothness)
{
	return (1.0f - smoothness);
}

// �m�o�I�ȃ��t�l�X�����ۂ̃��t�l�X�ɕϊ�
float perceptualRoughnessToRoughness(float perceptualRoughness)
{
	return perceptualRoughness * perceptualRoughness;
}

// �g�U����
float fdLambert()
{
	return 1.0 / 3.1415926;
}

// �g�U����BRDF
float3 diffuseBRDF(float3 deffuseColor)
{
	return deffuseColor * fdLambert();
}

// �}�C�N���t�@�Z�b�g���z�֐��iTrowbridge-Reitz[GGX]�j
float dGGX(float NoH, float linearRoughness)
{
	float a2 = linearRoughness * linearRoughness;
	float f = (NoH * a2 - NoH) * NoH + 1.0;
	return a2 / (3.1415926 * f * f);
}

// �����֐��i�ߎ��o�[�W�����j
float vSmithGGXCorrelatedFast(float NoV, float NoL, float linearRoughness)
{
	float a = linearRoughness;
	float GGXV = NoL * (NoV * (1.0 - a) + a);
	float GGXL = NoV * (NoL * (1.0 - a) + a);
	return 0.5 / (GGXV + GGXL + 1e-5);
}

// 5��
float pow5(float x)
{
	return x * x * x * x * x;
}

// �t���l������
float3 fSchlick(float cosA, float3 f0)
{
	return f0 + (1.0 - f0) * pow5(1.0 - cosA);
}

// ���ʔ���BRDF�iCook-Torrance approximation�j
float3 specularBRDF(float3 specularColor, float NoH, float NoV, float NoL, float LoH, float linearRoughness)
{
	float D = dGGX(NoH, linearRoughness);
	float V = vSmithGGXCorrelatedFast(NoV, NoL, linearRoughness);
	float3 F = fSchlick(LoH, specularColor);
	return D * V * F;
}

// �m�����j�A��Ԃ��烊�j�A��Ԃɕϊ�
float3 ConvertToLinear(float3 color)
{
	return pow(color, 2.2);
}

// ���j�A��Ԃ���m�����j�A��Ԃɕϊ�
float3 ConvertToNoneLinear(float3 color)
{
	return pow(color, 1 / 2.2);
}

float4 main(PS_INPUT Input) : SV_TARGET
{
	// ���j�A�J���[�ɕϊ�
	float3 linearAlbedoColor = ConvertToLinear(albedoColor.xyz);

	// �g�U���˃J���[�̎擾�i������j
	float3 diffuseColor = lerp(linearAlbedoColor, 0.0f, metallic);
	// �g�U���˃J���[�̎擾�i�����j
	float3 specularColor = lerp(0.04f, linearAlbedoColor, metallic);
	// ���t�l�X�ɕϊ� 0.0�i�c���c���j�`1.0�i�U���U���j
	float perceptualRoughness = smoothnessToPerceptualRoughness(smoothness);
	// ���j�A��Ԃ̃��t�l�X�ɕϊ� 0.0�i�c���c���j�`1.0�i�U���U���j
	float linearRoughness = perceptualRoughnessToRoughness(perceptualRoughness);

	// �e��x�N�g�������߂�
	float3 N = normalize(g_NormalMapTexture.Sample(g_NormalMapSampler, Input.TexCoord).xyz * 2.0 - 1.0);
	float3 L = normalize(Input.Light);
	float3 V = normalize(Input.View);
	float3 H = normalize(L + V);
	float3 R = reflect(-V, N);

	// �e��x�N�g���̓���
	float NoV = abs(dot(N, V)) + 1e-5;
	float NoL = saturate(dot(N, L));
	float NoH = saturate(dot(N, H));
	float LoV = saturate(dot(L, V));
	float LoH = saturate(dot(L, H));

	// ���ˏƓx�̌v�Z
	float3 irradiance = NoL * 3.1415926;

	// �o�������˗����z�֐��iBRDF�j�̌v�Z
	float3 Fd = diffuseBRDF(diffuseColor);
	float3 Fr = specularBRDF(specularColor, NoH, NoV, NoL, LoH, linearRoughness);
	float3 BRDF = (Fd + Fr) * irradiance;

	// �m�����j�A�J���[�ɕϊ����ďo��
	return float4(ConvertToNoneLinear(BRDF), 1.0f);
}