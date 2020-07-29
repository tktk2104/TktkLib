#include "TktkDX12BaseComponents/2D/RectCollider/RectColliderMaker.h"

namespace tktk
{
	RectColliderMaker RectColliderMaker::m_self;

	RectColliderMaker & RectColliderMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = RectColliderMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<RectCollider> RectColliderMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<RectCollider>(
			m_collisionGroupType,
			m_rectSize,
			m_localPosition
			);
	}

	RectColliderMaker & RectColliderMaker::collisionGroupType(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_collisionGroupType = value;
		return *this;
	}

	RectColliderMaker & RectColliderMaker::rectSize(const tktkMath::Vector2 & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_rectSize = value;
		return *this;
	}

	RectColliderMaker & RectColliderMaker::localPosition(const tktkMath::Vector2 & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_localPosition = value;
		return *this;
	}
}