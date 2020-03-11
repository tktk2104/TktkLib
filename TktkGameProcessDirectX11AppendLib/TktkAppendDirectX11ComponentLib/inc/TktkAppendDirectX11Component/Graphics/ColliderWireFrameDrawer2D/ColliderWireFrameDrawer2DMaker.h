#ifndef COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_
#define COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "ColliderWireFrameDrawer2D.h"

namespace tktk
{
	class ColliderWireFrameDrawer2DMaker
	{
	public:

		static ColliderWireFrameDrawer2DMaker& makeStart(GameObjectPtr user);

	private:

		static ColliderWireFrameDrawer2DMaker m_self;

	private:

		// プライベートコンストラクタ達
		ColliderWireFrameDrawer2DMaker() = default;
		ColliderWireFrameDrawer2DMaker(const ColliderWireFrameDrawer2DMaker& other) = default;
		ColliderWireFrameDrawer2DMaker& operator = (const ColliderWireFrameDrawer2DMaker& other) = default;

	public:

		// 作成する
		CfpPtr<ColliderWireFrameDrawer2D> create();

		// 描画優先度を設定する
		ColliderWireFrameDrawer2DMaker& drawPriority(float value);

		// 線の色を設定する
		ColliderWireFrameDrawer2DMaker& lineColor(const Color& value);

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		float m_drawPriority{ 0.0f };
		Color m_lineColor{ Color::white };
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_
