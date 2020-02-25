#ifndef COLLIDER_WIREFRAME_DRAWER_3D_MAKER_H_
#define COLLIDER_WIREFRAME_DRAWER_3D_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "ColliderWireFrameDrawer3D.h"

namespace tktk
{
	class ColliderWireFrameDrawer3DMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static ColliderWireFrameDrawer3DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<ColliderWireFrameDrawer3D> create();

		ColliderWireFrameDrawer3DMaker& drawPriority(float value);

		ColliderWireFrameDrawer3DMaker& wireFrameColor(const Color& value);

	private:

		// ���g�̃|�C���^
		static ColliderWireFrameDrawer3DMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		float m_drawPriority;
		Color m_wireFrameColor;
	};
}
#endif // !COLLIDER_WIREFRAME_DRAWER_3D_MAKER_H_