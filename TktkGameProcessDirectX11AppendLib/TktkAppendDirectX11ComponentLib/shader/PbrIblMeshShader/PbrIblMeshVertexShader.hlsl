cbuffer MeshConstantBuffer : register(b0)
{
	float4x4    WorldMatrix;
	float4x4    ViewMatrix;
	float4x4    ProjectionMatrix;
	float4x4    BoneMatrices[256];
};

cbuffer LightConstantBuffer : register(b1)
{
	float4		lightAmbient;
	float4		lightDiffuse;
	float4		lightSpeqular;
	float3		lightPosition;
	float		padOneOne;
}

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
	float2 TexCoord     : TEXCOORD0;
	float3 VPosition	: TEXCOORD1;
	float3 VNormal		: TEXCOORD2;
	float3 VLight		: TEXCOORD3;
	float3 VTangent		: TEXCOORD4;
	float3 VBinormal	: TEXCOORD5;
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

	Output.Position = mul(ProjectionMatrix, ViewPosition);
	Output.TexCoord = Input.TexCoord;
	Output.VPosition = ViewPosition.xyz;
	Output.VNormal = viewNormal;
	Output.VLight = ViewLight;
	Output.VTangent = viewTangent;
	Output.VBinormal = viewBinormal;

	return Output;
}