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

struct VS_INPUT
{
	float4  Position     : POSITION;
	float3  Normal       : NORMAL;
	float2  TexCoord     : TEXCOORD;
	int4    BlendIndices : BLENDINDICES;
	float4  BlendWeight  : BLENDWEIGHT;
	float3	Tangent		 : TANGENT;
	float3	Binormal	 : BINORMAL;
};

struct VS_OUTPUT
{
	float4 Position     : SV_POSITION;
	float2 TexCoord     : TEXCOORD;
	float3 View			: TEXCOORD1;
	float3 Light		: TEXCOORD2;
};

VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	// ���̒��_���g�p���郁�b�V���̃{�[���̃��[�J���s����v�Z����
	float4x4 LocalMatrix
		= BoneMatrices[Input.BlendIndices.x] * Input.BlendWeight.x
		+ BoneMatrices[Input.BlendIndices.y] * Input.BlendWeight.y
		+ BoneMatrices[Input.BlendIndices.z] * Input.BlendWeight.z
		+ BoneMatrices[Input.BlendIndices.w] * Input.BlendWeight.w;

	// �y���̒��_���W�̍��W�ϊ��z
	// �{�[���̃��[�J���s����g���č��W�ϊ�����
	float4 LocalPosition = mul(LocalMatrix, Input.Position);
	// �萔�o�b�t�@�Ŏ擾�������[���h�s����g���č��W�ϊ�����
	float4 WorldPosition = mul(WorldMatrix, LocalPosition);
	// �萔�o�b�t�@�Ŏ擾�����r���[�s����g���č��W�ϊ�����
	float4 ViewPosition = mul(ViewMatrix, WorldPosition);

	// ���W�ϊ��Ŏg�p����4x4�̍s���3x3�̍s��ɒ���
	float3x3 LocalMatrix3 = (float3x3)LocalMatrix;
	float3x3 WorldMatrix3 = (float3x3)WorldMatrix;
	float3x3 ViewMatrix3 = (float3x3)ViewMatrix;

	// �y���̒��_�@���̍��W�ϊ��z�i�����͒��_���W�̍��W�ϊ��Ƃقړ����j
	float3 localNormal = mul(LocalMatrix3, Input.Normal);
	float3 worldNormal = mul(WorldMatrix3, localNormal);
	float3 viewNormal = mul(ViewMatrix3, worldNormal);

	// �y���̒��_�^���W�F���g�̍��W�ϊ��z�i�����͒��_���W�̍��W�ϊ��Ƃقړ����j
	float3 localTangent = mul(LocalMatrix3, Input.Tangent);
	float3 worldTangent = mul(WorldMatrix3, localTangent);
	float3 viewTangent = mul(ViewMatrix3, worldTangent);

	// �y���̒��_�o�C�m�[�}���̍��W�ϊ��z�i�����͒��_���W�̍��W�ϊ��Ƃقړ����j
	float3 localBinormal = mul(LocalMatrix3, Input.Binormal);
	float3 worldBinormal = mul(WorldMatrix3, localBinormal);
	float3 viewBinormal = mul(ViewMatrix3, worldBinormal);

	// ���C�g�̍��W���r���[�s����g���č��W�ϊ�����
	float3 ViewLight = mul(ViewMatrix, float4(lightPosition, 1.0f)).xyz;

	// �ڋ�ԕϊ��s����v�Z
	float3x3 matTBN = float3x3(normalize(viewTangent), normalize(viewBinormal), normalize(viewNormal));

	// �p�[�X�y�N�e�B�u��Ԃł̒��_���W���v�Z
	Output.Position = mul(ProjectionMatrix, ViewPosition);
	// TexCoord�����̂܂ܓn��
	Output.TexCoord = Input.TexCoord;
	// ���_���J�����̃x�N�g����ڋ�ԕϊ��s����g���č��W�ϊ�
	Output.View = mul(-ViewPosition.xyz, matTBN);
	// 
	Output.Light = mul((ViewLight - ViewPosition.xyz), matTBN);

	return Output;
}