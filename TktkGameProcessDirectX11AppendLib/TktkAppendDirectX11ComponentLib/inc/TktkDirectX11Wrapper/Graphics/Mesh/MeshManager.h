#ifndef MESH_MANAGER_H_
#define MESH_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Assets/MeshAssets.h"

namespace tktk
{
	class MeshManager
	{
	public:
		
		static void setUp();

	public:

		// 新たなメッシュデータを作成する
		static void create(
			int id,
			const VertexBufferInitParams& vertexBufferParams,
			const IndexBufferInitParams& indexBufferParams
		);

		// 指定したメッシュデータを削除する
		static void erase(int id);

		// 全てのメッシュデータを削除する
		static void clear();

		// 指定したメッシュデータを管理するクラスのポインタを取得する
		static MeshData* getDataPtr(int id);

	private:

		static CfpPtr<MeshAssets> m_assetsPtr;
	};
}
#endif // !MESH_MANAGER_H_
