#include "TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h"

namespace tktk
{
	Transform3DMaker Transform3DMaker::m_self;

	Transform3DMaker& Transform3DMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = Transform3DMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<Transform3D> Transform3DMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<Transform3D>(
			m_initPosition,
			m_initScaleRate,
			m_initRotation,
			m_traceType
			);
	}

	Transform3DMaker& Transform3DMaker::initPosition(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initPosition = value;
		return *this;
	}

	Transform3DMaker& Transform3DMaker::initScaleRate(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initScaleRate = value;
		return *this;
	}

	Transform3DMaker& Transform3DMaker::initRotation(const tktkMath::Quaternion& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initRotation = value;
		return *this;
	}

	Transform3DMaker& Transform3DMaker::traceType(TraceParentType value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_traceType = value;
		return *this;
	}
}