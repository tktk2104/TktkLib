#include "TktkDX12BaseComponents/2D/InertialMovement2D/InertialMovement2DMaker.h"

namespace tktk
{
	InertialMovement2DMaker InertialMovement2DMaker::m_self;

	InertialMovement2DMaker & InertialMovement2DMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = InertialMovement2DMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<InertialMovement2D> InertialMovement2DMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<InertialMovement2D>(
			m_decelerationPerSec,
			m_initVelocity
			);
	}

	InertialMovement2DMaker & InertialMovement2DMaker::decelerationPerSec(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_decelerationPerSec = value;
		return *this;
	}

	InertialMovement2DMaker & InertialMovement2DMaker::initVelocity(const tktkMath::Vector2 & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initVelocity = value;
		return *this;
	}
}