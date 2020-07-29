#include "TktkDX12BaseComponents/3D/BoxCollider/BoxColliderMaker.h"

namespace tktk
{
	BoxColliderMaker BoxColliderMaker::m_self;

	BoxColliderMaker & BoxColliderMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BoxColliderMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<BoxCollider> BoxColliderMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<BoxCollider>(
			m_collisionGroupType,
			m_boxSize,
			m_localPosition
			);
	}

	BoxColliderMaker & BoxColliderMaker::collisionGroupType(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_collisionGroupType = value;
		return *this;
	}

	BoxColliderMaker & BoxColliderMaker::boxSize(const tktkMath::Vector3 & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_boxSize = value;
		return *this;
	}

	BoxColliderMaker & BoxColliderMaker::localPosition(const tktkMath::Vector3 & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_localPosition = value;
		return *this;
	}
}