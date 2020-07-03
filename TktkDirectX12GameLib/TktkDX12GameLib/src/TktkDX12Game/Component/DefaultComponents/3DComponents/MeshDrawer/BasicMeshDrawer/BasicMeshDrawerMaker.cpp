#include "TktkDX12Game/Component/DefaultComponents/3DComponents/MeshDrawer/BasicMeshDrawer/BasicMeshDrawerMaker.h"

namespace tktk
{
	BasicMeshDrawerMaker BasicMeshDrawerMaker::m_self;

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BasicMeshDrawerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�vID�̃f�t�H���g�l�̓o�b�N�o�b�t�@
		m_self.m_useRtvDescriptorHeapId = DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<BasicMeshDrawer> BasicMeshDrawerMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<BasicMeshDrawer>(
			m_drawPriority,
			m_meshId,
			m_skeletonId,
			m_useRtvDescriptorHeapId
			);
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::useRtvDescriptorHeapIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useRtvDescriptorHeapId = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::meshIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_meshId = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::skeletonIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_skeletonId = value;
		return *this;
	}
}