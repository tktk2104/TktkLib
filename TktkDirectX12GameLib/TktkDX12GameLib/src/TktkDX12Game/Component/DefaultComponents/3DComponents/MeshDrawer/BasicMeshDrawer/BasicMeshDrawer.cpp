#include "TktkDX12Game/Component/DefaultComponents/3DComponents/MeshDrawer/BasicMeshDrawer/BasicMeshDrawer.h"

namespace tktk
{
	BasicMeshDrawer::BasicMeshDrawer(float drawPriority, unsigned int meshId, unsigned int skeletonId, unsigned int useRtvDescriptorHeapId)
		: ComponentBase(drawPriority)
		, m_meshId(meshId)
		, m_skeletonId(skeletonId)
		, m_useRtvDescriptorHeapId(useRtvDescriptorHeapId)
	{
	}

	void BasicMeshDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}

		m_animator = getComponent<MeshAnimator>();
	}

	void BasicMeshDrawer::draw() const
	{
		if (!m_animator.expired())
		{
			m_animator->transformSkeleton(m_skeletonId);
		}

		// �{�[���s��̒萔�o�b�t�@���X�V����
		DX12GameManager::updateBoneMatrixCbuffer(m_skeletonId);

		// ���b�V���`��ɕK�v�Ȓl
		MeshDrawFuncBaseArgs baseArgs{};
		{
			// Transform3D���烏�[���h�s����擾
			baseArgs.worldMatrix = m_transform->calculateWorldMatrix();

			// �g�p����r���[�|�[�g�ԍ�
			baseArgs.viewportId = DX12GameManager::getSystemId(SystemViewportType::Basic);

			// �g�p����V�U�[��`�ԍ�
			baseArgs.scissorRectId = DX12GameManager::getSystemId(SystemScissorRectType::Basic);

			// �g�p���郌���_�[�^�[�Q�b�g�f�B�X�N���v�^�q�[�v�ԍ�
			baseArgs.rtvDescriptorHeapId = m_useRtvDescriptorHeapId;

			// �g�p����[�x�X�e���V���f�B�X�N���v�^�q�[�v�ԍ�
			baseArgs.dsvDescriptorHeapId = DX12GameManager::getSystemId(SystemDsvDescriptorHeapType::Basic);
		}
		
		// �J�������
		{
			baseArgs.viewMatrix = tktkMath::Matrix4::createLookAtLH(
				tktkMath::Vector3(0.0f, 15.0f, -20.0f),
				tktkMath::Vector3(0.0f, 8.0f, 0.0f),
				tktkMath::vec3Up
			);
			
			baseArgs.projectionMatrix = tktkMath::Matrix4::createPerspectiveFieldOfViewLH(
				90.0f,
				tktk::DX12GameManager::getWindowSize().x / tktk::DX12GameManager::getWindowSize().y,
				1.0f,
				100.0f
			);
		}

		// ���C�g���
		{
			baseArgs.lightPosition = tktkMath::Vector3(60.0f, 10.0f, -60.0f);

			baseArgs.lightMatrix
				= tktkMath::Matrix4::createLookAtLH(
					baseArgs.lightPosition,
					tktkMath::Vector3(0.0f, 0.0f, 0.0f),
					tktkMath::vec3Up
				)
				* tktkMath::Matrix4::createOrthographicLH(40, 40, 1.0f, 100.0f);
		}

		// ���b�V����`�悷��
		DX12GameManager::drawBasicMesh(m_meshId, baseArgs);
	}
}