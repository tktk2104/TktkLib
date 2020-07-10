#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BasicMeshShadowMapWriterMaker.h"

namespace tktk
{
	BasicMeshShadowMapWriterMaker BasicMeshShadowMapWriterMaker::m_self;

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BasicMeshShadowMapWriterMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<BasicMeshShadowMapWriter> BasicMeshShadowMapWriterMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<BasicMeshShadowMapWriter>(
			m_drawPriority,
			m_meshId,
			m_skeletonId
			);
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::meshIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_meshId = value;
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::skeletonIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_skeletonId = value;
		return *this;
	}
}