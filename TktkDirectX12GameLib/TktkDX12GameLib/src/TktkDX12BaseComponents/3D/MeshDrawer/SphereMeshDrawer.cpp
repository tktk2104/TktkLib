#include "TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshDrawer.h"

namespace tktk
{
	SphereMeshDrawer::SphereMeshDrawer(float drawPriority, unsigned int cameraId, unsigned int shadowMapCameraId, unsigned int lightId, unsigned int useRtvDescriptorHeapId)
		: ComponentBase(drawPriority)
		, m_cameraId(cameraId)
		, m_shadowMapCameraId(shadowMapCameraId)
		, m_lightId(lightId)
		, m_useRtvDescriptorHeapId(useRtvDescriptorHeapId)
	{
	}

	void SphereMeshDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}
	}

	void SphereMeshDrawer::draw() const
	{
		DX12GameManager::resetBoneMatrixCbuffer();

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

			// �g�p���郉�C�g�ԍ�
			baseArgs.lightId = m_lightId;

			// �V���h�E�}�b�v���g�p����ׂɕK�v�ȃV���h�E�}�b�v�J�����s��
			baseArgs.shadowMapBufferData.shadowMapViewProjMat = DX12GameManager::getViewMatrix(m_shadowMapCameraId) * DX12GameManager::getProjectionMatrix(m_shadowMapCameraId);
		}

		// ���b�V����`�悷��
		DX12GameManager::drawBasicMesh(DX12GameManager::getSystemId(SystemBasicMeshType::Sphere), baseArgs);
	}
}