#ifndef SPRITE_DRAWER_MAKER_H_
#define SPRITE_DRAWER_MAKER_H_

#include "SpriteDrawer.h"

namespace tktk
{
	// SpriteDrawerのインスタンスを作成する構造体
	struct SpriteDrawerMaker
	{
	public:

		// インスタンス作成開始
		static SpriteDrawerMaker& makeStart();

	public:

		// 作成する
		SpriteDrawer* create();

		// 表示するテクスチャのIdを設定する
		SpriteDrawerMaker& textureId(int value);

		// 表示するテクスチャの分割読み込み番号を設定する
		SpriteDrawerMaker& splitTextureIndex(int value = -1);

		// 描画優先度を設定する
		SpriteDrawerMaker& drawPriority(float value);

		// スプライトの中心位置を設定する（割合 0.0～1.0）
		SpriteDrawerMaker& spriteCenterPosRate(const Vector2& value = Vector2(0.5f, 0.5f));

		// 描画のブレンド方法の種類を設定する
		SpriteDrawerMaker& blendMode(BlendMode value);

		// 描画のブレンドに使用する値を設定する
		SpriteDrawerMaker& blendParam(float value = 1.0f);

		// 表示するテクスチャの反転フラグを設定する
		SpriteDrawerMaker& reverseFlag(ReverseFlag value);

		// 表示するテクスチャの切抜き描画範囲を設定する
		SpriteDrawerMaker& useClipping(
			const Vector2& clippingLeftTopPos,		// 切り抜く左上座標
			const Vector2& clippingRightBottomPos	// 切り抜く右下座標
		);

		// 描画するレンダーターゲットを設定する
		SpriteDrawerMaker& renderTargetId(int value);

	private:

		// 自身のポインタ
		static SpriteDrawerMaker m_self;

	private:

		int m_textureId{ -1 };
		int m_splitTextureIndex{ -1 };
		float m_drawPriority{ 0 };
		Vector2 m_spriteCenterPosRate{ Vector2(0.5f, 0.5f) };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		ReverseFlag m_reverseFlag{ ReverseFlag::NOT_REVERSE };
		bool m_useClipping{ false };
		Vector2 m_clippingLeftTopPos{ Vector2::zero };
		Vector2 m_clippingRightBottomPos{ Vector2::one };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};
}
#endif // !SPRITE_DRAWER_MAKER_H_