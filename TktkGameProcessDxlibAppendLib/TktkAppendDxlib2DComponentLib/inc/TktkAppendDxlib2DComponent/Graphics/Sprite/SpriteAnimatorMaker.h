#ifndef SPRITE_ANIMATOR_MAKER_H_
#define SPRITE_ANIMATOR_MAKER_H_

#include <memory>
#include <vector>
#include "SpriteAnimator.h"

namespace tktk
{
	class SpriteAnimatorMaker
	{
	public:

		// インスタンス作成開始
		static SpriteAnimatorMaker& makeStart();

	public:

		// 作成する
		SpriteAnimator* create();

		// 使用するテクスチャのIdを設定する
		SpriteAnimatorMaker& textureId(int value);

		// アニメーションに使用する分割画像番号を設定する
		template <int... Args>
		SpriteAnimatorMaker& splitTextureIndexList()
		{
			m_splitTextureIndexList = std::vector<int>({ Args... });
			return *this;
		};

		// アニメーションで使用する静止画１枚当たりの時間を設定する（秒）
		SpriteAnimatorMaker& animationIntervalSec(float value);

		// アニメーションをループさせるかを設定する
		SpriteAnimatorMaker& loop(bool value);

		// アニメーションの再生速度倍率を設定する
		SpriteAnimatorMaker& animSpeedRate(float value);

	private:

		// 自身のポインタ
		static SpriteAnimatorMaker m_self;

	private:

		int m_textureId{ -1 };
		std::vector<int> m_splitTextureIndexList;
		float m_animationIntervalSec{ 0.1f };
		bool m_loop{ false };
		float m_animSpeedRate{ 1.0f };
	};
}
#endif // !SPRITE_ANIMATOR_MAKER_H_