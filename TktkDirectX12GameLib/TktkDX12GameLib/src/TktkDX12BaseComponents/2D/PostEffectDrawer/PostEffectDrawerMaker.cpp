#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawerMaker.h"

namespace tktk
{
	PostEffectDrawerMaker PostEffectDrawerMaker::m_self;

	PostEffectDrawerMaker& PostEffectDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = PostEffectDrawerMaker();
		
		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�vID�̃f�t�H���g�l�̓o�b�N�o�b�t�@
		m_self.m_useRtvDescriptorHeapId = DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<PostEffectDrawer> PostEffectDrawerMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<PostEffectDrawer>(
			m_drawPriority,
			m_postEffectMaterialId,
			m_useRtvDescriptorHeapId
			);
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::useRtvDescriptorHeapIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useRtvDescriptorHeapId = value;
		return *this;
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::postEffectMaterialIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_postEffectMaterialId = value;
		return *this;
	}
}