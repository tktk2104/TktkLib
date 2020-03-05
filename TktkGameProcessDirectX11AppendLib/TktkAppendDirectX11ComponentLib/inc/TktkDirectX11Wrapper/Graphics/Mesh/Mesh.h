#ifndef MESH_H_
#define MESH_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Assets/MeshData.h"

namespace tktk
{
	class Mesh
	{
	public:

		// 新たなメッシュデータを作成する
		// ※この関数でメッシュデータを作成する場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const VertexBufferInitParams& vertexBufferParams, const IndexBufferInitParams& indexBufferParams, const MaterialSlotsInitParams& materialSlotsParams)
		{
			createImpl(static_cast<int>(id), vertexBufferParams, indexBufferParams, materialSlotsParams);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const VertexBufferInitParams& vertexBufferParams, const IndexBufferInitParams& indexBufferParams, const MaterialSlotsInitParams& materialSlotsParams)
			{ static_assert(false, "MeshId Fraud Type"); }

		// 指定したメッシュデータを削除する
		// ※この関数でメッシュデータを削除する場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "MeshId Fraud Type"); }

		// 指定したメッシュデータを管理するクラスのポインタを取得する
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static MeshData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static MeshData* getDataPtr(IdType id) { static_assert(false, "MeshId Fraud Type"); }

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const VertexBufferInitParams& vertexBufferParams, const IndexBufferInitParams& indexBufferParams, const MaterialSlotsInitParams& materialSlotsParams);
		static void eraseImpl(int id);
		static MeshData* getDataPtrImpl(int id);
	};
}
#endif // !MESH_H_
