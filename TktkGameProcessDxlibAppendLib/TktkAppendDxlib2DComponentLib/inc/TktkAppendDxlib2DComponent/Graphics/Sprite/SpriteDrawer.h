#ifndef SPRITE_DRAWER_H_
#define SPRITE_DRAWER_H_

#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "../../../TktkDxlib2DWrapper/Assets/TextureAssets/TextureAssets.h"
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"
#include "ReverseFlag.h"

namespace tktk
{
	// スプライトを描画するコンポーネント
	// 【前提コンポーネント：Transform2D】
	class SpriteDrawer
		: public ComponentBase
	{
	public:

		SpriteDrawer(
			int textureId,							// 表示するテクスチャのId
			int splitTextureIndex,					// 表示するテクスチャの分割読み込み番号
			float drawPriority,						// 描画優先度
			const Vector2& spriteCenterPosRate,		// スプライトの中心位置（割合 0.0～1.0）
			BlendMode blendMode,					// 描画のブレンド方法の種類
			float blendParam,						// 描画のブレンドに使用する値
			unsigned int reverseFlag,				// 描画する画像を反転するか
			bool useClipping,						// 切抜き描画を行うか？
			const Vector2& clippingLeftTopPos,		// 切り抜く左上座標
			const Vector2& clippingRightBottomPos	// 切り抜く右下座標
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// テクスチャIDを取得
		int getTextureId() const;
		// テクスチャIDの再設定
		void setTextureId(int textureId);

		// 表示するテクスチャの分割読み込み番号を取得
		int getSplitTextureIndex() const;
		// 表示するテクスチャの分割読み込み番号を再設定
		// -1を入力すると切り抜かずに描画する
		void setSplitTextureIndex(int splitTextureIndex);

		// スプライトの中心位置（割合 0.0～1.0）を取得
		const Vector2& getSpriteCenterPosRate() const;
		// スプライトの中心位置（割合 0.0～1.0）を再設定
		void setSpriteCenterPosRate(const Vector2& spriteCenterPosRate = Vector2(0.5f, 0.5f));

		// スプライトを切り抜いて表示する
		void useClipping(
			const Vector2& clippingLeftTopPos,		// 切り抜く左上座標
			const Vector2& clippingRightBottomPos	// 切り抜く右下座標
		);
		// スプライトを切り抜いて表示するのをやめる
		void unUseClipping();

		// 描画のブレンド方法の種類を取得
		BlendMode getBlendMode() const;
		// 描画のブレンド方法の種類を再設定
		void setBlendMode(BlendMode blendMode);

		// 描画のブレンドに使用する値を取得
		float getBlendParam() const;
		// 描画のブレンドに使用する値を再設定
		void setBlendParam(float blendParam);

		// 描画する画像の反転フラグを再設定
		void setReverseFlag(unsigned int reverseFlag);

		// 指定したレンダーターゲットに描画する
		void useRenderTarget(int renderTargetId);
		// レンダーターゲットを使用せずに描画する
		void unUseRenderTarget();

	private:

		// 自身の２次元座標コンポーネント
		CfpPtr<Transform2D> m_transform2D;

		// テクスチャリソースの管理クラス
		CfpPtr<TextureAssets> m_textureAssets;

		// 表示するテクスチャのId
		int m_textureId{ -1 };

		// 表示するテクスチャの分割読み込み番号
		int m_splitTextureIndex{ -1 };

		// スプライトの中心位置（割合 0.0～1.0）
		Vector2 m_spriteCenterPosRate{ Vector2(0.5f, 0.5f) };

		// 描画のブレンド方法の種類
		BlendMode m_blendMode;

		// 描画のブレンドに使用する値
		float m_blendParam;

		// 反転フラグ
		unsigned int m_reverseFlag{ NOT_REVERSE };

		// テクスチャの切抜きを行うか
		bool m_useClipping{ false };

		// テクスチャの切抜きに使用する左上座標
		Vector2 m_clippingLeftTopPos{ Vector2::zero };

		// テクスチャの切抜きに使用する右下座標
		Vector2 m_clippingRightBottomPos{ Vector2::one };

		// レンダーターゲットに描画するか
		bool m_useRenderTarget{ false };

		// 描画するレンダーターゲットのId
		int m_renderTargetId{ -1 };
	};
}
#endif // !SPRITE_DRAWER_H_