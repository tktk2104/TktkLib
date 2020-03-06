#ifndef SPRITE_CLIPPING_ANIMATOR_H_
#define SPRITE_CLIPPING_ANIMATOR_H_

#include <vector>
#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "SpriteClippingDrawer.h"

namespace tktk
{
	class SpriteClippingAnimator
		: public ComponentBase
	{
	public:

		SpriteClippingAnimator(
			const std::vector<Vector2>& animationFrameTexturePosArray,
			float animationIntervalSec,
			bool isLoop,
			float animSpeedRate
		);

	public:

		void start();
		void update();

	public:

		// アニメーションが終了したかを取得
		bool isEndAnimation() const;

		// アニメーションのコマごとのテクスチャのクリッピング描画範囲の左上座標を再設定
		void setAnimFrameTextureLeftTopPosArray(const std::vector<Vector2>& posArray);

		// アニメーションのコマごとのテクスチャのクリッピング描画範囲の左上座標を取得
		const std::vector<Vector2>& getAnimFrameTextureLeftTopPosArray() const;

		// アニメーションの再生速度を再設定
		void setAnimSpeedRate(float animSpeedRate);

		// アニメーションの再生速度を取得
		float getAnimSpeedRate() const;

		// アニメーションをループさせるかを再設定
		void setIsLoop(bool isLoop);

		// アニメーションのループフラグを取得
		bool getIsLoop() const;

	private:

		std::vector<Vector2> m_animFrameTextureLeftTopPosArray{  };
		float m_animSpeedRate{ 1.0f };
		float m_animationTimer{ 0.0f };
		float m_animationTotalTime{ 0.0f };
		float m_animationIntervalSec{ 1.0f };
		bool m_isLoop{ true };

		CfpPtr<SpriteClippingDrawer> m_spriteClippingDrawer{  };
	};
}
#endif // !SPRITE_CLIPPING_ANIMATOR_H_