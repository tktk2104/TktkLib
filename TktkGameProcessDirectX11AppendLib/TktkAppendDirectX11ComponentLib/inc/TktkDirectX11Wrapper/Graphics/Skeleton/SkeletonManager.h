#ifndef SKELETON_MANAGER_H_
#define SKELETON_MANAGER_H_

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

		// 新しいスケルトンを作成する
		static void create(int id, const std::vector<Bone>& boneArray);

		// 指定したスケルトンを削除する
		static void erase(int id);

		// 全てのスケルトンを削除する
		static void clear();

		// 指定したスケルトンを管理するクラスの参照を取得する
		static const SkeletonData& getData(int id);

	private:

		static CfpPtr<SkeletonAssets> m_assetsPtr;
	};
}
#endif // !SKELETON_MANAGER_H_