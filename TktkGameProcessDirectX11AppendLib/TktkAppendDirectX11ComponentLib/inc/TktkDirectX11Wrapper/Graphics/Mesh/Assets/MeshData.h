#ifndef MESH_DATA_H_
#define MESH_DATA_H_

#include "VertexBuffer/VertexBuffer.h"
#include "IndexBuffer/IndexBuffer.h"
#include "MaterialSlots/MaterialSlots.h"

#include "SystemMeshId.h"

namespace tktk
{
	class MeshData
	{
	public:

		MeshData(
			D3D_PRIMITIVE_TOPOLOGY primitiveTopology,
			const VertexBufferInitParams& vertexBufferParams,
			const IndexBufferInitParams& indexBufferParams,
			const MaterialSlotsInitParams& materialSlotsParams
		);
		~MeshData() = default;

		// コピー禁止
		MeshData(const MeshData& other) = delete;
		MeshData& operator = (const MeshData& other) = delete;

	public:

		// どういう頂点の並びで描画命令を行うかをレンダリングパイプラインに設定する
		void setPrimitiveTopology() const;

		// 頂点バッファとインデックスバッファをレンダリングパイプラインに設定する
		void setVertexAndIndexBuffer() const;

		// マテリアルスロットが何個あるか取得する
		unsigned int getMaterialSlotCount() const;

		// 指定したマテリアルスロットのサブセットを取得する
		const Subset& getSubset(unsigned int slotIndex) const;

	private:

		D3D_PRIMITIVE_TOPOLOGY m_primitiveTopology;
		VertexBuffer m_vertexBuffer;
		IndexBuffer m_indexBuffer;
		MaterialSlots m_materialSlots;
	};
}
#endif // !MESH_DATA_H_
