#include "TktkDX12BaseComponents/2D/Line2dDrawer/Line2DDrawerMaker.h"

namespace tktk
{
	Line2DDrawerMaker Line2DDrawerMaker::m_self;

	Line2DDrawerMaker & Line2DDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = Line2DDrawerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�vID�̃f�t�H���g�l�̓o�b�N�o�b�t�@
		m_self.m_useRtvDescriptorHeapId = DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<Line2DDrawer> Line2DDrawerMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<Line2DDrawer>(
			m_drawPriority,
			m_useLine2DMaterialId,
			m_lineVertexArray,
			m_lineColor,
			m_blendRate,
			m_useRtvDescriptorHeapId
			);
	}

	Line2DDrawerMaker & Line2DDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	Line2DDrawerMaker & Line2DDrawerMaker::lineVertexArray(const std::vector<tktkMath::Vector2>& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_lineVertexArray = value;
		return *this;
	}

	Line2DDrawerMaker & Line2DDrawerMaker::lineColor(const tktkMath::Color & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_lineColor = value;
		return *this;
	}

	Line2DDrawerMaker & Line2DDrawerMaker::blendRate(const tktkMath::Color & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_blendRate = value;
		return *this;
	}

	Line2DDrawerMaker& Line2DDrawerMaker::useLine2DMaterialIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useLine2DMaterialId = value;
		return *this;
	}

	Line2DDrawerMaker& Line2DDrawerMaker::useRtvDescriptorHeapIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useRtvDescriptorHeapId = value;
		return *this;
	}
}