#include "TktkDX12BaseComponents/2D/RectColliderExtrusion/RectColliderExtrusionMaker.h"

namespace tktk
{
	RectColliderExtrusionMaker RectColliderExtrusionMaker::m_self;

	RectColliderExtrusionMaker & RectColliderExtrusionMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = RectColliderExtrusionMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<RectColliderExtrusion> RectColliderExtrusionMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<RectColliderExtrusion>();
	}
}