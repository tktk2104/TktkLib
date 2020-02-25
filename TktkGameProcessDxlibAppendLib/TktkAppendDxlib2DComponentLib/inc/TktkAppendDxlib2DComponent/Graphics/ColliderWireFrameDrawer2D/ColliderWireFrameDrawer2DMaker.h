#ifndef COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_
#define COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "ColliderWireFrameDrawer2D.h"

namespace tktk
{
	class ColliderWireFrameDrawer2DMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static ColliderWireFrameDrawer2DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<ColliderWireFrameDrawer2D> create();

	public:

		ColliderWireFrameDrawer2DMaker& drawPriority(float value);

		ColliderWireFrameDrawer2DMaker& wireFrameColor(const Color& value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static ColliderWireFrameDrawer2DMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		float m_drawPriority{ 0.0f };
		Color m_wireFrameColor{ Color::white };
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_