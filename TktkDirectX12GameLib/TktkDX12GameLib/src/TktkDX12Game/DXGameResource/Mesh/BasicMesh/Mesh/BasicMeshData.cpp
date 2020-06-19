#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Mesh/BasicMeshData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/BasicMeshShadowMapCbufferData.h"

namespace tktk
{
	BasicMeshData::BasicMeshData(const BasicMeshInitParam& initParam)
		: m_useVertexBufferId(initParam.useVertexBufferId)
		, m_useIndexBufferId(initParam.useIndexBufferId)
		, m_indexNum(initParam.indexNum)
		, m_materialSlots(initParam.materialSlots)
	{
	}

	void BasicMeshData::writeShadowMap(const MeshWriteShadowFuncBaseArgs& baseArgs)
	{
		// �ʏ탁�b�V���ŃV���h�E�}�b�v�`��p�̒萔�o�b�t�@���X�V����
		updateShadowMapCbuffer(baseArgs);

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
		MeshMaterialDrawFuncArgs materialDrawFuncArgs{};
		materialDrawFuncArgs.useVertexBufferId		= m_useVertexBufferId;
		materialDrawFuncArgs.useIndexBufferId		= m_useIndexBufferId;


		for (const auto& node : m_materialSlots)
		{
			materialDrawFuncArgs.indexBufferStartPos = node.indexBufferStartPos;
			materialDrawFuncArgs.indexBufferUseCount = node.indexBufferUseCount;
		
			DX12GameManager::drawBasicMeshMaterial(node.useMaterialId, baseArgs, materialDrawFuncArgs);
		}

		// �R�}���h���X�g�����s����
		DX12GameManager::executeCommandList();
	}

	void BasicMeshData::updateShadowMapCbuffer(const MeshWriteShadowFuncBaseArgs& baseArgs)
	{
		BasicMeshShadowMapCbufferData cbufferData{};

		cbufferData.worldMatrix = baseArgs.worldMatrix;
		cbufferData.viewMatrix = baseArgs.viewMatrix;
		cbufferData.projectionMatrix = baseArgs.projectionMatrix;

		for (unsigned int i = 0; i < 128U; i++)
		{
			cbufferData.boneMatrix[i] = baseArgs.boneMatrix[i];
		}

		DX12GameManager::updateConstantBuffer(DX12GameManager::getSystemId(SystemConstantBufferType::BasicMeshShadowMap), cbufferData);
	}
}