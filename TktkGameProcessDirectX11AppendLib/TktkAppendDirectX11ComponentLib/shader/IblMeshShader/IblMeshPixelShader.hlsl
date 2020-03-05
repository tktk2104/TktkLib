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

// �@���}�b�v
SamplerState g_NormalMapSampler  : register(s0);
Texture2D    g_NormalMapTexture  : register(t0);

// IBL���ʔ��˃}�b�v
SamplerState g_IBLSpecularMapSampler : register(s1);
TextureCube  g_IBLSpecularMapTexture : register(t1);

// IBL_BRDF�}�b�v
SamplerState g_IBLBRDFMapSampler : register(s2);
Texture2D	 g_IBLBRDFMapTexture : register(t2);

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

// IBL�̌v�Z
float3 imageBasedLighting(float3 N, float3 R, float NoV, float3 deffuseColor, float3 specularColor, float perceptualRoughness)
{
	float3 Ld = g_IBLSpecularMapTexture.SampleLevel(g_IBLSpecularMapSampler, N, 10.0 - 0.5).rgb * deffuseColor;

	float3 Lld = g_IBLSpecularMapTexture.SampleLevel(g_IBLSpecularMapSampler, R, perceptualRoughness * 10.0).rgb;

	float2 Ldfg = g_IBLBRDFMapTexture.Sample(g_IBLBRDFMapSampler, float2(NoV, 1.0 - perceptualRoughness)).xy;

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

float4 main(PS_INPUT Input) : SV_TARGET
{
	// ���j�A�J���[�ɕϊ�
	float3 linearAlbedoColor = ConvertToLinear(albedoColor.xyz);

	// �g�U���˃J���[�̎擾�i������j
	float3 diffuseColor = lerp(linearAlbedoColor, 0.0f, metallic);
	// ���ʔ��˃J���[�̎擾�i�����j
	float3 specularColor = lerp(0.04f, linearAlbedoColor, metallic);
	// ���t�l�X�ɕϊ� 0.0�i�c���c���j�`1.0�i�U���U���j
	float perceptualRoughness = smoothnessToPerceptualRoughness(smoothness);
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
	float3 L = normalize(-Input.VLight);
	float3 V = normalize(-Input.VPosition);
	float3 H = normalize(L + V);
	float3 R = reflect(-V, N);

	// �e��x�N�g���̓���
	float NoV = abs(dot(N, V)) + 1e-5;
	float NoL = saturate(dot(N, L));
	float NoH = saturate(dot(N, H));
	float LoV = saturate(dot(L, V));
	float LoH = saturate(dot(L, H));

	// �C���[�W�x�[�X�h���C�e�B���O
	float3 IBL = imageBasedLighting(N, R, NoV, diffuseColor, specularColor, perceptualRoughness);

	// �m�����j�A�J���[�ɕϊ����ďo��
	return float4(ConvertToNoneLinear(IBL), 1.0f);
}