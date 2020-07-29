#include "TktkDX12BaseComponents/2D/Polygon2dCollider/Polygon2dColliderMaker.h"

namespace tktk
{
	Polygon2dColliderMaker Polygon2dColliderMaker::m_self;

	Polygon2dColliderMaker & Polygon2dColliderMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = Polygon2dColliderMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<Polygon2dCollider> Polygon2dColliderMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<Polygon2dCollider>(
			m_collisionGroupType,
			m_vertexs,
			m_localPosition
			);
	}

	Polygon2dColliderMaker & Polygon2dColliderMaker::collisionGroupType(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_collisionGroupType = value;
		return *this;
	}

	Polygon2dColliderMaker & Polygon2dColliderMaker::vertexs(const std::vector<tktkMath::Vector2> & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_vertexs = value;
		return *this;
	}

	Polygon2dColliderMaker& Polygon2dColliderMaker::localPosition(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_localPosition = value;
		return *this;
	}
}