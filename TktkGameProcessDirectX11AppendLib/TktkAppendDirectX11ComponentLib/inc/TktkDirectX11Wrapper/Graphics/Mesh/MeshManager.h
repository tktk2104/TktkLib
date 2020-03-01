#ifndef MESH_MANAGER_H_
#define MESH_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Assets/MeshAssets.h"

namespace tktk
{
	class MeshManager
	{
	public:
		
		// 「MeshAssets」を作成
		static void setUp();

	public:

		// 新たなメッシュデータを作成する
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const VertexBufferInitParams& vertexBufferParams, const IndexBufferInitParams& indexBufferParams)
		{
			createImpl(static_cast<int>(id), vertexBufferParams, indexBufferParams);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const VertexBufferInitParams& vertexBufferParams, const IndexBufferInitParams& indexBufferParams)
			{ static_assert(false, "MeshId Fraud Type"); }

		// 指定したメッシュデータを削除する
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

		// 全てのメッシュデータを削除する
		static void clear();

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const VertexBufferInitParams& vertexBufferParams, const IndexBufferInitParams& indexBufferParams);
		static void eraseImpl(int id);
		static MeshData* getDataPtrImpl(int id);

	private:

		static CfpPtr<MeshAssets> m_assetsPtr;
	};
}
#endif // !MESH_MANAGER_H_
