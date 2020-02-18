#ifndef ANIMATION_MANAGER_H_
#define ANIMATION_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/AnimationAssets.h"

namespace tktk
{
	// 「AnimationAssets」に簡単にアクセスするためのクラス
	class AnimationManager
	{
	public:

		// 「AnimationAssets」を生成
		static void setUp();

	public:

		// 新たなアニメーションをロードする
		static void create(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames);

		// 指定したアニメーションを削除する
		static void erase(int id);

		// 全てのアニメーションを削除する
		static void clear();

		// 指定したアニメーションを管理するクラスの参照を取得する
		static const AnimationData& getData(int id);

	private:

		static CfpPtr<AnimationAssets> m_assetsPtr;
	};
}
#endif // !ANIMATION_MANAGER_H_
