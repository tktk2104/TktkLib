#include "TktkDX12BaseComponents/2D/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2DMaker.h"

namespace tktk
{
	ColliderWireFrameDrawer2DMaker ColliderWireFrameDrawer2DMaker::m_self;

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = ColliderWireFrameDrawer2DMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<ColliderWireFrameDrawer2D> ColliderWireFrameDrawer2DMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<ColliderWireFrameDrawer2D>(
			m_drawPriority,
			m_lineColor,
			m_useLine2DMaterialIdArray
			);
	}

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::lineColor(const tktkMath::Color & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_lineColor = value;
		return *this;
	}

	ColliderWireFrameDrawer2DMaker& ColliderWireFrameDrawer2DMaker::useLine2DMaterialIdArray(const std::vector<unsigned int>& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useLine2DMaterialIdArray = value;
		return *this;
	}
}