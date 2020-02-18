#ifndef COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_
#define COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_

#include <memory>
#include "ColliderWireFrameDrawer2D.h"

namespace tktk
{
	class ColliderWireFrameDrawer2DMaker
	{
	public:

		// インスタンス作成開始
		static ColliderWireFrameDrawer2DMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<ColliderWireFrameDrawer2D> create();

		ColliderWireFrameDrawer2DMaker& drawPriority(float value);

		ColliderWireFrameDrawer2DMaker& wireFrameColor(const Color& value);

	private:

		// 自身のポインタ
		static ColliderWireFrameDrawer2DMaker m_self;

	private:

		float m_drawPriority;
		Color m_wireFrameColor;
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_