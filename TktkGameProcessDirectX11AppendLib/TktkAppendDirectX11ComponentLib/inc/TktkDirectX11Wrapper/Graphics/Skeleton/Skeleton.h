#ifndef SKELETON_H_
#define SKELETON_H_

#include "Asset/SkeletonData.h"

namespace tktk
{
	// 「SkeletonManager」の実装の一部を隠すためのクラス
	class Skeleton
	{
	public:

		// 新しいスケルトンを作成する
		// ※この関数でスケルトンを作る場合、idは1以上でなければならない
		static void create(int id, const std::vector<Bone>& boneArray);

		// 指定したスケルトンを削除する
		// ※この関数でスケルトンを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// 指定したスケルトンを管理するクラスの参照を取得する
		static const SkeletonData& getData(int id);
	};
}
#endif // !SKELETON_H_