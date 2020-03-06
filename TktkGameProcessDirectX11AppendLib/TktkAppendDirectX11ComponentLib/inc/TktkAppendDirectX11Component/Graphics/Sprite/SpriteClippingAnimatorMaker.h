#ifndef SPRITE_CLIPPING_ANIMATOR_MAKER_H_
#define SPRITE_CLIPPING_ANIMATOR_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "SpriteClippingAnimator.h"

namespace tktk
{
	class SpriteClippingAnimatorMaker
	{
	public:

		// インスタンス作成開始
		static SpriteClippingAnimatorMaker& makeStart(GameObjectPtr user);

	private:

		// 自身のポインタ
		static SpriteClippingAnimatorMaker m_self;

	private:

		// プライベートコンストラクタ達
		SpriteClippingAnimatorMaker() = default;
		SpriteClippingAnimatorMaker(const SpriteClippingAnimatorMaker& other) = default;
		SpriteClippingAnimatorMaker& operator = (const SpriteClippingAnimatorMaker& other) = default;

	public:

		// 作成する
		CfpPtr<SpriteClippingAnimator> create();

		// アニメーションのコマごとのテクスチャのクリッピング描画範囲の左上座標を設定
		SpriteClippingAnimatorMaker& animFrameTextureLeftTopPosArray(const std::vector<Vector2>& value);

		// アニメーション１コマにかける時間を設定
		SpriteClippingAnimatorMaker& animationIntervalSec(float value);

		// アニメーションをループさせるかを設定
		SpriteClippingAnimatorMaker& isLoop(bool value);

		// アニメーションの再生速度を設定
		SpriteClippingAnimatorMaker& animSpeedRate(float value);

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		std::vector<Vector2> m_animFrameTextureLeftTopPosArray{  };
		float m_animationIntervalSec{ 1.0f };
		bool m_isLoop{ true };
		float m_animSpeedRate{ 1.0f };
	};
}
#endif // !SPRITE_CLIPPING_ANIMATOR_MAKER_H_
