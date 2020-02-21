#ifndef RECT_DRAWER_H_
#define RECT_DRAWER_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"

namespace tktk
{
	// 長方形を描画するコンポーネント
	// 【前提コンポーネント：Transform2D】
	class RectDrawer
		: public ComponentBase
	{
	public:

		RectDrawer(
			const Vector2& rectSize,		// 長方形の大きさ
			const Vector2& localPosition,	// 長方形のローカル座標
			float lineThickness,			// 長方形の辺の太さ
			bool isFill,					// 塗りつぶしフラグ
			const Color& rectColor,			// 長方形の描画色
			float drawPriority,				// 描画優先度
			BlendMode blendMode,			// 描画のブレンド方法の種類
			float blendParam,				// 描画のブレンドに使用する値
			bool useAntialiasing			// アンチエイリアスの使用フラグ
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// 長方形の大きさを取得
		const Vector2& getRectSize() const;
		// 長方形の大きさを再設定
		void setRectSize(const Vector2& rectSize);

		// 長方形のローカル座標を取得
		const Vector2& getLocalPosition() const;
		// 長方形のローカル座標を再設定
		void setLocalPosition(const Vector2& localPosition);

		// 長方形の辺の太さを取得
		float getLineThickness() const;
		// 長方形の辺の太さを再設定
		void setLineThickness(float lineThickness);

		// 塗りつぶしフラグを取得
		bool getIsFill() const;
		// 塗りつぶしフラグを再設定
		void setIsFill(bool isFill);

		// 長方形の描画色を取得
		const Color& getRectColor() const;
		// 長方形の描画色を再設定
		void setRectColor(const Color& rectColor);

		// 描画のブレンド方法の種類を取得
		BlendMode getBlendMode() const;
		// 描画のブレンド方法の種類を再設定
		void setBlendMode(BlendMode blendMode);

		// 描画のブレンドに使用する値を取得
		float getBlendParam() const;
		// 描画のブレンドに使用する値を再設定
		void setBlendParam(float blendParam);

		// アンチエイリアスの使用フラグを取得
		bool getUseAntialiasing() const;
		// アンチエイリアスの使用フラグを再設定
		void setUseAntialiasing(bool useAntialiasing);

		// 指定したレンダーターゲットに描画する
		void useRenderTarget(int renderTargetId);
		// レンダーターゲットを使用せずに描画する
		void unUseRenderTarget();

	private:

		// 自身の２次元座標コンポーネント
		CfpPtr<Transform2D> m_transform2D;

		// 長方形の大きさ
		Vector2 m_rectSize;

		// 長方形のローカル座標
		Vector2 m_localPosition;

		// 長方形の辺の太さ
		float m_lineThickness;

		// 塗りつぶしフラグ
		bool m_isFill;

		// 長方形の描画色
		Color m_rectColor;

		// 描画のブレンド方法の種類
		BlendMode m_blendMode;

		// 描画のブレンドに使用する値
		float m_blendParam;

		// アンチエイリアスの使用フラグ
		bool m_useAntialiasing;

		// レンダーターゲットに描画するか
		bool m_useRenderTarget{ false };

		// 描画するレンダーターゲットのId
		int m_renderTargetId{ -1 };
	};
}
#endif // !RECT_DRAWER_H_