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

		// �v���C�x�[�g�R���X�g���N�^�B
		ColliderWireFrameDrawer2DMaker() = default;
		ColliderWireFrameDrawer2DMaker(const ColliderWireFrameDrawer2DMaker& other) = default;
		ColliderWireFrameDrawer2DMaker& operator = (const ColliderWireFrameDrawer2DMaker& other) = default;

	public:

		// �쐬����
		CfpPtr<ColliderWireFrameDrawer2D> create();

		// �`��D��x��ݒ肷��
		ColliderWireFrameDrawer2DMaker& drawPriority(float value);

		// ���̐F��ݒ肷��
		ColliderWireFrameDrawer2DMaker& lineColor(const Color& value);

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		float m_drawPriority{ 0.0f };
		Color m_lineColor{ Color::white };
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_
