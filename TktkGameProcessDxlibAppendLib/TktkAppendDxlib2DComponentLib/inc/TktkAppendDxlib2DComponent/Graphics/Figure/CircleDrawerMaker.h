#ifndef CIRCLE_DRAWER_MAKER_H_
#define CIRCLE_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "CircleDrawer.h"

namespace tktk
{
	struct CircleDrawerMaker
	{
	public:

		// インスタンス作成開始
		static CircleDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<CircleDrawer> create();

		// 真円の半径を設定する
		CircleDrawerMaker& radius(float value);

		// 真円のローカル座標を設定する
		CircleDrawerMaker& localPosition(const Vector2& value);

		// 真円の線の太さを設定する
		CircleDrawerMaker& lineThickness(float value);

		// 塗りつぶしフラグを設定する
		CircleDrawerMaker& isFill(bool value);

		/// 真円の描画色を設定する
		CircleDrawerMaker& circleColor(const Color& value);

		// 描画優先度を設定する
		CircleDrawerMaker& drawPriority(float value);

		// 描画のブレンド方法の種類を設定する
		CircleDrawerMaker& blendMode(BlendMode value);

		// 描画のブレンドに使用する値を設定する
		CircleDrawerMaker& blendParam(float value);

		// アンチエイリアスの使用フラグを設定する
		CircleDrawerMaker& useAntialiasing(bool value);

		// アンチエイリアスを使用する時に使う円を形作る頂点の数を設定する
		CircleDrawerMaker& vertexNum(int value);

		// 描画するレンダーターゲットを設定する
		CircleDrawerMaker& renderTargetId(int value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static CircleDrawerMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{};
		float m_radius{ 1.0f };
		Vector2 m_localPosition{ Vector2::zero };
		float m_lineThickness{ 1.0f };
		bool m_isFill{ true };
		Color m_circleColor{ Color::white };
		float m_drawPriority{ 0.0f };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		bool m_useAntialiasing{ true };
		int m_vertexNum{ 32 };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};
}
#endif // !CIRCLE_DRAWER_MAKER_H_