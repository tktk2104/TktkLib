#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Mesh/BasicMeshData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	BasicMeshData::BasicMeshData(const BasicMeshInitParam& initParam)
		: m_useVertexBufferId(initParam.useVertexBufferId)
		, m_useIndexBufferId(initParam.useIndexBufferId)
		, m_indexNum(initParam.indexNum)
		, m_materialSlots(initParam.materialSlots)
	{
	}

	void BasicMeshData::writeShadowMap()
	{
		// �V���h�E�}�b�v�`��p�̐[�x�o�b�t�@�[�g�̂݁h��ݒ肷��
		DX12GameManager::setOnlyDepthStencil(DX12GameManager::getSystemId(SystemDsvDescriptorHeapType::ShadowMap));

		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(DX12GameManager::getSystemId(SystemViewportType::Basic));

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(DX12GameManager::getSystemId(SystemScissorRectType::Basic));

		// �ʏ탁�b�V���ŃV���h�E�}�b�v�`��p�̃p�C�v���C���X�e�[�g��ݒ肷��
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::ShadowMap));

		// �ʏ탁�b�V���ŃV���h�E�}�b�v�`��p�̃f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, DX12GameManager::getSystemId(SystemBasicDescriptorHeapType::BasicMeshShadowMap) } });

		// �g���C�A���O�����X�g�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// �`��Ŏg�p���钸�_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(m_useVertexBufferId);

		// �`��Ŏg�p����C���f�b�N�X�o�b�t�@��ݒ肷��
		DX12GameManager::setIndexBuffer(m_useIndexBufferId);

		// �h���[�R�[��
		DX12GameManager::drawIndexedInstanced(m_indexNum, 1U, 0U, 0U, 0U);

		// �[�x�X�e���V���o�b�t�@�[���V�F�[�_�[�Ŏg�����Ԃɂ���
		DX12GameManager::unSetDepthStencil(DX12GameManager::getSystemId(SystemDsvDescriptorHeapType::ShadowMap));

		// �R�}���h���X�g�����s����
		DX12GameManager::executeCommandList();
	}

	void BasicMeshData::drawMesh(const MeshDrawFuncBaseArgs& baseArgs)
	{
		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(baseArgs.viewportId);

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(baseArgs.scissorRectId);

		// �ʏ탁�b�V���p�̃p�C�v���C���X�e�[�g��ݒ肷��
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::BasicMesh));

		// �g���C�A���O�����X�g�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// �`��Ŏg�p���钸�_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(m_useVertexBufferId);

		// �`��Ŏg�p����C���f�b�N�X�o�b�t�@��ݒ肷��
		DX12GameManager::setIndexBuffer(m_useIndexBufferId);

		// �����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V����ݒ肷��i�o�b�N�o�b�t�@�[�ɒ��ŕ`�悷��ꍇ�͓��ꏈ���j
		if (baseArgs.rtvDescriptorHeapId == DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferAndDepthStencil(baseArgs.dsvDescriptorHeapId);
		}
		else
		{
			DX12GameManager::setRenderTargetAndDepthStencil(baseArgs.rtvDescriptorHeapId, baseArgs.dsvDescriptorHeapId, 0U, 1U);
		}

		// �}�e���A���̐������`�悷��
		for (const auto& node : m_materialSlots)
		{
			// �}�e���A���̏���ݒ肷��
			DX12GameManager::setMaterialData(node.useMaterialId);

			// �h���[�R�[��
			DX12GameManager::drawIndexedInstanced(node.indexBufferUseCount, 1U, node.indexBufferStartPos, 0U, 0U);
		}

		// �o�b�N�o�b�t�@�ȊO�ɕ`�悵�Ă�����g�p���������_�[�^�[�Q�b�g�o�b�t�@���V�F�[�_�[�Ŏg�p�����Ԃɂ���
		if (baseArgs.rtvDescriptorHeapId != DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRenderTarget(baseArgs.rtvDescriptorHeapId, 0U, 1U);
		}

		// �[�x�X�e���V���o�b�t�@�[���V�F�[�_�[�Ŏg�����Ԃɂ���
		DX12GameManager::unSetDepthStencil(baseArgs.dsvDescriptorHeapId);

		// �R�}���h���X�g�����s����
		DX12GameManager::executeCommandList();
	}
}