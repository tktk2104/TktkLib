#ifndef SKELETON_H_
#define SKELETON_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/SkeletonData.h"

namespace tktk
{
	// 「SkeletonManager」の実装の一部を隠すためのクラス
	class Skeleton
	{
	public:

		// 新しいスケルトンを作成する
		// ※この関数でスケルトンを作る場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::vector<Bone>& boneArray)
		{
			createImpl(static_cast<int>(id), boneArray);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::vector<Bone>& boneArray) { static_assert(false, "SkeletonId Fraud Type"); }

		// 指定したスケルトンを削除する
		// ※この関数でスケルトンを削除する場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "SkeletonId Fraud Type"); }

		// 指定したスケルトンを管理するクラスの参照を取得する
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const SkeletonData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const SkeletonData& getData(IdType id) { static_assert(false, "SkeletonId Fraud Type"); }

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const std::vector<Bone>& boneArray);
		static void eraseImpl(int id);
		static const SkeletonData& getDataImpl(int id);
	};
}
#endif // !SKELETON_H_