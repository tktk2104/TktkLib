#ifndef COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_
#define COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "ColliderWireFrameDrawer2D.h"

namespace tktk
{
	class ColliderWireFrameDrawer2DMaker
	{
	public:

		// インスタンス作成開始
		static ColliderWireFrameDrawer2DMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<ColliderWireFrameDrawer2D> create();

	public:

		ColliderWireFrameDrawer2DMaker& drawPriority(float value);

		ColliderWireFrameDrawer2DMaker& wireFrameColor(const Color& value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static ColliderWireFrameDrawer2DMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{};
		float m_drawPriority{ 0.0f };
		Color m_wireFrameColor{ Color::white };
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_