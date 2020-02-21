#ifndef COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_
#define COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_

#include "ColliderWireFrameDrawer2D.h"

namespace tktk
{
	class ColliderWireFrameDrawer2DMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static ColliderWireFrameDrawer2DMaker& makeStart();

	public:

		// �쐬����
		ColliderWireFrameDrawer2D* create();

	public:

		ColliderWireFrameDrawer2DMaker& drawPriority(float value);

		ColliderWireFrameDrawer2DMaker& wireFrameColor(const Color& value);

	private:

		// ���g�̃|�C���^
		static ColliderWireFrameDrawer2DMaker m_self;

	private:

		float m_drawPriority;
		Color m_wireFrameColor;
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_