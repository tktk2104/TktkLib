#ifndef SPHERE_DRAWER_MAKER_H_
#define SPHERE_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "SphereDrawer.h"

namespace tktk
{
	class SphereDrawerMaker
	{
	public:

		static SphereDrawerMaker& makeStart(GameObjectPtr user);

	public:

		CfpPtr<SphereDrawer> create();

		// 描画優先度を設定する
		SphereDrawerMaker& drawPriority(float value);

		// 球体の大きさを設定する
		SphereDrawerMaker& radius(float value);

		// 球体を描画する時のポリゴンの細かさを設定する
		SphereDrawerMaker& divNum(int value);

		// 球体のローカル座標を設定する
		SphereDrawerMaker& localPosition(const Vector3& value);

		// 塗りつぶしフラグを設定する
		SphereDrawerMaker& isFill(bool value);

		// 球体の描画色を設定する
		SphereDrawerMaker& sphereColor(const Color& value);

		// 描画のブレンド方法の種類を設定する
		SphereDrawerMaker& blendMode(const BlendMode& value);

		// 描画のブレンドに使用する値を設定する
		SphereDrawerMaker& blendParam(float value);

		// ライトを使用して描画を行うか？
		SphereDrawerMaker& useLight(bool value);

		// Zバッファを使用して描画を行うか?
		SphereDrawerMaker& writeZBuffer(bool value);

		// 描画するレンダーターゲットを設定する
		SphereDrawerMaker& renderTargetId(int value);

		// 影を生成するかを設定
		SphereDrawerMaker& createShadow(bool value);

		// 影の生成を行うコンポーネントの描画優先度を設定
		SphereDrawerMaker& shadowCreatorPriority(float value);

	private:

		static SphereDrawerMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{};
		float m_drawPriority{ 0.0f };
		float m_radius{ 1.0f };
		int m_divNum{ 30 };
		Vector3 m_localPosition{ Vector3::zero };
		bool m_isFill{ true };
		Color m_sphereColor{ Color::white };
		BlendMode m_blendMode{ BlendMode::None };
		float m_blendParam{ 1.0f };
		bool m_useLight{ true };
		bool m_writeZBuffer{ true };
		int m_renderTargetId{ -1 };
		bool m_createShadow{ false };
		float m_shadowCreatorPriority{ 100 };
	};
}
#endif // !SPHERE_DRAWER_MAKER_H_