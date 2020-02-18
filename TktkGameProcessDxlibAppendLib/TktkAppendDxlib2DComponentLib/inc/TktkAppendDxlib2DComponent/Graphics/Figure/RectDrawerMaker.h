#ifndef RECT_DRAWER_MAKER_H_
#define RECT_DRAWER_MAKER_H_

#include <memory>
#include "RectDrawer.h"

namespace tktk
{
	struct RectDrawerMaker
	{
	public:

		// インスタンス作成開始
		static RectDrawerMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<RectDrawer> create();

		// 長方形の大きさを設定
		RectDrawerMaker& rectSize(const Vector2& value);

		// 長方形のローカル座標を設定
		RectDrawerMaker& localPosition(const Vector2& value);

		// 長方形の線の太さを設定する
		RectDrawerMaker& lineThickness(float value);

		// 塗りつぶしフラグを設定する
		RectDrawerMaker& isFill(bool value);

		// 長方形の描画色を設定する
		RectDrawerMaker& rectColor(const Color& value);

		// 描画優先度を設定する
		RectDrawerMaker& drawPriority(float value);

		// 描画のブレンド方法の種類を設定する
		RectDrawerMaker& blendMode(BlendMode value);

		// 描画のブレンドに使用する値を設定する
		RectDrawerMaker& blendParam(float value);

		// アンチエイリアスの使用フラグを設定する
		RectDrawerMaker& useAntialiasing(bool value);

		// 描画するレンダーターゲットを設定する
		RectDrawerMaker& renderTargetId(int value);

	private:

		// 自身のポインタ
		static RectDrawerMaker m_self;

	private:

		Vector2 m_rectSize{ Vector2::one };
		Vector2 m_localPosition{ Vector2::zero };
		float m_lineThickness{ 1.0f };
		bool m_isFill{ true };
		Color m_rectColor{ Color::white };
		float m_drawPriority{ 0 };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		bool m_useAntialiasing{ true };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};
}
#endif // !RECT_DRAWER_MAKER_H_
