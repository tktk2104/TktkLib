#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Material/BasicMeshMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/BasicMeshConstantBufferData.h"

namespace tktk
{
	BasicMeshMaterialData::BasicMeshMaterialData(const BasicMeshMaterialInitParam& initParam)
		: m_createDescriptorHeapId(initParam.createDescriptorHeapId)
		, m_materialAmbient(initParam.materialAmbient)
		, m_materialDiffuse(initParam.materialDiffuse)
		, m_materialSpecular(initParam.materialSpecular)
		, m_materialEmissive(initParam.materialEmissive)
		, m_materialShiniess(initParam.materialShiniess)
	{
		// �f�B�X�N���v�^�q�[�v�����
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(3U);

		{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

			// �A���x�h�}�b�v�ƃV���h�E�}�b�v�̂Q���
			srvDescriptorParam.descriptorParamArray = {
				{ BufferType::texture,		initParam.useAlbedoMapTextureId											},
				{ BufferType::depthStencil, DX12GameManager::getSystemId(SystemDepthStencilBufferType::ShadowMap)	}
			};
		}

		{ /* �R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// 
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::BasicMesh)			}
			};
		}

		{ /* �R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// 
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::BasicMeshBoneMat)	}
			};
		}
		DX12GameManager::createBasicDescriptorHeap(m_createDescriptorHeapId, descriptorHeapInitParam);
	}

	void BasicMeshMaterialData::drawUseMaterial(const MeshDrawFuncBaseArgs& baseArgs, const MeshMaterialDrawFuncArgs& materialArgs)
	{
		// �ʏ탁�b�V���p�̒萔�o�b�t�@���X�V����
		updateBasicMeshConstantBuffer(baseArgs);

		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(baseArgs.viewportId);

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(baseArgs.scissorRectId);

		// �����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V����ݒ肷��i�o�b�N�o�b�t�@�[�ɒ��ŕ`�悷��ꍇ�͓��ꏈ���j
		if (baseArgs.rtvDescriptorHeapId == DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferAndDepthStencil(baseArgs.dsvDescriptorHeapId);
		}
		else
		{
			DX12GameManager::setRenderTargetAndDepthStencil(baseArgs.rtvDescriptorHeapId, baseArgs.dsvDescriptorHeapId, 0U, 1U);
		}

		// �ʏ탁�b�V���p�̃p�C�v���C���X�e�[�g��ݒ肷��
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::BasicMesh));
		
		// �ʏ탁�b�V���p�̃f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_createDescriptorHeapId } });
		
		// �g���C�A���O�����X�g�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// �`��Ŏg�p���钸�_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(materialArgs.useVertexBufferId);

		// �`��Ŏg�p����C���f�b�N�X�o�b�t�@��ݒ肷��
		DX12GameManager::setIndexBuffer(materialArgs.useIndexBufferId);

		// �h���[�R�[��
		DX12GameManager::drawIndexedInstanced(materialArgs.indexBufferUseCount, 1U, materialArgs.indexBufferStartPos, 0U, 0U);
	
		// �o�b�N�o�b�t�@�ȊO�ɕ`�悵�Ă�����g�p���������_�[�^�[�Q�b�g�o�b�t�@���V�F�[�_�[�Ŏg�p�����Ԃɂ���
		if (baseArgs.rtvDescriptorHeapId != DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRenderTarget(baseArgs.rtvDescriptorHeapId, 0U, 1U);
		}

		// �[�x�X�e���V���o�b�t�@�[���V�F�[�_�[�Ŏg�����Ԃɂ���
		DX12GameManager::unSetDepthStencil(baseArgs.dsvDescriptorHeapId);

		//// �R�}���h���X�g�����s����
		//DX12GameManager::executeCommandList();
	}

	// �ʏ탁�b�V���p�̒萔�o�b�t�@���X�V����
	void BasicMeshMaterialData::updateBasicMeshConstantBuffer(const MeshDrawFuncBaseArgs& baseArgs)
	{
		BasicMeshConstantBufferData constantBufferData;

		constantBufferData.worldMatrix = baseArgs.worldMatrix;
		constantBufferData.viewMatrix = baseArgs.viewMatrix;
		constantBufferData.projectionMatrix = baseArgs.projectionMatrix;

		/*for (unsigned int i = 0; i < 128U; i++)
		{
			constantBufferData.boneMatrix[i] = baseArgs.boneMatrix[i];
		}*/

		constantBufferData.lightAmbient		= baseArgs.lightAmbient;
		constantBufferData.lightDiffuse		= baseArgs.lightDiffuse;
		constantBufferData.lightSpeqular	= baseArgs.lightSpeqular;
		constantBufferData.lightPosition	= baseArgs.lightPosition;
		constantBufferData.lightMatrix		= baseArgs.lightMatrix;

		constantBufferData.materialAmbient	= m_materialAmbient;
		constantBufferData.materialDiffuse	= m_materialDiffuse;
		constantBufferData.materialSpecular = m_materialSpecular;
		constantBufferData.materialEmissive = m_materialEmissive;
		constantBufferData.materialShiniess = m_materialShiniess;

		DX12GameManager::updateConstantBuffer(DX12GameManager::getSystemId(SystemConstantBufferType::BasicMesh), constantBufferData);

		BasicMeshBoneMatrix boneMatBuf;

		for (unsigned int i = 0; i < 128U; i++)
		{
			boneMatBuf.boneMatrix[i] = baseArgs.boneMatrix[i];
		}
		DX12GameManager::updateConstantBuffer(DX12GameManager::getSystemId(SystemConstantBufferType::BasicMeshBoneMat), boneMatBuf);
	}
}