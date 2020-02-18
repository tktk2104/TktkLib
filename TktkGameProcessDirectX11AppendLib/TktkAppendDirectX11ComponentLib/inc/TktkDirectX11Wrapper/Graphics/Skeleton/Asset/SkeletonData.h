#ifndef SKELETON_DATA_H_
#define SKELETON_DATA_H_

#include <string>
#include <vector>
#include "Bone.h"

namespace tktk
{
	// スケルトンを管理するクラス
	class SkeletonData
	{
	public:

		explicit SkeletonData(const std::vector<Bone>& boneArray);
		~SkeletonData();

		SkeletonData(const SkeletonData& other) = delete;
		SkeletonData& operator = (const SkeletonData& other) = delete;

	public:

		// ボーンの数を取得する
		unsigned int getSize() const;

		// ボーン情報の配列を取得する
		const std::vector<Bone>& getBoneArray() const;

	private:

		std::vector<Bone> m_boneArray;
	};
}
#endif // !SKELETON_DATA_H_