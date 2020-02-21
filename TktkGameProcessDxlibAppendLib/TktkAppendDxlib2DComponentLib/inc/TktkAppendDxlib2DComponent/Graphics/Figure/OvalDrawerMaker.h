#ifndef OVAL_DRAWER_MAKER_H_
#define OVAL_DRAWER_MAKER_H_

#include "OvalDrawer.h"

namespace tktk
{
	struct OvalDrawerMaker
	{
	public:

		// インスタンス作成開始
		static OvalDrawerMaker& makeStart();

	public:

		// 作成する
		OvalDrawer* create();

	public:

		// 楕円の大きさを設定する
		OvalDrawerMaker& ovalSize(const Vector2& value);

		// 楕円のローカル座標を設定する
		OvalDrawerMaker& localPosition(const Vector2& value);

		// 楕円の線の太さを設定する
		OvalDrawerMaker& lineThickness(float value);

		// 塗りつぶしフラグを設定する
		OvalDrawerMaker& isFill(bool value);

		/// 楕円の描画色を設定する
		OvalDrawerMaker& ovalColor(const Color& value);

		// 描画優先度を設定する
		OvalDrawerMaker& drawPriority(float value);

		// 描画のブレンド方法の種類を設定する
		OvalDrawerMaker& blendMode(BlendMode value);

		// 描画のブレンドに使用する値を設定する
		OvalDrawerMaker& blendParam(float value);

		// アンチエイリアスの使用フラグを設定する
		OvalDrawerMaker& useAntialiasing(bool value);

		// アンチエイリアスを使用する時に使う円を形作る頂点の数を設定する
		OvalDrawerMaker& vertexNum(int value);

		// 描画するレンダーターゲットを設定する
		OvalDrawerMaker& renderTargetId(int value);

	private:

		// 自身のポインタ
		static OvalDrawerMaker m_self;

	private:

		Vector2 m_ovalSize{ Vector2::one };
		Vector2 m_localPosition{ Vector2::zero };
		float m_lineThickness{ 1.0f };
		bool m_isFill{ true };
		Color m_ovalColor{ Color::white };
		float m_drawPriority{ 0 };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		bool m_useAntialiasing{ true };
		int m_vertexNum{ 32 };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};
}
#endif // !OVAL_DRAWER_MAKER_H_
