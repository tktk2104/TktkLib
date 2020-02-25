#ifndef COLLIDER_WIREFRAME_DRAWER_3D_MAKER_H_
#define COLLIDER_WIREFRAME_DRAWER_3D_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "ColliderWireFrameDrawer3D.h"

namespace tktk
{
	class ColliderWireFrameDrawer3DMaker
	{
	public:

		// インスタンス作成開始
		static ColliderWireFrameDrawer3DMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<ColliderWireFrameDrawer3D> create();

		ColliderWireFrameDrawer3DMaker& drawPriority(float value);

		ColliderWireFrameDrawer3DMaker& wireFrameColor(const Color& value);

	private:

		// 自身のポインタ
		static ColliderWireFrameDrawer3DMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{};
		float m_drawPriority;
		Color m_wireFrameColor;
	};
}
#endif // !COLLIDER_WIREFRAME_DRAWER_3D_MAKER_H_