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
	float3 View			: TEXCOORD1;
	float3 Light		: TEXCOORD2;
};

VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	// この頂点が使用するメッシュのボーンのローカル行列を計算する
	float4x4 LocalMatrix
		= BoneMatrices[Input.BlendIndices.x] * Input.BlendWeight.x
		+ BoneMatrices[Input.BlendIndices.y] * Input.BlendWeight.y
		+ BoneMatrices[Input.BlendIndices.z] * Input.BlendWeight.z
		+ BoneMatrices[Input.BlendIndices.w] * Input.BlendWeight.w;

	// 【この頂点座標の座標変換】
	// ボーンのローカル行列を使って座標変換する
	float4 LocalPosition = mul(LocalMatrix, Input.Position);
	// 定数バッファで取得したワールド行列を使って座標変換する
	float4 WorldPosition = mul(WorldMatrix, LocalPosition);
	// 定数バッファで取得したビュー行列を使って座標変換する
	float4 ViewPosition = mul(ViewMatrix, WorldPosition);

	// 座標変換で使用する4x4の行列を3x3の行列に直す
	float3x3 LocalMatrix3 = (float3x3)LocalMatrix;
	float3x3 WorldMatrix3 = (float3x3)WorldMatrix;
	float3x3 ViewMatrix3 = (float3x3)ViewMatrix;

	// 【この頂点法線の座標変換】（処理は頂点座標の座標変換とほぼ同じ）
	float3 localNormal = mul(LocalMatrix3, Input.Normal);
	float3 worldNormal = mul(WorldMatrix3, localNormal);
	float3 viewNormal = mul(ViewMatrix3, worldNormal);

	// 【この頂点タンジェントの座標変換】（処理は頂点座標の座標変換とほぼ同じ）
	float3 localTangent = mul(LocalMatrix3, Input.Tangent);
	float3 worldTangent = mul(WorldMatrix3, localTangent);
	float3 viewTangent = mul(ViewMatrix3, worldTangent);

	// 【この頂点バイノーマルの座標変換】（処理は頂点座標の座標変換とほぼ同じ）
	float3 localBinormal = mul(LocalMatrix3, Input.Binormal);
	float3 worldBinormal = mul(WorldMatrix3, localBinormal);
	float3 viewBinormal = mul(ViewMatrix3, worldBinormal);

	// ライトの座標をビュー行列を使って座標変換する
	float3 ViewLight = mul(ViewMatrix, float4(lightPosition, 1.0f)).xyz;

	// 接空間変換行列を計算
	float3x3 matTBN = float3x3(normalize(viewTangent), normalize(viewBinormal), normalize(viewNormal));

	// パースペクティブ空間での頂点座標を計算
	Output.Position = mul(ProjectionMatrix, ViewPosition);
	// TexCoordをそのまま渡す
	Output.TexCoord = Input.TexCoord;
	// 頂点→カメラのベクトルを接空間変換行列を使って座標変換
	Output.View = mul(-ViewPosition.xyz, matTBN);
	// 
	Output.Light = mul((ViewLight - ViewPosition.xyz), matTBN);

	return Output;
}