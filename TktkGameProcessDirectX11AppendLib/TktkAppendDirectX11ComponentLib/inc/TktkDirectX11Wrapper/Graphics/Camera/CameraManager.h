#ifndef CAMERA_MANAGER_H_
#define CAMERA_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/CameraAssets.h"

namespace tktk
{
	// 「CameraAssets」に簡単にアクセスするためのクラス
	class CameraManager
	{
	public:

		// 「CameraAssets」を生成
		static void setUp();

	public:

		// 新たなカメラを生成する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Matrix4& viewMatrix, const Matrix4& projectionMatrix)
		{
			createImpl(static_cast<int>(id), viewMatrix, projectionMatrix);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Matrix4& viewMatrix, const Matrix4& projectionMatrix) { static_assert(false, "CameraId Fraud Type"); }

		// 指定したカメラを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "CameraId Fraud Type"); }

		// 指定したカメラを管理するクラスのポインタを取得する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static CameraData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static CameraData* getDataPtr(IdType id) { static_assert(false, "CameraId Fraud Type"); }

		// 全てのカメラを削除する
		static void clear();

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const Matrix4& viewMatrix, const Matrix4& projectionMatrix);
		static void eraseImpl(int id);
		static CameraData* getDataPtrImpl(int id);

	private:

		static CfpPtr<CameraAssets> m_assetsPtr;
	};
}
#endif // !CAMERA_MANAGER_H_