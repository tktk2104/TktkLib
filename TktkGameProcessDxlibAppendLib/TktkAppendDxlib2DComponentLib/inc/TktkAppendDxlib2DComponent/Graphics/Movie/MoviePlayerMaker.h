#ifndef MOVIE_PLAYER_MAKER_H_
#define MOVIE_PLAYER_MAKER_H_

#include "MoviePlayer.h"

namespace tktk
{
	class MoviePlayerMaker
	{
	public:

		// インスタンス作成開始
		static MoviePlayerMaker& makeStart();

	public:

		// 作成する
		MoviePlayer* create();

		// 描画優先度を設定する
		MoviePlayerMaker& drawPriority(float value);

		// 表示する動画のIdを設定する
		MoviePlayerMaker& movieId(int value);

		// 動画の中心位置を設定する（割合 0.0～1.0）
		MoviePlayerMaker& movieCenterPosRate(const Vector2& value = Vector2(0.5f, 0.5f));

		// 描画のブレンド方法の種類を設定する
		MoviePlayerMaker& blendMode(BlendMode value);

		// 描画のブレンドに使用する値を設定する
		MoviePlayerMaker& blendParam(float value = 1.0f);

		// 表示する動画の反転フラグを設定する
		MoviePlayerMaker& reverseFlag(ReverseFlag value);

		// 表示する動画の切抜き描画範囲を設定する
		MoviePlayerMaker& useClipping(
			const Vector2& clippingLeftTopPos,		// 切り抜く左上座標
			const Vector2& clippingRightBottomPos	// 切り抜く右下座標
		);

		// 描画するレンダーターゲットを設定する
		MoviePlayerMaker& renderTargetId(int value);

	private:

		// 自身のポインタ
		static MoviePlayerMaker m_self;

	private:

		float m_drawPriority{ 0 };
		int m_movieId{ -1 };
		Vector2 m_movieCenterPosRate{ Vector2(0.5f, 0.5f) };
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
#endif // !MOVIE_PLAYER_MAKER_H_