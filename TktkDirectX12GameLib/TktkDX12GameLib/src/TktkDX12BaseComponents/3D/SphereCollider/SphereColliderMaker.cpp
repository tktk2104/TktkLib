#include "TktkDX12BaseComponents/3D/SphereCollider/SphereColliderMaker.h"

namespace tktk
{
	SphereColliderMaker SphereColliderMaker::m_self;

	SphereColliderMaker & SphereColliderMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = SphereColliderMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<SphereCollider>SphereColliderMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<SphereCollider>(
			m_collisionGroupType,
			m_radius,
			m_localPosition
			);
	}

	SphereColliderMaker & SphereColliderMaker::collisionGroupType(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_collisionGroupType = value;
		return *this;
	}

	SphereColliderMaker & SphereColliderMaker::radius(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_radius = value;
		return *this;
	}

	SphereColliderMaker & SphereColliderMaker::localPosition(const tktkMath::Vector3 & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_localPosition = value;
		return *this;
	}
}