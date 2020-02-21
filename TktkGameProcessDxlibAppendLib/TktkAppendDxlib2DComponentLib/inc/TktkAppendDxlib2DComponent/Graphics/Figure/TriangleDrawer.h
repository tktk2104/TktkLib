#ifndef TRIANGLE_DRAWER_H_
#define TRIANGLE_DRAWER_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"

namespace tktk
{
	// 三角形を描画するコンポーネント
	// 【前提コンポーネント：Transform2D】
	class TriangleDrawer
		: public ComponentBase
	{
	public:

		TriangleDrawer(
			const Vector2& relativeFirstPos,	// 自身の座標から見た三角形の１つ目の座標
			const Vector2& relativeSecondPos,	// 自身の座標から見た三角形の２つ目の座標
			const Vector2& relativeThirdPos,	// 自身の座標から見た三角形の３つ目の座標
			float lineThickness,				// 三角形の辺の太さ
			bool isFill,						// 塗りつぶしフラグ
			const Color& triangleColor,			// 三角形の描画色
			float drawPriority,					// 描画優先度
			BlendMode blendMode,				// 描画のブレンド方法の種類
			float blendParam,					// 描画のブレンドに使用する値
			bool useAntialiasing				// アンチエイリアスの使用フラグ
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// 自身の座標から見た三角形の１つ目の座標を取得
		const Vector2& getRelativeFirstPos() const;

		// 自身の座標から見た三角形の１つ目の座標を再設定
		void setRelativeFirstPos(const Vector2& relativeFirstPos);

		// 自身の座標から見た三角形の２つ目の座標を取得
		const Vector2& getRelativeSecondPos() const;

		// 自身の座標から見た三角形の２つ目の座標を再設定
		void setRelativeSecondPos(const Vector2& relativeSecondPos);

		// 自身の座標から見た三角形の３つ目の座標を取得
		const Vector2& getRelativeThirdPos() const;

		// 自身の座標から見た三角形の３つ目の座標を再設定
		void setRelativeThirdPos(const Vector2& relativeSecondPos);

		// 三角形の辺の太さを取得
		float getLineThickness() const;

		// 三角形の辺の太さを再設定
		void setLineThickness(float lineThickness);

		// 塗りつぶしフラグを取得
		bool getIsFill() const;

		// 塗りつぶしフラグを再設定
		void setIsFill(bool isFill);

		// 三角形の描画色を取得
		const Color& getTriangleColor() const;

		// 三角形の描画色を再設定
		void setTriangleColor(const Color& triangleColor);

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

		// 自身の座標から見た三角形の１つ目の座標
		Vector2 m_relativeFirstPos;

		// 自身の座標から見た三角形の２つ目の座標
		Vector2 m_relativeSecondPos;

		// 自身の座標から見た三角形の３つ目の座標
		Vector2 m_relativeThirdPos;

		// 三角形の辺の太さ
		float m_lineThickness;

		// 塗りつぶしフラグ
		bool m_isFill;

		// 三角形の描画色
		Color m_triangleColor;

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
#endif // !TRIANGLE_DRAWER_H_