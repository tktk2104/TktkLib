#ifndef ANIMATION_DATA_H_
#define ANIMATION_DATA_H_

#include <string>
#include <vector>
#include <unordered_map>
#include "KeyFrame.h"

namespace tktk
{
	// アニメーションを管理するクラス
	class AnimationData
	{
	public:

		explicit AnimationData(const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames);
		~AnimationData();

		AnimationData(const AnimationData& other) = delete;
		AnimationData& operator = (const AnimationData& other) = delete;

	public:

		// 指定したフレームのキーフレーム情報を計算する
		KeyFrame calculateKeyFrame(const std::string& boneName, float frameNo) const;

		// アニメーションの終了フレームを見つける
		float findEndFrameNo() const;

	private:

		// ボーンごとのキーフレームの配列を管理する連想配列
		std::unordered_map<std::string, std::vector<KeyFrame>> m_boneKeyFrames;
	};
}
#endif // !ANIMATION_DATA_H_