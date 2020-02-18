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

// �A���x�h�}�b�v
SamplerState g_AlbedoMapSampler  : register(s0);
Texture2D	 g_AlbedoMapTexture  : register(t0);

// �@���}�b�v
SamplerState g_NormalMapSampler  : register(s1);
Texture2D    g_NormalMapTexture  : register(t1);

// ���^���b�N�X���[�X�l�X�}�b�v
SamplerState g_MetallicSmoothnessMapSampler : register(s2);
Texture2D	 g_MetallicSmoothnessMapTexture : register(t2);

// �A���r�G���g�I�N���[�W�����}�b�v
SamplerState g_AmbientOcclusionMapSampler : register(s3);
Texture2D	 g_AmbientOcclusionMapTexture : register(t3);

// IBL���ʔ��˃}�b�v
SamplerState g_IBLSpecularMapSampler : register(s4);
TextureCube  g_IBLSpecularMapTexture : register(t4);

// IBL_BRDF�}�b�v
SamplerState g_IBLBRDFMapSampler : register(s5);
Texture2D	 g_IBLBRDFMapTexture : register(t5);

// �X���[�X�l�X�����t�l�X�ɕϊ�
float smoothnessToPerceptualRoughness(float smoothness)
{
	return (1.0f - smoothness);
}

// ���j�A��Ԃ̃��t�l�X�ɕϊ�
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

// IBL�̌v�Z
float3 imageBasedLighting(float3 N, float3 R, float NoV, float3 deffuseColor, float3 specularColor, float perceptualRoughness)
{
	float3 Ld = g_IBLSpecularMapTexture.SampleLevel(g_IBLSpecularMapSampler, N, 10 - 0.5).rgb * deffuseColor;

	float3 Lld = g_IBLSpecularMapTexture.SampleLevel(g_IBLSpecularMapSampler, R, perceptualRoughness * 10).rgb;

	float2 Ldfg = g_IBLBRDFMapTexture.Sample(g_IBLBRDFMapSampler, float2(NoV, perceptualRoughness)).xy;

	float3 Lr = (specularColor * Ldfg.x + Ldfg.y) * Lld;

	return Ld + Lr;
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
	// �A���x�h�J���[�����j�A�J���[�ɕϊ����Ď擾
	float3 albedoColor = ConvertToLinear(g_AlbedoMapTexture.Sample(g_AlbedoMapSampler, Input.TexCoord).xyz);

	// ���^���b�N�ƃX���[�X�l�X�̒l���擾
	float4 metallicSmoothness = g_MetallicSmoothnessMapTexture.Sample(g_MetallicSmoothnessMapSampler, Input.TexCoord);

	// �A���r�G���g�I�N���[�W�����̒l���擾
	float4 ambientOcclusion = g_AmbientOcclusionMapTexture.Sample(g_AmbientOcclusionMapSampler, Input.TexCoord);

	// �g�U���˃J���[�̎擾�i������j
	float3 diffuseColor = lerp(albedoColor, 0.0f, metallicSmoothness.r);
	// ���ʔ��˃J���[�̎擾�i�����j
	float3 specularColor = lerp(0.04f, albedoColor, metallicSmoothness.r);
	// ���t�l�X�ɕϊ� 0.0�i�c���c���j�`1.0�i�U���U���j
	float perceptualRoughness = smoothnessToPerceptualRoughness(metallicSmoothness.a);
	// ���j�A��Ԃ̃��t�l�X�ɕϊ� 0.0�i�c���c���j�`1.0�i�U���U���j
	float linearRoughness = perceptualRoughnessToRoughness(perceptualRoughness);

	// �ڋ�ԕϊ��s����v�Z
	float3x3 matTBN = float3x3(
		normalize(Input.VTangent),
		normalize(Input.VBinormal),
		normalize(Input.VNormal)
		);

	// �e��x�N�g�������߂�
	float3 N = mul(normalize(g_NormalMapTexture.Sample(g_NormalMapSampler, Input.TexCoord).xyz * 2.0 - 1.0), matTBN);
	float3 L = mul((Input.VLight - Input.VPosition), matTBN);//normalize(-Input.VLight);
	float3 V = normalize(-Input.VPosition);
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

	// �C���[�W�x�[�X�h���C�e�B���O
	float3 IBL = imageBasedLighting(N, R, NoV, diffuseColor, specularColor, perceptualRoughness);

	// �ŏI�I�ȐF���v�Z
	float3 finalColor = (BRDF + IBL) * ambientOcclusion.xyz;

	// temp
	finalColor = ACESFilm(finalColor);

	// �m�����j�A�J���[�ɕϊ����ďo��
	return float4(ConvertToNoneLinear(finalColor), 1.0f);
}