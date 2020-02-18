#ifndef ANIMATION_LOADER_H_
#define ANIMATION_LOADER_H_

#include <string>

namespace tktk
{
	// アニメーションを読み込む補助クラス
	class AnimationLoader
	{
	public:

		// ボーン名->キーフレーム情報->ボーン名…と整列しているバイナリデータの読み込み専用
		static void load(int id, const std::string& fileName);
	};
}
#endif // !ANIMATION_LOADER_H_