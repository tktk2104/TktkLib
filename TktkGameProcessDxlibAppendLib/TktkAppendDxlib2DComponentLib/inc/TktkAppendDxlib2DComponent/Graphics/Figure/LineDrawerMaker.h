#ifndef LINE_DRAWER_MAKER_H_
#define LINE_DRAWER_MAKER_H_

#include <memory>
#include "LineDrawer.h"

namespace tktk
{
	struct LineDrawerMaker
	{
	public:

		// インスタンス作成開始
		static LineDrawerMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<LineDrawer> create();

		// 自身の座標から見た線分の１つ目の座標を設定
		LineDrawerMaker& relativeFirstPos(const Vector2& value);

		// 自身の座標から見た線分の２つ目の座標を設定
		LineDrawerMaker& relativeSecondPos(const Vector2& value);

		// 線分の線の太さを設定する
		LineDrawerMaker& lineThickness(float value);

		// 線分の描画色を設定する
		LineDrawerMaker& lineColor(const Color& value);

		// 描画優先度を設定する
		LineDrawerMaker& drawPriority(float value);

		// 描画のブレンド方法の種類を設定する
		LineDrawerMaker& blendMode(BlendMode value);

		// 描画のブレンドに使用する値を設定する
		LineDrawerMaker& blendParam(float value);

		// アンチエイリアスの使用フラグを設定する
		LineDrawerMaker& useAntialiasing(bool value);

		// 描画するレンダーターゲットを設定する
		LineDrawerMaker& renderTargetId(int value);

	private:

		// 自身のポインタ
		static LineDrawerMaker m_self;

	private:

		Vector2 m_relativeFirstPos{ Vector2(-1.0f, -1.0f) };
		Vector2 m_relativeSecondPos{ Vector2( 1.0f,  1.0f) };
		float m_lineThickness{ 1.0f };
		Color m_lineColor{ Color::white };
		float m_drawPriority{ 0 };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		bool m_useAntialiasing{ true };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};
}
#endif // !LINE_DRAWER_MAKER_H_
