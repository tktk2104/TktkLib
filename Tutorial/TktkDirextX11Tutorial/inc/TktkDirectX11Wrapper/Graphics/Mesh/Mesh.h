#ifndef MESH_H_

#include "Assets/MeshData.h"

namespace tktk
{
	class Mesh
	{
	public:

		// 新たなメッシュデータを作成する
		// ※この関数でメッシュデータを作成する場合、idは1以上でなければならない
		static void create(
			int id,
			const VertexBufferInitParams& vertexBufferParams,
			const IndexBufferInitParams& indexBufferParams
		);

		// 指定したメッシュデータを削除する
		// ※この関数でメッシュデータを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// 指定したメッシュデータを管理するクラスのポインタを取得する
		static MeshData* getDataPtr(int id);
	};
}
#endif // !MESH_H_
