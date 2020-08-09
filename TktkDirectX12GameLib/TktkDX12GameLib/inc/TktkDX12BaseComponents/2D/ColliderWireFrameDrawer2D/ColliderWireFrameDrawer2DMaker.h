#ifndef COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_
#define COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_

#include "ColliderWireFrameDrawer2D.h"

namespace tktk
{
	// �uColliderWireFrameDrawer2D�v�̃C���X�^���X���쐬����N���X
	class ColliderWireFrameDrawer2DMaker
	{
	private:  /* �v���C�x�[�g�R���X�g���N�^�B */

		ColliderWireFrameDrawer2DMaker() = default;
		ColliderWireFrameDrawer2DMaker(const ColliderWireFrameDrawer2DMaker & other) = default;
		ColliderWireFrameDrawer2DMaker& operator = (const ColliderWireFrameDrawer2DMaker & other) = default;

	public:

		// �쐬�J�n
		static ColliderWireFrameDrawer2DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<ColliderWireFrameDrawer2D> create();

		// �`��D��x��ݒ肷��
		ColliderWireFrameDrawer2DMaker& drawPriority(float value);

		// ���̐F��ݒ肷��
		ColliderWireFrameDrawer2DMaker& lineColor(const tktkMath::Color& value);

		// �g�p����2D���C���}�e���A���̔z���ݒ肷��
		ColliderWireFrameDrawer2DMaker& useLine2DMaterialIdArray(const std::vector<unsigned int>& value);

	private:

		static ColliderWireFrameDrawer2DMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr				m_user{ };
		float						m_drawPriority{ 0.0f };
		tktkMath::Color				m_lineColor{ tktkMath::colorWhite };
		std::vector<unsigned int>	m_useLine2DMaterialIdArray{};
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_
