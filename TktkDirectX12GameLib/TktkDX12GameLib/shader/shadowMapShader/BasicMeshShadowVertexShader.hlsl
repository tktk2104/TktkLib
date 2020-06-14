cbuffer ConstantBuffer : register(b0)
{
	float4x4    WorldMatrix;
	float4x4    ViewMatrix;
	float4x4    ProjectionMatrix;
	float4x4    BoneMatrices[128];
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
};

VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	// ���̒��_���g�p���郁�b�V���̃{�[���̃��[�J���s����v�Z����
	float4x4 LocalMatrix
		= mul(BoneMatrices[Input.BlendIndices.x], Input.BlendWeight.x)
		+ mul(BoneMatrices[Input.BlendIndices.y], Input.BlendWeight.y);

	// �y���̒��_���W�̍��W�ϊ��z
	// �{�[���̃��[�J���s����g���č��W�ϊ�����
	float4 LocalPosition = mul(LocalMatrix, Input.Position);
	// �萔�o�b�t�@�Ŏ擾�������[���h�s����g���č��W�ϊ�����
	float4 WorldPosition = mul(WorldMatrix, LocalPosition);
	// �萔�o�b�t�@�Ŏ擾�����r���[�s����g���č��W�ϊ�����
	float4 ViewPosition = mul(ViewMatrix, WorldPosition);;
	
	// �p�[�X�y�N�e�B�u��Ԃł̒��_���W���v�Z
	Output.Position = mul(ProjectionMatrix, ViewPosition);

	return Output;
}