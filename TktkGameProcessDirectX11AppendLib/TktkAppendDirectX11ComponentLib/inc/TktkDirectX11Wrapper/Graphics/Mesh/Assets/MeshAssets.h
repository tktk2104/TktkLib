#ifndef MESH_ASSETS_H_
#define MESH_ASSETS_H_

#include <unordered_map>
#include "MeshData.h"

namespace tktk
{
	class MeshAssets
	{
	public:
		MeshAssets() = default;
		~MeshAssets();

		MeshAssets(const MeshAssets& other) = delete;
		MeshAssets& operator = (const MeshAssets& other) = delete;

	public:

		// 新たなメッシュデータを作成する
		void create(
			int id,
			const VertexBufferInitParams& vertexBufferParams,
			const IndexBufferInitParams& indexBufferParams,
			const MaterialSlotsInitParams& materialSlotsParams
		);

		// 指定したメッシュデータを削除する
		void erase(int id);

		// 全てのメッシュデータを削除する
		void clear();

		// 指定したメッシュデータを管理するクラスのポインタを取得する
		MeshData* getDataPtr(int id);

	private:

		std::unordered_map<int, MeshData> m_assets;
	};
}
#endif // !MESH_ASSETS_H_
