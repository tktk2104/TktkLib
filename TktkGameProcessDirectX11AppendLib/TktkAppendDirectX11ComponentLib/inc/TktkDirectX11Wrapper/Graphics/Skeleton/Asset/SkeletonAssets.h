#ifndef SKELETON_ASSETS_H_
#define SKELETON_ASSETS_H_

#include <unordered_map>
#include "SkeletonData.h"

namespace tktk
{
	// 「SkeletonData」を管理するクラス
	class SkeletonAssets
	{
	public:

		SkeletonAssets() = default;
		~SkeletonAssets();

		SkeletonAssets(const SkeletonAssets& other) = delete;
		SkeletonAssets& operator = (const SkeletonAssets& other) = delete;

	public:

		// 新しいスケルトンを作成する
		void create(int id, const std::vector<Bone>& boneArray);

		// 指定したスケルトンを削除する
		void erase(int id);

		// 全てのスケルトンを削除する
		void clear();

		// 指定したスケルトンを管理するクラスの参照を取得する
		const SkeletonData& getData(int id) const;

	private:

		// スケルトンを管理するクラスの連想配列
		std::unordered_map<int, SkeletonData> m_assets;
	};
}
#endif // !SKELETON_ASSETS_H_