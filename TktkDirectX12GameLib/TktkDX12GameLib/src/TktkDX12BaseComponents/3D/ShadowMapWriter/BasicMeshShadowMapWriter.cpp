#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BasicMeshShadowMapWriter.h"

namespace tktk
{
	BasicMeshShadowMapWriter::BasicMeshShadowMapWriter(float drawPriority, unsigned int meshId, unsigned int skeletonId, unsigned int cameraId)
		: ComponentBase(drawPriority)
		, m_meshId(meshId)
		, m_skeletonId(skeletonId)
		, m_cameraId(cameraId)
	{
	}

	void BasicMeshShadowMapWriter::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshShadowMapWriter not found Transform3D");
		}
	}

	void BasicMeshShadowMapWriter::draw() const
	{
		// �{�[���s��̒萔�o�b�t�@���X�V����
		DX12GameManager::updateBoneMatrixCbuffer(m_skeletonId);

		// �[�x�}�b�v�����o���ɕK�v�Ȓl
		MeshTransformCbuffer transformBufferData{};
		{
			// Transform3D���烏�[���h�s����擾
			transformBufferData.worldMatrix = m_transform->calculateWorldMatrix();

			// �g�p����J�����̃r���[�s��
			transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_cameraId);

			// �g�p����J�����̃v���W�F�N�V�����s��
			transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_cameraId);
		}

		// �V���h�E�}�b�v��`�悷��
		DX12GameManager::writeBasicMeshShadowMap(m_meshId, transformBufferData);
	}
}