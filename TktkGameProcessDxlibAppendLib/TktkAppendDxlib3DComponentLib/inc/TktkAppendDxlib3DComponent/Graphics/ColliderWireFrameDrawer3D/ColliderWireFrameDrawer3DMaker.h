#ifndef COLLIDER_WIREFRAME_DRAWER_3D_MAKER_H_
#define COLLIDER_WIREFRAME_DRAWER_3D_MAKER_H_

#include <memory>
#include "ColliderWireFrameDrawer3D.h"

namespace tktk
{
	class ColliderWireFrameDrawer3DMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static ColliderWireFrameDrawer3DMaker& makeStart();

	public:

		// �쐬����
		std::shared_ptr<ColliderWireFrameDrawer3D> create();

		ColliderWireFrameDrawer3DMaker& drawPriority(float value);

		ColliderWireFrameDrawer3DMaker& wireFrameColor(const Color& value);

	private:

		// ���g�̃|�C���^
		static ColliderWireFrameDrawer3DMaker m_self;

	private:

		float m_drawPriority;
		Color m_wireFrameColor;
	};
}
#endif // !COLLIDER_WIREFRAME_DRAWER_3D_MAKER_H_