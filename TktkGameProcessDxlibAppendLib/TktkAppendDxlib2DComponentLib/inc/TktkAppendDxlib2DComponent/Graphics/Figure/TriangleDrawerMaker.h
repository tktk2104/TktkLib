#ifndef TRIANGLE_DRAWER_MAKER_H_
#define TRIANGLE_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "TriangleDrawer.h"

namespace tktk
{
	struct TriangleDrawerMaker
	{
	public:

		// インスタンス作成開始
		static TriangleDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<TriangleDrawer> create();

	public:

		// 自身の座標から見た三角形の１つ目の座標を設定
		TriangleDrawerMaker& relativeFirstPos(const Vector2& value);

		// 自身の座標から見た三角形の２つ目の座標を設定
		TriangleDrawerMaker& relativeSecondPos(const Vector2& value);

		//自身の座標から見た三角形の３つ目の座標を設定
		TriangleDrawerMaker& relativeThirdPos(const Vector2& value);

		// 三角形の線の太さを設定する
		TriangleDrawerMaker& lineThickness(float value);

		// 塗りつぶしフラグを設定する
		TriangleDrawerMaker& isFill(bool value);

		// 三角形の描画色を設定する
		TriangleDrawerMaker& triangleColor(const Color& value);

		// 描画優先度を設定する
		TriangleDrawerMaker& drawPriority(float value);

		// 描画のブレンド方法の種類を設定する
		TriangleDrawerMaker& blendMode(BlendMode value);

		// 描画のブレンドに使用する値を設定する
		TriangleDrawerMaker& blendParam(float value);

		// アンチエイリアスの使用フラグを設定する
		TriangleDrawerMaker& useAntialiasing(bool value);

		// 描画するレンダーターゲットを設定する
		TriangleDrawerMaker& renderTargetId(int value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static TriangleDrawerMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{};
		Vector2 m_relativeFirstPos{ Vector2(0.0f, 1.0f) };
		Vector2 m_relativeSecondPos{ Vector2(1.0f, -1.0f) };
		Vector2 m_relativeThirdPos{ Vector2(1.0f, 1.0f) };
		float m_lineThickness{ 1.0f };
		bool m_isFill{ true };
		Color m_triangleColor{ Color::white };
		float m_drawPriority{ 0.0f };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		bool m_useAntialiasing{ true };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};
}
#endif // !TRIANGLE_DRAWER_MAKER_H_

