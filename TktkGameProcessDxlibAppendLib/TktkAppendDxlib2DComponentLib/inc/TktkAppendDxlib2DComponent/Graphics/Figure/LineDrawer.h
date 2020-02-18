#ifndef LINE_DRAWER_H_
#define LINE_DRAWER_H_

#include <memory>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"

namespace tktk
{
	// 線分を描画するコンポーネント
	// 【前提コンポーネント：Transform2D】
	class LineDrawer
		: public ComponentBase
	{
	public:

		LineDrawer(
			const Vector2& relativeFirstPos,	// 自身の座標から見た線分の１つ目の座標
			const Vector2& relativeSecondPos,	// 自身の座標から見た線分の２つ目の座標
			float lineThickness,				// 線分の太さ
			const Color& lineColor,				// 線分の描画色
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

		// 自身の座標から見た線分の１つ目の座標を取得
		const Vector2& getRelativeFirstPos() const;
		// 自身の座標から見た線分の１つ目の座標を再設定
		void setRelativeFirstPos(const Vector2& relativeFirstPos);

		// 自身の座標から見た線分の２つ目の座標を取得
		const Vector2& getRelativeSecondPos() const;
		// 自身の座標から見た線分の２つ目の座標を再設定
		void setRelativeSecondPos(const Vector2& relativeSecondPos);

		// 線分の太さを取得
		float getLineThickness() const;
		// 線分の太さを再設定
		void setLineThickness(float lineThickness);

		// 線分の描画色を取得
		const Color& getLineColor() const;
		// 線分の描画色を再設定
		void setLineColor(const Color& lineColor);

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
		std::weak_ptr<Transform2D> m_transform2D;

		// 自身の座標から見た線分の１つ目の座標
		Vector2 m_relativeFirstPos;

		// 自身の座標から見た線分の２つ目の座標
		Vector2 m_relativeSecondPos;

		// 線分の太さ
		float m_lineThickness;

		// 線分の描画色
		Color m_lineColor;

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
#endif // !LINE_DRAWER_H_