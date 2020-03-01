#ifndef SKELETON_MANAGER_H_
#define SKELETON_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/SkeletonAssets.h"

namespace tktk
{
	// 「SkeletonAssets」に簡単にアクセスするためのクラス
	class SkeletonManager
	{
	public:

		// 「SkeletonAssets」を生成
		static void setUp();

	public:

		// 新しいスケルトンを作成する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::vector<Bone>& boneArray)
		{
			createImpl(static_cast<int>(id), boneArray);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::vector<Bone>& boneArray) { static_assert(false, "SkeletonId Fraud Type"); }

		// 指定したスケルトンを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "SkeletonId Fraud Type"); }

		// 指定したスケルトンを管理するクラスの参照を取得する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const SkeletonData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const SkeletonData& getData(IdType id) { static_assert(false, "SkeletonId Fraud Type"); }

		// 全てのスケルトンを削除する
		static void clear();

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const std::vector<Bone>& boneArray);
		static void eraseImpl(int id);
		static const SkeletonData& getDataImpl(int id);

	private:

		static CfpPtr<SkeletonAssets> m_assetsPtr;
	};
}
#endif // !SKELETON_MANAGER_H_