#ifndef BOX_DRAWER_MAKER_H_
#define BOX_DRAWER_MAKER_H_

#include <memory>
#include "BoxDrawer.h"

namespace tktk
{
	class BoxDrawerMaker
	{
	public:

		static BoxDrawerMaker& makeStart();

	public:

		std::shared_ptr<BoxDrawer> create();

		// 描画優先度を設定する
		BoxDrawerMaker& drawPriority(float value);

		// 立方体の大きさを設定する
		BoxDrawerMaker& boxSize(const Vector3& value);

		// 立方体のローカル座標を設定する
		BoxDrawerMaker& localPosition(const Vector3& value);

		// 塗りつぶしフラグを設定する
		BoxDrawerMaker& isFill(bool value);

		// 立方体の描画色を設定する
		BoxDrawerMaker& boxColor(const Color& value);

		// 描画のブレンド方法の種類を設定する
		BoxDrawerMaker& blendMode(const BlendMode& value);

		// 描画のブレンドに使用する値を設定する
		BoxDrawerMaker& blendParam(float value);

		// ライトを使用して描画を行うか？
		BoxDrawerMaker& useLight(bool value);

		// Zバッファを使用して描画を行うか?
		BoxDrawerMaker& writeZBuffer(bool value);

		// 描画するレンダーターゲットを設定する
		BoxDrawerMaker& renderTargetId(int value);

		// 影を生成するかを設定
		BoxDrawerMaker& createShadow(bool value);

		// 影の生成を行うコンポーネントの描画優先度を設定
		BoxDrawerMaker& shadowCreatorPriority(float value);

	private:

		static BoxDrawerMaker m_self;

	private:

		float m_drawPriority{ 0.0f };
		Vector3 m_boxSize{ Vector3::one };
		Vector3 m_localPosition{ Vector3::zero };
		bool m_isFill{ true };
		Color m_boxColor{ Color::white };
		BlendMode m_blendMode{ BlendMode::None };
		float m_blendParam{ 1.0f };
		bool m_useLight{ true };
		bool m_writeZBuffer{ true };
		int m_renderTargetId{ -1 };
		bool m_createShadow{ false };
		float m_shadowCreatorPriority{ 100 };
	};
}
#endif // !BOX_DRAWER_MAKER_H_