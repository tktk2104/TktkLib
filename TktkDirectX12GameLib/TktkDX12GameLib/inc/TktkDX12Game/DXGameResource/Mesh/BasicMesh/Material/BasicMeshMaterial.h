#ifndef BASIC_MESH_MATERIAL_H_
#define BASIC_MESH_MATERIAL_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "BasicMeshMaterialData.h"

namespace tktk
{
	// 「BasicMeshMaterialData」を管理するクラス
	class BasicMeshMaterial
	{
	public:

		BasicMeshMaterial(const ShaderFilePaths& shaderFilePaths, unsigned int basicMeshMaterialNum);
		~BasicMeshMaterial() = default;

	public:

		// 「BasicMeshMaterialData」のインスタンスを作る
		void create(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		// 指定の通常メッシュのマテリアル情報をグラフィックパイプラインに設定する
		void setMaterialData(unsigned int id)  const;

	private:

		// 通常メッシュマテリアル描画用のルートシグネチャを作る
		void createRootSignature() const;

		// 通常メッシュマテリアル描画用のパイプラインステートを作る
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const;

	private:

		HeapArray<BasicMeshMaterialData> m_basicMeshMaterialArray;
	};
}
#endif // !BASIC_MESH_MATERIAL_H_