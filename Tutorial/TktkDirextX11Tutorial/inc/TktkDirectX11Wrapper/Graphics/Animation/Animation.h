#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "Asset/AnimationData.h"

namespace tktk
{
	// 「AnimationManager」の実装の一部を隠すためのクラス
	class Animation
	{
	public:

		// 新たなアニメーションをロードする
		// ※この関数でアニメーションをロードする場合、idは1以上でなければならない
		static void create(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames);

		// 指定したアニメーションを削除する
		// ※この関数でアニメーションを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// 指定したアニメーションを管理するクラスの参照を取得する
		static const AnimationData& getData(int id);
	};
}
#endif // !ANIMATION_H_