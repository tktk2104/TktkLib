#include "TktkDX12BaseComponents/3D/MeshDrawer/BasicMeshDrawer.h"

namespace tktk
{
	BasicMeshDrawer::BasicMeshDrawer(float drawPriority, unsigned int meshId, unsigned int skeletonId, unsigned int cameraId, unsigned int shadowMapCameraId, unsigned int useRtvDescriptorHeapId)
		: ComponentBase(drawPriority)
		, m_meshId(meshId)
		, m_skeletonId(skeletonId)
		, m_cameraId(cameraId)
		, m_shadowMapCameraId(shadowMapCameraId)
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
			baseArgs.transformBufferData.worldMatrix = m_transform->calculateWorldMatrix();

			// �g�p����J�����̃r���[�s��
			baseArgs.transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_cameraId);

			// �g�p����J�����̃v���W�F�N�V�����s��
			baseArgs.transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_cameraId);

			// �g�p����r���[�|�[�g�ԍ�
			baseArgs.viewportId = DX12GameManager::getSystemId(SystemViewportType::Basic);

			// �g�p����V�U�[��`�ԍ�
			baseArgs.scissorRectId = DX12GameManager::getSystemId(SystemScissorRectType::Basic);

			// �g�p���郌���_�[�^�[�Q�b�g�f�B�X�N���v�^�q�[�v�ԍ�
			baseArgs.rtvDescriptorHeapId = m_useRtvDescriptorHeapId;

			// �g�p����[�x�X�e���V���f�B�X�N���v�^�q�[�v�ԍ�
			baseArgs.dsvDescriptorHeapId = DX12GameManager::getSystemId(SystemDsvDescriptorHeapType::Basic);

			// �V���h�E�}�b�v���g�p����ׂɕK�v�ȃV���h�E�}�b�v�J�����s��
			baseArgs.shadowMapBufferData.shadowMapViewProjMat = DX12GameManager::getViewMatrix(m_shadowMapCameraId) * DX12GameManager::getProjectionMatrix(m_shadowMapCameraId);
		}

		// ���C�g���
		{
			baseArgs.lightBufferData.lightPosition = tktkMath::Vector3(60.0f, 10.0f, -60.0f);
		}

		// ���b�V����`�悷��
		DX12GameManager::drawBasicMesh(m_meshId, baseArgs);
	}
}