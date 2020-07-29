#include "TktkDX12BaseComponents/Other/ReceiveMessageToSelfDestroyer/ReceiveMessageToSelfDestroyerMaker.h"

namespace tktk
{
	ReceiveMessageToSelfDestroyerMaker ReceiveMessageToSelfDestroyerMaker::m_self;

	ReceiveMessageToSelfDestroyerMaker & ReceiveMessageToSelfDestroyerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = ReceiveMessageToSelfDestroyerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<ReceiveMessageToSelfDestroyer> ReceiveMessageToSelfDestroyerMaker::create()
	{
		return m_user->createComponent<ReceiveMessageToSelfDestroyer>(
			m_destroyMessegeType
			);
	}

	ReceiveMessageToSelfDestroyerMaker & ReceiveMessageToSelfDestroyerMaker::destroyMessegeType(int value)
	{
		m_destroyMessegeType = value;
		return *this;
	}
}