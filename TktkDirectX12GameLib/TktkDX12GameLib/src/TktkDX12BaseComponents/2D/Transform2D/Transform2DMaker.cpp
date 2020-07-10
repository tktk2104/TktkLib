#include "TktkDX12BaseComponents/2D/Transform2D/Transform2DMaker.h"

namespace tktk
{
	Transform2DMaker Transform2DMaker::m_self;

	Transform2DMaker& Transform2DMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = Transform2DMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<Transform2D> Transform2DMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<Transform2D>(
			m_initPosition,
			m_initScaleRate,
			m_initRotationDeg,
			m_traceType
			);
	}

	Transform2DMaker& Transform2DMaker::initPosition(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initPosition = value;
		return *this;
	}

	Transform2DMaker& Transform2DMaker::initScaleRate(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initScaleRate = value;
		return *this;
	}

	Transform2DMaker& Transform2DMaker::initRotationDeg(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initRotationDeg = value;
		return *this;
	}

	Transform2DMaker& Transform2DMaker::traceType(TraceParentType value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_traceType = value;
		return *this;
	}
}