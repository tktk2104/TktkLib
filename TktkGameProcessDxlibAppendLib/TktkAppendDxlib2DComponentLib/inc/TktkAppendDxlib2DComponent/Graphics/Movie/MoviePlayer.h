#ifndef MOVIE_PLAYER_H_
#define MOVIE_PLAYER_H_

#include <TktkMath/Vector2.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "../../../TktkDxlib2DWrapper/Assets/MovieAssets/MovieAssets.h"
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"
#include "../Sprite/ReverseFlag.h"

namespace tktk
{
	class MoviePlayer
		: public ComponentBase
	{
	public:

		MoviePlayer(
			float drawPriority,						// 描画優先度
			int movieId,							// 描画する動画のId
			const Vector2& movieCenterPosRate,		// 動画の中心位置（割合 0.0～1.0）
			BlendMode blendMode,					// 描画のブレンド方法の種類
			float blendParam,						// 描画のブレンドに使用する値
			unsigned int reverseFlag,				// 描画する動画を反転するか
			bool useClipping,						// 切抜き描画を行うか？
			const Vector2& clippingLeftTopPos,		// 切り抜く左上座標
			const Vector2& clippingRightBottomPos	// 切り抜く右下座標
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// ムービーIDを取得
		int getMovieId() const;
		// ムービーIDの再設定
		void setMovieId(int movieId);

		// 動画の中心位置（割合 0.0～1.0）を取得
		const Vector2& getMovieCenterPosRate() const;
		// 動画の中心位置（割合 0.0～1.0）を再設定
		void setMovieCenterPosRate(const Vector2& movieCenterPosRate = Vector2(0.5f, 0.5f));

		// 動画を切り抜いて表示する
		void useClipping(
			const Vector2& clippingLeftTopPos,		// 切り抜く左上座標
			const Vector2& clippingRightBottomPos	// 切り抜く右下座標
		);
		// 動画を切り抜いて表示するのをやめる
		void unUseClipping();

		// 描画のブレンド方法の種類を取得
		BlendMode getBlendMode() const;
		// 描画のブレンド方法の種類を再設定
		void setBlendMode(BlendMode blendMode);

		// 描画のブレンドに使用する値を取得
		float getBlendParam() const;
		// 描画のブレンドに使用する値を再設定
		void setBlendParam(float blendParam);

		// 描画する動画の反転フラグを再設定
		void setReverseFlag(unsigned int reverseFlag);

		// 指定したレンダーターゲットに描画する
		void useRenderTarget(int renderTargetId);
		// レンダーターゲットを使用せずに描画する
		void unUseRenderTarget();

	private:

		// 自身の２次元座標コンポーネント
		CfpPtr<Transform2D> m_transform2D;

		// 動画リソースの管理クラス
		CfpPtr<MovieAssets> m_movieAssets;

		// 表示する動画のId
		int m_movieId{ -1 };

		// スプライトの中心位置（割合 0.0～1.0）
		Vector2 m_movieCenterPosRate{ Vector2(0.5f, 0.5f) };

		// 描画のブレンド方法の種類
		BlendMode m_blendMode;

		// 描画のブレンドに使用する値
		float m_blendParam;

		// 反転フラグ
		unsigned int m_reverseFlag{ NOT_REVERSE };

		// 動画の切抜きを行うか
		bool m_useClipping{ false };

		// 動画の切抜きに使用する左上座標
		Vector2 m_clippingLeftTopPos{ Vector2::zero };

		// 動画の切抜きに使用する右下座標
		Vector2 m_clippingRightBottomPos{ Vector2::one };

		// レンダーターゲットに描画するか
		bool m_useRenderTarget{ false };

		// 描画するレンダーターゲットのId
		int m_renderTargetId{ -1 };
	};
}
#endif // !MOVIE_PLAYER_H_