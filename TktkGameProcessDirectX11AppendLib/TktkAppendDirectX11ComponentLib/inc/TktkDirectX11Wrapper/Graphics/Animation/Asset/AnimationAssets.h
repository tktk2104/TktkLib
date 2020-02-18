#ifndef ANIMATION_ASSETS_H_
#define ANIMATION_ASSETS_H_

#include <unordered_map>
#include "AnimationData.h"

namespace tktk
{
	// 「AnimationData」を管理するクラス
	class AnimationAssets
	{
	public:

		AnimationAssets() = default;
		~AnimationAssets();

		AnimationAssets(const AnimationAssets& other) = delete;
		AnimationAssets& operator = (const AnimationAssets& other) = delete;

	public:

		// 新たなアニメーションを作成する
		void create(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames);

		// 指定したアニメーションを削除する
		void erase(int id);

		// 全てのアニメーションを削除する
		void clear();

		// 指定したアニメーションを管理するクラスの参照を取得する
		const AnimationData& getData(int id) const;

	private:

		// アニメーションを管理するクラスの連想配列
		std::unordered_map<int, AnimationData> m_assets;
	};
}
#endif // !ANIMATION_ASSETS_H_