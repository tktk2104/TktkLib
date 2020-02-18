#ifndef COLLIDER_WIREFRAME_DRAWER_3D_MAKER_H_
#define COLLIDER_WIREFRAME_DRAWER_3D_MAKER_H_

#include <memory>
#include "ColliderWireFrameDrawer3D.h"

namespace tktk
{
	class ColliderWireFrameDrawer3DMaker
	{
	public:

		// インスタンス作成開始
		static ColliderWireFrameDrawer3DMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<ColliderWireFrameDrawer3D> create();

		ColliderWireFrameDrawer3DMaker& drawPriority(float value);

		ColliderWireFrameDrawer3DMaker& wireFrameColor(const Color& value);

	private:

		// 自身のポインタ
		static ColliderWireFrameDrawer3DMaker m_self;

	private:

		float m_drawPriority;
		Color m_wireFrameColor;
	};
}
#endif // !COLLIDER_WIREFRAME_DRAWER_3D_MAKER_H_